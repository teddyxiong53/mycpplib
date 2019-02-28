#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include "thread/Thread.h"
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>
#include "datetime/Timestamp.h"
#include "Callbacks.h"
#include "TimerId.h"
#include "thread/Mutex.h"

namespace muduo
{
class Channel;
class Poller;
class TimerQueue;

class EventLoop: boost::noncopyable
{
public:
    typedef boost::function<void ()> Functor;

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
    void runInLoop(const Functor& cb);
    void queueInLoop(const Functor& cb);

    TimerId runAt(const Timestamp &time, const TimerCallback &cb);
    TimerId runAfter(double delay, const TimerCallback &cb);
    TimerId runEvery(double interval, const TimerCallback& cb);

    void wakeup();

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

    void handleRead();
    void doPendingFunctors();

    bool callingPendingFunctors_;
    int wakeupFd_;
    boost::scoped_ptr<Channel> wakeupChannel_;

    MutexLock mutex_;
    std::vector<Functor> pendingFunctors_;

};
} // muduo

#endif //MUDUO_NET_EVENTLOOP_H