#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <atomic>

#define BUF_LEN 64
using Task = std::function<void()>;

class Timer
{
public:
    Timer() : stopped(false)
    {
    }
    void startPeriod(unsigned int period, Task && task)
    {
        if (!task)
            return;

        std::thread([this, period, task]() {
            while (true)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds{period});
                if (stopped)
                    break;
                task();
            }
        }).detach();
    }
    void startOnce(unsigned int delay, Task && task)
    {
        if (!task)
            return;

        std::thread([this, delay, task] {
            std::this_thread::sleep_for(std::chrono::milliseconds{delay});
            if (stopped)
                return;
            task();
        }).detach();
    }
    void stop()
    {
        stopped = true;
    }

private:
    std::atomic<bool> stopped;
};

void func1()
{
    char buf[BUF_LEN] = {0};
    snprintf(buf, sizeof(buf), "thread %u trigger func1\n", std::this_thread::get_id());
    std::cout << buf;
}

void func2(int x)
{
    char buf[BUF_LEN] = {0};
    snprintf(buf, sizeof(buf), "thread %u trigger func2, x=%d\n", std::this_thread::get_id(), x);
    std::cout << buf;
}

int main(int argc, char *argv[])
{
    Timer timer;
    timer.startPeriod(1000, std::bind(func1));
    std::cout << "timer started" << std::endl;
    timer.startOnce(2000, std::bind(func2, 2));
    timer.startOnce(4000, std::bind(func2, 3));
    getchar();
    timer.stop();
    std::cout << "timer stopped" << std::endl;
    return 0;
}