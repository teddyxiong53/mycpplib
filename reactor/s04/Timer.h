#ifndef MUDUO_NET_TIMER_H
#define MUDUO_NET_TIMER_H
#include <boost/noncopyable.hpp>
#include "datetime/Timestamp.h"
#include "Callbacks.h"

namespace muduo
{
class Timer : boost::noncopyable
{
public:
    Timer(const TimerCallback& cb, Timestamp when, double interval)
     : callback_(cb),
       expiration_(when),
       interval_(interval),
       repeat_(interval > 0.0)
    {

    }
    void run() const {
        callback_();
    }
    Timestamp expiration() {
        return expiration_;
    }
    bool repeat() {
        return repeat_;
    }
    void restart(Timestamp now);

private:
    const TimerCallback callback_;
    Timestamp expiration_;
    const double interval_;
    const bool repeat_;
};
} // muduo


#endif //MUDUO_NET_TIMER_H