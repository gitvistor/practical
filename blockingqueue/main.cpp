
#include "BlockingQueue.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <ctime>
#include <random>

#define THREAD_NUM 5
#define QUEUE_SIZE 200
#define BUF_SIZE 64
#define WAIT_SECONDS 10
#define SLEEP_SECONDS 10

using namespace std;

int main(int argc, char **argv)
{
	std::default_random_engine random(time(NULL));
	std::uniform_int_distribution<int> distributor(1, 100);

	BlockingQueue<int> intQueue;

	std::vector<std::thread> vecProducer;
	std::vector<std::thread> vecComsumer;

	for (auto i = 0; i < THREAD_NUM; i++)
	{
		vecProducer.emplace_back([&intQueue, &random, &distributor]() {
			while (true)
			{
				auto item = distributor(random);
				if (!intQueue.put(item))
					break;
				char buf[BUF_SIZE] = {0};
				snprintf(buf, sizeof(buf), "thread %u put %d\n", std::this_thread::get_id(), item);
				std::cout << buf;
				//low cpu load
				//std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		});
	}

	for (auto i = 0; i < THREAD_NUM; i++)
	{
		vecComsumer.emplace_back([&intQueue]() {
			while (true)
			{
				int item;
				// if (!intQueue.take(item, WAIT_SECONDS))
				if (!intQueue.take(item))
					break;
				char buf[BUF_SIZE] = {0};
				snprintf(buf, sizeof(buf), "thread %u take %d\n", std::this_thread::get_id(), item);
				std::cout << buf;
			}
		});
	}

	std::this_thread::sleep_for(std::chrono::seconds(SLEEP_SECONDS));
	intQueue.close();

	std::for_each(vecProducer.begin(), vecProducer.end(), [](std::thread &t) {
		t.join();
	});

	std::for_each(vecComsumer.begin(), vecComsumer.end(), [](std::thread &t) {
		t.join();
	});

	std::cout << "main thread closed queue after sleep " << SLEEP_SECONDS << "s\n";

	return 0;
}
