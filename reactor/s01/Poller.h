#ifndef MUDUO_NET_POLLER_H
#define MUDUO_NET_POLLER_H
#include <map>
#include <vector>
#include "datetime/Timestamp.h"
#include "EventLoop.h"

struct pollfd;
namespace muduo
{
class Channel;
class Poller: boost::noncopyable
{
public:
    typedef std::vector<Channel*> ChannelList;
    Poller(EventLoop *loop);
    ~Poller();

    Timestamp poll(int timeoutMs, ChannelList *activeChannels);
    void updateChannel(Channel * channel);
    void assertInLoopThread() {
        ownerLoop_->assertInLoopThread();
    }
private:
    typedef std::vector<struct pollfd> PollFdList;
    typedef std::map<int, Channel*> ChannelMap;
    EventLoop *ownerLoop_;
    PollFdList pollfds_;
    ChannelMap channels_;

    void fillActiveChannels(int numEvents, ChannelList *activeChannels);
};
} // muduo

#endif //MUDUO_NET_POLLER_H