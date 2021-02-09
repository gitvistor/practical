
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <algorithm>

using namespace std;

class Singleton
{
	public:
	static Singleton* GetInstance()
	{
		static Singleton instance;
		return &instance;
	}

private:
	Singleton() = default;
	Singleton(const Singleton &) = delete;
	Singleton &operator=(const Singleton &) = delete;
};

class Singleton_Helper
{
public:
	static Singleton_Helper *GetInstance()
	{
		static Singleton_Helper instance;
		return &instance;
	}

	struct Object_Creator
	{
		Object_Creator()
		{
			Singleton_Helper::GetInstance();
		}
	};

private:
	static Object_Creator _object_creator;

private:
	Singleton_Helper() = default;
	Singleton_Helper(const Singleton_Helper &) = delete;
	Singleton_Helper &operator=(const Singleton_Helper &) = delete;
};

Singleton_Helper::Object_Creator _object_creator;

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
			// snprintf(buf, sizeof(buf), "GetInstance thread:%d, create object addr:%x\n", std::this_thread::get_id(), static_cast<void *>(Singleton_Helper::GetInstance()));
			// cout << buf;
		}));
	}

	std::for_each(vec.begin(), vec.end(), std::mem_fn(std::thread::join));

	return 0;
}
