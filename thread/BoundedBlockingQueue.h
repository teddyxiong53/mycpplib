#ifndef MUDUO_BASE_BOUNDEDBLOCKINGQUEUE_H
#define MUDUO_BASE_BOUNDEDBLOCKINGQUEUE_H
#include "Condition.h"
#include "Mutex.h"
#include <boost/noncopyable.hpp>
#include <boost/circular_buffer.hpp>
#include <assert.h>

namespace muduo
{
template<typename T>
class BoundedBlockingQueue: boost::noncopyable
{
public:
    explicit BoundedBlockingQueue(int maxSize)
     : mutex_(),
       notEmpty_(mutex_),
       notFull_(mutex_),
       queue_(maxSize)
    {

    }
    void put(const T& x) {
        MutexLockGuard lock(mutex_);
        while(queue_.full()) {
            notFull_.wait();
        }
        queue_.push_back(x);
        notEmpty_.notify();
    }
    T take() {
        MutexLockGuard lock(mutex_);
        while(queue_.empty()) {
            notEmpty_.wait();
        }
        T front(queue_.front());
        queue_.pop_front();
        return front;
    }
    bool empty() {
        MutexLockGuard lock(mutex_);
        return queue_.empty();
    }
    bool full() {
        MutexLockGuard lock(mutex_);
        return queue_.full();
    }
    size_t size() {
        MutexLockGuard lock(mutex_);
        return queue_.size();
    }
    size_t capacity() {
        MutexLockGuard lock(mutex_);
        return queue_.capacity();
    }
private:
    mutable MutexLock mutex_;
    Condition notEmpty_;
    Condition notFull_;
    boost::circular_buffer<T> queue_;
};
}

#endif //MUDUO_BASE_BOUNDEDBLOCKINGQUEUE_H