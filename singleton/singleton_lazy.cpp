
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <algorithm>

using namespace std;

class Singleton
{
public:
	static Singleton *GetInstance()
	{
		if (!instance)
		{
			std::lock_guard<std::mutex> lock(mtx);
			if (!instance)
			{
				instance = new Singleton;
			}
		}
		return instance;
	}

	class Collector
	{
	public:
		Collector() = default;
		~Collector()
		{
			if (Singleton::instance)
			{
				char buf[64] = {0};
				snprintf(buf, sizeof(buf), "Collector thread:%d, destroy object addr:%x\n", std::this_thread::get_id(), static_cast<void *>(Singleton::instance));
				cout << buf;
				delete Singleton::instance;
				Singleton::instance = nullptr;
			}
		}
	};

	static Collector collector;

	Singleton(const Singleton &) = delete;
	Singleton &operator=(const Singleton &) = delete;

private:
	Singleton() = default;

private:
	static std::mutex mtx;
	static Singleton *instance;
};

std::mutex Singleton::mtx;
Singleton* Singleton::instance = nullptr;
Singleton::Collector Singleton::collector;

#define THREAD_NUM 10

int main(int argc,char*argv[])
{
	std::vector<std::thread> vec;
	vec.reserve(THREAD_NUM);
	for (auto i = 0; i < THREAD_NUM; i++)
	{
		vec.emplace_back(std::move([]() {
			char buf[64] = {0};
			snprintf(buf, sizeof(buf), "GetInstance thread:%d, create object addr:%x\n", std::this_thread::get_id(), static_cast<void *>(Singleton::GetInstance()));
			cout << buf;
		}));
	}

	std::for_each(vec.begin(), vec.end(), std::mem_fn(std::thread::join));

	return 0;
}
