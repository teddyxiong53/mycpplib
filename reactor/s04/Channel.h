#ifndef MUDUO_NET_CHANNEL_H
#define MUDUO_NET_CHANNEL_H

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

namespace muduo
{
class EventLoop;
class Channel : boost::noncopyable
{
public:
    typedef boost::function<void ()> EventCallback;
    Channel(EventLoop *loop, int fd);
    void handleEvent();

    void setReadCallback(const EventCallback& cb) {
        readCallback_ = cb;
    }
    void setWriteCallback(const EventCallback& cb) {
        writeCallback_ = cb;
    }
    void setErrorCallback(const EventCallback& cb) {
        errorCallback_ = cb;
    }
    int fd() {
        return fd_;

    }
    int events() {
        return events_;
    }
    int set_revents(int revt) {
        revents_ = revt;
    }
    bool isNoneEvent() {
        return events_ == kNoneEvent;
    }
    void enableReading() {
        events_ |= kReadEvent;
        update();
    }
    int index() {
        return index_;
    }
    void set_index(int idx) {
        index_ = idx;
    }
    EventLoop *ownerLoop() {
        return loop_;
    }

private:
    void update();
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;
    const int fd_;
    int events_;
    int revents_;
    int index_;
    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
};
} // muduo


#endif //MUDUO_NET_CHANNEL_H