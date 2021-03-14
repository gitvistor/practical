#pragma once
#include "wheel_timer.h"

class time_wheel
{
public:
    time_wheel();
    ~time_wheel();
    tw_timer *add_timer(int);
    void del_timer(tw_timer *);
    void tick();

private:
    static const int N = 60;
    static const int SI = 1;
    tw_timer *slots[N];
    int cur_slot;
};