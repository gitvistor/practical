
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <algorithm>
#include <condition_variable>
#include <stdexcept>
#include <chrono>
#include <atomic>
#include <memory>

using namespace std;

#define MAX_THREADS 100
#define THREAD_NUM 10
#define TASK_NUM 20
#define BUF_LEN 64

class Task
{
public:
	Task() = default;
	void process()
	{
		char buf[BUF_LEN] = {0};
		snprintf(buf, sizeof(buf), "thread %u run...\n", std::this_thread::get_id());
		std::cout<< buf;
	}
};

template <typename T>
class threadPool
{
public:
	threadPool(int number);
	~threadPool();
	void append(std::shared_ptr<T>&& request);

private:
	void worker(void *arg);
	void run();

private:
	std::vector<std::thread> work_threads;
	std::queue<std::shared_ptr<T>> tasks;
	std::mutex mtx;
	std::condition_variable condition;
	std::atomic<bool> stop;
};

template <typename T>
threadPool<T>::threadPool(int number)
{
	stop = false;
	if (number <= 0 || number > MAX_THREADS)
		throw std::exception();

	for (auto i = 0; i < number; i++)
	{
		work_threads.emplace_back(&threadPool<T>::worker, this, this);
	}
}

template <typename T>
threadPool<T>::~threadPool()
{
	stop = true;
	condition.notify_all();
	std::for_each(work_threads.begin(), work_threads.end(), [](thread &e) { e.join(); });
}

template <typename T>
void threadPool<T>::append(std::shared_ptr<T>&& request)
{
	mtx.lock();
	tasks.push(std::move(request));
	mtx.unlock();
	condition.notify_one();
}

template <typename T>
void threadPool<T>::worker(void *arg)
{
	threadPool *pool = static_cast<threadPool *>(arg);
	// threadPool<T> *pool = static_cast<threadPool<T> *>(arg);
	pool->run();
}

template <typename T>
void threadPool<T>::run()
{
	while (true)
	{
		std::shared_ptr<T> request;
		{
			std::unique_lock<std::mutex> lock(mtx);
			condition.wait(lock, [this] {
				return !tasks.empty() || stop;
			});

			if (stop)
				break;

			request = tasks.front();
			tasks.pop();
		}
		if (request)
		{
			request->process();
		}
	}
}

int main(int argc, char *argv[])
{
	{
		threadPool<Task> pool(THREAD_NUM);
		int i = 0;
		while (i++ < TASK_NUM)
		{
			auto task = std::make_shared<Task>();
			pool.append(std::move(task));
			std::this_thread::sleep_for(std::chrono::seconds{1});
		}
	}
	std::cout<<"main over"<<std::endl;
	return 0;
}
