
#include "time_wheel.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>

#define FD_LIMIT 100
#define MAX_EVENT_NUNBER 1024
#define TIME_SHOT 1
#define INTERVAL 15

static int pipefd[2];
static int epollfd = 0;
static time_wheel timerlist;

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void addfd(int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

void sig_handler(int sig)
{
    int save_errno = errno;
    send(pipefd[1], (char *)&sig, 1, 0);
    errno = save_errno;
}

void addsig(int sig)
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

void timer_handler()
{
    timerlist.tick();
    alarm(TIME_SHOT);
}

void time_callback(client_data *user_data)
{
    assert(user_data);
    epoll_ctl(epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);
    close(user_data->sockfd);
    std::cout << "close " << user_data->sockfd << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "usage: " << basename(argv[0]) << " ip_address port_number" << std::endl;
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    int ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUNBER];
    epollfd = epoll_create(5);
    assert(epollfd != -1);

    addfd(listenfd);

    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
    assert(ret != -1);

    setnonblocking(pipefd[1]);
    addfd(pipefd[0]);

    addsig(SIGALRM);
    addsig(SIGTERM);
    addsig(SIGINT);

    bool stop_server = false;
    client_data *users = new client_data[FD_LIMIT];
    bool timeout = false;
    alarm(TIME_SHOT);

    while (!stop_server)
    {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUNBER, -1);
        if (number < 0 && errno != EINTR)
        {
            std::cout << "epoll failure\n";
            break;
        }

        for (int i = 0; i < number; i++)
        {
            int sockfd = events[i].data.fd;
            if (sockfd == listenfd)
            {
                struct sockaddr_in client_address;
                socklen_t client_addrLength = sizeof(client_address);
                int connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrLength);
                addfd(connfd);
                users[connfd].address = client_address;
                users[connfd].sockfd = connfd;
                std::cout << "accept user: " << connfd << std::endl;
                tw_timer *timer = timerlist.add_timer(INTERVAL);
                timer->user_data = &users[connfd];
                timer->cb_func = time_callback;
                users[connfd].timer = timer;
            }
            else if (sockfd == pipefd[0] && events[i].events & EPOLLIN)
            {
                int sig;
                char signals[1024];
                ret = recv(pipefd[0], signals, sizeof(signals), 0);
                if (ret == 0 || ret == -1)
                    continue;
                else
                {
                    for (int i = 0; i < ret; i++)
                    {
                        switch (signals[i])
                        {
                        case SIGALRM:
                        {
                            timeout = true;
                            break;
                        }
                        case SIGTERM:
                        case SIGINT:
                        {
                            stop_server = true;
                            std::cout << "\nexit loop" << std::endl;
                            break;
                        }
                        }
                    }
                }
            }
            else if (events[i].events & EPOLLIN)
            {
                memset(users[sockfd].buf, '\0', BUFFER_SIZE);
                ret = recv(sockfd, users[sockfd].buf, BUFFER_SIZE - 1, 0);
                std::cout << "get " << ret << " bytes from client " << sockfd << ", data: " << users[sockfd].buf;
                tw_timer *timer = users[sockfd].timer;
                if (ret < 0)
                {
                    if (errno != EAGAIN)
                    {
                        time_callback(&users[sockfd]);
                        if (timer)
                        {
                            timerlist.del_timer(timer);
                        }
                    }
                }
                else if (ret == 0)
                {
                    time_callback(&users[sockfd]);
                    if (timer)
                    {
                        timerlist.del_timer(timer);
                    }
                }
                else
                {
                }
            }
            else
            {
            }
        }

        if (timeout)
        {
            timer_handler();
            timeout = false;
        }
    }

    close(listenfd);
    close(pipefd[1]);
    close(pipefd[0]);

    std::cout << "main over" << std::endl;

    return 0;
}