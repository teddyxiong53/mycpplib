#include "Poller.h"
#include "Channel.h"
#include "logging/Logging.h"

#include <assert.h>
#include <poll.h>

using namespace muduo;

Poller::Poller(EventLoop *loop)
 : ownerLoop_(loop)
{

}

Poller::~Poller() {

}

Timestamp Poller::poll(int timeoutMs, ChannelList *activeChannels)
{
    int numEvents = ::poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);
    Timestamp now(Timestamp::now());
    if(numEvents > 0) {
        LOG_TRACE << numEvents << " events happened";
        fillActiveChannels(numEvents, activeChannels);
    } else if(numEvents == 0) {
        LOG_TRACE << " nothing happended";
    } else {
        LOG_SYSERR << "Poller:poll()";
    }
    return now;
}

void Poller::fillActiveChannels(int numEvents, ChannelList *activeChannels)
{
    for(PollFdList::const_iterator pfd = pollfds_.begin();
        pfd != pollfds_.end() && numEvents > 0; pfd++) {
        if(pfd->revents > 0) {
            numEvents --;
            ChannelMap::const_iterator ch = channels_.find(pfd->fd);
            Channel *channel = ch->second;
            channel->set_revents(pfd->revents);
            activeChannels->push_back(channel);
        }
    }
}

void Poller::updateChannel(Channel *channel)
{
    assertInLoopThread();
    LOG_TRACE << "fd = " << channel->fd() << " events = " << channel->events();
    if(channel->index() < 0) {
        // a new one
        struct pollfd pfd;
        pfd.fd = channel->fd();
        pfd.events = static_cast<short>(channel->events());
        pfd.revents = 0;
        pollfds_.push_back(pfd);
        int idx = static_cast<int>(pollfds_.size()) - 1;
        channel->set_index(idx);
        channels_[pfd.fd] = channel;
    } else {
        //update existing one
        int idx = channel->index();
        struct pollfd& pfd = pollfds_[idx];
        pfd.events = static_cast<short>(channel->events());
        pfd.revents = 0;
        if(channel->isNoneEvent()) {
            pfd.fd = -1;
        }
    }
}

