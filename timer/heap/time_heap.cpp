
#include "time_heap.h"
#include <cstring>

time_heap::time_heap(int cap)
    : array(new heap_timer *[cap]), capacity(cap), cur_size(0)
{
    memset(array, 0, sizeof(array));
}

time_heap::time_heap(heap_timer **init_array, int size, int cap)
    : array(new heap_timer *[cap]), capacity(cap), cur_size(size)
{
    memset(array, 0, sizeof(array));

    for (int i = 0; i < cur_size; i++)
    {
        array[i] = init_array[i];
    }

    adjust_heap();
}

time_heap::~time_heap()
{
    for (int i = 0; i < cur_size; i++)
    {
        delete array[i];
    }
    delete[] array;
}

void time_heap::add_timer(heap_timer *timer)
{
    if (cur_size >= capacity)
        resize();

    int hole = cur_size++;
    int parent = 0;
    for (; hole > 0; hole = parent)
    {
        parent = (hole - 1) >> 1;
        if (array[parent]->expire <= timer->expire)
            break;
        array[hole] = array[parent];
    }
    array[hole] = timer;
}

void time_heap::adjust_heap()
{
    if(cur_size <= 0)
        return;

    for (int i = (cur_size - 1) >> 1; i >= 0; i--)
    {
        shift_down(i);
    }
}

void time_heap::adjust_timer(heap_timer *old_timer, heap_timer *new_timer)
{
    del_timer(old_timer);
    add_timer(new_timer);
}

void time_heap::del_timer(heap_timer *timer)
{
    timer->timeout_callback = nullptr;
}

heap_timer *time_heap::top() const
{
    return cur_size > 0 ? array[0] : nullptr;
}

void time_heap::pop_timer()
{
    if (cur_size <= 0)
    {
        return;
    }

    std::cout << "delete user: " << array[0]->user_data->sockfd << std::endl;
    delete array[0];
    array[0] = array[--cur_size];

    std::cout << "cur_size: " << cur_size << std::endl;
    shift_down(0);
}

void time_heap::tick()
{
    time_t cur = time(NULL);
    while (cur_size > 0)
    {
        heap_timer *tmp = array[0];
        if (!tmp)
            break;

        std::cout << "current time is: " << cur << std::endl;
        if (tmp->expire > cur)
            break;

        if (tmp->timeout_callback)
        {
            tmp->timeout_callback(tmp->user_data);
        }

        pop_timer();
        tmp = array[0];
    }
}

bool time_heap::emtpy() const
{
    return cur_size == 0;
}

void time_heap::shift_down(int hole)
{
    heap_timer *tmp = array[hole];
    int child;
    for (; 2 * hole + 1 < cur_size; hole = child)
    {
        child = 2 * hole + 1;
        if (child + 1 < cur_size && array[child]->expire > array[child + 1]->expire)
        {
            child++;
        }

        if (array[child]->expire > tmp->expire)
            break;

        array[hole] = array[child];
    }
    array[hole] = tmp;
}

void time_heap::resize()
{
    capacity = capacity << 1;
    heap_timer **tmp = new heap_timer *[capacity];
    memset(tmp, 0, sizeof(tmp));

    for (int i = 0; i < cur_size; i++)
    {
        tmp[i] = array[i];
    }

    delete[] array;
    array = tmp;
}