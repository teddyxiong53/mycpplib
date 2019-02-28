#ifndef MUDUO_NET_SOCKET_H
#define MUDUO_NET_SOCKET_H

#include <boost/noncopyable.hpp>

namespace muduo
{
class InetAddress;

class Socket: boost::noncopyable
{
public:
    explicit Socket(int sockfd): sockfd_(sockfd) {

    }
    ~Socket();
    int fd() {
        return sockfd_;
    }
    void bindAddress(const InetAddress& localAddr);
    void listen();
    int accept(InetAddress* peerAddr);
    void setReuseAddr(bool on);

private:
    const int sockfd_;
};
} // muduo


#endif //MUDUO_NET_SOCKET_H