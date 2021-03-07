#pragma once

#include <iostream>
#include <netinet/in.h>
#include <ctime>

const int BUFFER_SIZE = 1024;
class heap_timer;

struct client_data
{
    struct sockaddr_in addr;
    int sockfd;
    char buf[BUFFER_SIZE];
    heap_timer *timer;
};

class heap_timer
{
public:
    heap_timer(int delay)
    {
        time_t now = time(NULL);
        std::cout << "create time: " << now << ", delay: " << delay << std::endl;
        expire = now + delay;
    }
    
    void update_time(int delay)
    {
        time_t now = time(NULL);
        std::cout << "update time: " << now << ", delay: " << delay << std::endl;
        expire = now + delay;
    }
    
    void (*timeout_callback)(client_data *);

public:
    time_t expire;
    client_data *user_data;
};