#pragma once
#include <ctime>
#include <netinet/in.h>

#define BUFFER_SIZE 64
class tw_timer;

struct client_data
{
    sockaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    tw_timer *timer;
};

class tw_timer
{
public:
    tw_timer(int rot, int ts) : prev(nullptr), next(nullptr), rotation(rot), slot(ts)
    {
    }

public:
    int rotation;
    int slot;
    void (*cb_func)(client_data *);
    client_data *user_data;
    tw_timer *prev;
    tw_timer *next;
};