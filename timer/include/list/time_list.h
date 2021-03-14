#pragma once
#include "list_timer.h"

class sort_timer_lst
{
public:
    sort_timer_lst();
    ~sort_timer_lst();
    void add_timer(util_timer *);
    void adjust_timer(util_timer *);
    void del_timer(util_timer *);
    void tick();

private:
    void add_timer(util_timer *, util_timer *);
    util_timer *head;
    util_timer *tail;
};