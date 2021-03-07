#pragma once

#include "heap_timer.h"

class time_heap
{
public:
    time_heap(int cap);

    time_heap(heap_timer **init_array, int size, int cap);

    ~time_heap();

    void add_timer(heap_timer *timer);

    void adjust_heap();

    void adjust_timer(heap_timer *old_timer, heap_timer *new_timer);

    void del_timer(heap_timer *timer);

    heap_timer *top() const;

    void pop_timer();

    void tick();

    bool emtpy() const;

private:
    void shift_down(int hole);

    void resize();

private:
    heap_timer **array;
    int capacity;
    int cur_size;
};