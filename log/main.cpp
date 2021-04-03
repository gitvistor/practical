#include "Logger.h"
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <random>

using namespace std;

void run(int i)
{
	static std::default_random_engine e(time(nullptr));
	std::uniform_int_distribution<> u(0, 4);
	std::string str{"hello"};

	for (;;)
	{
		switch (u(e))
		// switch (i)
		{
		case 0:
			LOG_DEBUG << "run... " << 0 << ' ' << true;
			break;
		case 1:
			LOG_INFO << "run... " << 1.23 << ' ' << false;
			break;
		case 2:
			LOG_WARN << "run... " << -0 << ' ' << -5;
			break;
		case 3:
			LOG_ERROR << "run... " << str << ' ' << 9;
			break;
		case 4:
			LOG_FATAL << "run... " << -4.5f << ' ' << true;
			break;
		default:
			break;
		}

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

#define THREAD_NUM 5

int main(int argc, const char *argv[])
{
	Logger::getInstance()->setLogLevel(LOG_LEVEL::DEBUG);

	std::vector<std::thread> vec;
	for (int i = 0; i < THREAD_NUM; i++)
		vec.emplace_back(run, i);

	std::for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));

	// std::string str{"hello"};
	// for (;;)
	// {
		// LOG_DEBUG << "run... " << 0 << ' ' << true;
		// LOG_INFO << "run... " << 1.23 << ' ' << false;
	// 	LOG_WARN << "run... " << '2' << ' ' << -5;
	// 	LOG_ERROR << "run... " << str << ' ' << 9;
	// 	LOG_FATAL << "run... " << -4.5f << ' ' << true;
	// 	std::this_thread::sleep_for(std::chrono::seconds(1));
	// }

	return 0;
}
