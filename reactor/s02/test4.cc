#include "EventLoop.h"

#include <boost/bind.hpp>
#include <stdio.h>

muduo::EventLoop *g_loop;
int cnt = 0;

void printTid()
{
    printf("pid = %d, tid = %d\n", getpid(), muduo::CurrentThread::tid());
    printf("now :%s \n", muduo::Timestamp::now().toString().c_str());
}

void print(const char *msg)
{
    printf("msg %s %s \n", muduo::Timestamp::now().toString().c_str(), msg);
    if(cnt++ == 20) {
        g_loop->quit();
    }
}
int main()
{
    printTid();
    muduo::EventLoop loop;
    g_loop = &loop;
    print("main");
    loop.runAfter(1, boost::bind(print, "once1"));
    loop.runAfter(1.5, boost::bind(print, "once1.5"));
    loop.runEvery(2, boost::bind(print, "every2"));
    loop.runEvery(3, boost::bind(print, "every3"));
    loop.loop();
    printf("main loop exit\n");
    sleep(1);
}