#ifndef MUDUO_BASE_LOGSTREAM_H
#define MUDUO_BASE_LOGSTREAM_H

#include <assert.h>
#include <string.h>
#include <string>
#include <boost/noncopyable.hpp>

namespace muduo
{
using std::string;
namespace detail
{
const int kSmallBuffer = 4000;
const int kLargeBuffer = 4000*1000;

template<int SIZE>
class FixedBuffer: boost::noncopyable
{
public:
    FixedBuffer()
     : cur_(data_)
    {
        setCookie(cookieStart);
    }

    ~FixedBuffer() {
        setCookie(cookieEnd);
    }

    char *current() {
        return cur_;
    }
    const char *data() const {
        return data_;
    }
    int length() const {
        return cur_ - data_;
    }
    int avail() const {
        return static_cast<int>(end() - cur_);
    }
    void add(size_t len) {
        cur_ += len;
    }
    void reset() {
        cur_ = data_;
    }
    void bzero() {
        bzero(data_, sizeof(data_));
    }
    const char *debugString();
    void setCookie(void (*cookie)()) {
        cookie_ = cookie;
    }
    string asString() const {
        return string(data_, length());
    }
private:
    static void cookieStart();
    static void cookieEnd();
    void (*cookie_)();
    const char *end() const {
        return data_ + sizeof(data_);
    }
    char data_[SIZE];
    char *cur_;
};

class T {
public:
    T(const char *str, int len)
     : str_(str),
       len_(len)
    {
        assert(strlen(str) == len_);
    }
    const char *str_;
    const size_t len_;
};

class LogStream : boost::noncopyable
{
    typedef LogStream self;
public:
    typedef detail::FixedBuffer<detail::kSmallBuffer> Buffer;

}
}
}

#endif