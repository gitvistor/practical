#include "log.h"
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
	std::uniform_int_distribution<> u(1, 5);
	switch (u(e))
	{
	case 1:
		LOG_FATAL("run...");
		break;
	case 2:
		LOG_ERROR("run...");
		break;
	case 3:
		LOG_Warning("run...");
		break;
	case 4:
		LOG_Debug("run...");
		break;
	case 5:
		LOG_INFO("run...");
		break;
	default:
		break;
	}
}

int main(int argc, const char *argv[])
{
	std::vector<std::thread> vec;
	for (int i = 1; i <= 5; i++)
		vec.emplace_back(run, i);

	std::for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join));

	return 0;
}
