#ifndef MUDUO_NET_TIMERID_H
#define MUDUO_NET_TIMERID_H

#include "datetime/copyable.h"

namespace muduo
{
class Timer;
class TimerId: public muduo::copyable
{
public:
    explicit TimerId(Timer *timer)
     : value_(timer)
    {

    }
private:
    Timer *value_;
};
} // muduo

#endif //MUDUO_NET_TIMERID_H