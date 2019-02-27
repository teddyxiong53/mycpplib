#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include "thread/Thread.h"
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>

namespace muduo
{
class Channel;
class Poller;

class EventLoop: boost::noncopyable
{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void quit();
    void updateChannel(Channel *channel);

    void assertInLoopThread() {
        if(!isInLoopThread()) {
            abortNotInLoopThread();
        }
    }
    bool isInLoopThread() {
        return threadId_ == CurrentThread::tid();
    }
private:
    typedef std::vector<Channel *> ChannelList;
    bool looping_;
    bool quit_;
    const pid_t threadId_;
    boost::scoped_ptr<Poller> poller_;
    ChannelList activeChannels_;
    void abortNotInLoopThread();
};
} // muduo

#endif //MUDUO_NET_EVENTLOOP_H