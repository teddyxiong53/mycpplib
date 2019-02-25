#ifndef MUDUO_BASE_DATE_H
#define MUDUO_BASE_DATE_H
#include "copyable.h"
#include <string>
struct tm;
namespace muduo
{
class Date: public muduo::copyable
{
public:
    struct YearMonthDay {
        int year;
        int month;
        int day;
    };
    static const int kDaysPerWeek = 7;
    static const int kJulianDayOf1970_01_01;
    Date()
        : julianDayNumber_(0)
    {}
    Date(int year, int month, int day);
    explicit Date(int julianDayNum)
        : julianDayNumber_(julianDayNum)
    {}

    explicit Date(const struct tm&);
    void swap(Date& that) {
        std::swap(julianDayNumber_, that.julianDayNumber_);
    }
    bool valid() const {
        return julianDayNumber_ > 0;
    }
    //converts to yyyy-mm-dd
    std::string toIsoString() const;
    struct YearMonthDay yearMonthDay() const;
    int year() const {
        return yearMonthDay().year;
    }
    int month() const {
        return yearMonthDay().month;
    }
    int day() const {
        return yearMonthDay().day;
    }
    int weekDay() const {
        return (julianDayNumber_+1)%kDaysPerWeek;
    }
    int julianDayNumber() const {
        return julianDayNumber_;
    }
private:
    int julianDayNumber_;
};
};

#endif