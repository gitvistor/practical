
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <algorithm>
#include <functional>

using namespace std;

template <typename T>
class Singleton
{
public:
	template <typename... Args>
	static shared_ptr<T> GetInstance(Args &&... args)
	{
		static std::once_flag on_flag;
		std::call_once(on_flag, [&]() {
			// instance.reset(new T(std::forward<Args>(args)...));
			instance = std::make_shared<T>(std::forward<Args>(args)...);
		});

		return instance;
	}

private:
	explicit Singleton() = default;
	Singleton(const Singleton &) = delete;
	Singleton &operator=(const Singleton &) = delete;

private:
	static std::shared_ptr<T> instance;
};

template <typename T>
std::shared_ptr<T> Singleton<T>::instance;

class TestObject
{
public:
	TestObject(int a) : m(a)
	{
		cout << "TestObject m=" << m << endl;
	}

private:
	int m;
};

#define THREAD_NUM 10

int main(int argc,char*argv[])
{
	std::vector<std::thread> vec;
	vec.reserve(THREAD_NUM);
	for (auto i = 0; i < THREAD_NUM; i++)
	{
		vec.emplace_back(std::move([i]() {
			char buf[64] = {0};
			// snprintf(buf, sizeof(buf), "GetInstance thread:%d, create object addr:%x\n", std::this_thread::get_id(), static_cast<void *>(Singleton<int>::GetInstance().get()));
			// cout<<buf;
			snprintf(buf, sizeof(buf), "GetInstance thread:%d, create object addr:%x\n", std::this_thread::get_id(), static_cast<void *>(Singleton<TestObject>::GetInstance(i).get()));
			cout<<buf;
		}));
	}

	std::for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));

	return 0;
}