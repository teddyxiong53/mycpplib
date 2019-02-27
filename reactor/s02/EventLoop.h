#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include "thread/Thread.h"
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>
#include "datetime/Timestamp.h"
#include "Callbacks.h"
#include "TimerId.h"

namespace muduo
{
class Channel;
class Poller;
class TimerQueue;

class EventLoop: boost::noncopyable
{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void quit();

    Timestamp pollReturnTime() {
        return pollReturnTime_;
    }

    void updateChannel(Channel *channel);

    void assertInLoopThread() {
        if(!isInLoopThread()) {
            abortNotInLoopThread();
        }
    }
    bool isInLoopThread() {
        return threadId_ == CurrentThread::tid();
    }

    TimerId runAt(const Timestamp &time, const TimerCallback &cb);
    TimerId runAfter(double delay, const TimerCallback &cb);
    TimerId runEvery(double interval, const TimerCallback& cb);

private:
    typedef std::vector<Channel *> ChannelList;
    bool looping_;
    bool quit_;
    const pid_t threadId_;
    boost::scoped_ptr<Poller> poller_;
    ChannelList activeChannels_;
    void abortNotInLoopThread();

    Timestamp pollReturnTime_;
    boost::scoped_ptr<TimerQueue> timerQueue_;
};
} // muduo

#endif //MUDUO_NET_EVENTLOOP_H