#ifndef MUDUO_BASE_TIMEZONE_H
#define MUDUO_BASE_TIMEZONE_H
#include "copyable.h"
#include <boost/shared_ptr.hpp>
#include <time.h>


namespace muduo {
class TimeZone : public muduo:copyable
{
public:
    explicit TimeZone(const char *zonefile);
    struct tm toLocalTime(time_t secondsSinceEpoch);
    time_t fromLocalTime(const struct tm &) const;

    static struct tm toUtcTime(time_t secondsSinceEpoch);
    static time_t fromUtcTime(const struct tm &);
    static time_t fromUtcTime(int year, int month, int day, int hour, int minute, int second);
    struct Data;
private:
    boost::shared_ptr<Data> data_;
};
};

#endif