#ifndef MUDUO_NET_EVENTLOOP_H
#define MUDUO_NET_EVENTLOOP_H

#include "thread/Thread.h"
#include <boost/noncopyable.hpp>
namespace muduo
{
class EventLoop: boost::noncopyable
{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void assertInLoopThread() {
        if(!isInLoopThread()) {
            abortNotInLoopThread();
        }
    }
    bool isInLoopThread() {
        return threadId_ == CurrentThread::tid();
    }
private:
    bool looping_;
    const pid_t threadId_;
    void abortNotInLoopThread();
};
} // muduo

#endif //MUDUO_NET_EVENTLOOP_H