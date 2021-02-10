
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <algorithm>
#include <condition_variable>
#include <stdexcept>
#include <chrono>
#include <functional>
#include <atomic>
#include <memory>

using namespace std;

#define MAX_THREADS 100
#define THREAD_NUM 10
#define TASK_NUM 20
#define BUF_LEN 64

using Task = std::function<void(void)>;

class threadPool
{
public:
	threadPool(int);
	~threadPool();
	void append(Task &&);

private:
	void worker(void *);
	void run();

private:
	std::vector<std::thread> work_threads;
	std::queue<Task> task_queue;
	std::mutex mtx;
	std::condition_variable condition;
	std::atomic<bool> stop;
};

threadPool::threadPool(int number)
{
	if (number <= 0 || number >= MAX_THREADS)
		throw std::exception();

	stop = false;
	for (auto i = 0; i < number; i++)
	{
		work_threads.emplace_back(&threadPool::worker, this, this);
	}
}

threadPool::~threadPool()
{
	stop = true;
	condition.notify_all();
	for_each(work_threads.begin(), work_threads.end(), [](thread &e) { e.join(); });
}

void threadPool::append(Task &&task)
{
	mtx.lock();
	task_queue.push(std::move(task));
	mtx.unlock();
	condition.notify_one();
}

void threadPool::worker(void *arg)
{
	auto pool = static_cast<threadPool *>(arg);
	pool->run();
}

void threadPool::run()
{
	while (true)
	{
		Task task;
		{
			std::unique_lock<std::mutex> lock(mtx);
			condition.wait(lock, [this]() {
				return !task_queue.empty() || stop;
			});

			if (stop)
				break;

			task = task_queue.front();
			task_queue.pop();
		}
		if (task)
			task();
	}
}

struct Object
{
public:
	void operator()()
	{
		char buf[BUF_LEN] = {0};
		snprintf(buf, sizeof(buf), "thread %u Object operator, no args\n", std::this_thread::get_id());
		cout << buf;
	}

	void operator()(int m)
	{
		char buf[BUF_LEN] = {0};
		snprintf(buf, sizeof(buf), "thread %u Object operator, one args: %d\n", std::this_thread::get_id(), m);
		cout << buf;
	}

	void fun(int m, int n)
	{
		char buf[BUF_LEN] = {0};
		snprintf(buf, sizeof(buf), "thread %u Object fun, two args: %d %d\n", std::this_thread::get_id(), m, n);
		cout << buf;
	}
};

void fun()
{
	char buf[BUF_LEN] = {0};
	snprintf(buf, sizeof(buf), "thread %u normal fun, no args\n", std::this_thread::get_id());
	cout << buf;
}

void fun2(int m)
{
	char buf[BUF_LEN] = {0};
	snprintf(buf, sizeof(buf), "thread %u normal fun2, one args: %d\n", std::this_thread::get_id(), m);
	cout << buf;
}

int main(int argc, char *argv[])
{
	threadPool pool(THREAD_NUM);
	Object object;
	int i = 0;
	while (i++ < TASK_NUM)
	{
		pool.append(std::bind(Object()));
		pool.append(std::bind(Object(), 2));
		pool.append(std::bind(&Object::fun, &object, 3, 4));
		pool.append(fun);
		pool.append(std::bind(fun2,5));
		std::this_thread::sleep_for(std::chrono::seconds{1});
	}
	std::cout << "main over" << std::endl;
	return 0;
}
