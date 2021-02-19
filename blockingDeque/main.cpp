
#include "BlockingDeque.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <ctime>
#include <random>

#define THREAD_NUM 4
#define DEQUE_SIZE 200
#define BUF_SIZE 64
#define WAIT_SECONDS 5
#define SLEEP_SECONDS 30

using namespace std;

int main(int argc, char **argv)
{
	std::default_random_engine random(time(NULL));
	std::uniform_int_distribution<int> distributor(1, 100);

	BlockingDeque<int> intDeque;

	std::vector<std::thread> vecProducer;
	std::vector<std::thread> vecComsumer;

	for (auto i = 0; i < THREAD_NUM; i++)
	{
		vecProducer.emplace_back([&intDeque, &random, &distributor, i]() {
			if (i & 1)
			{
				while (true)
				{
					auto item = distributor(random);
					if (!intDeque.push_back(item))
						break;
					char buf[BUF_SIZE] = {0};
					snprintf(buf, sizeof(buf), "thread %u push_back %d\n", std::this_thread::get_id(), item);
					std::cout << buf;
					//low cpu load
					//std::this_thread::sleep_for(std::chrono::seconds(1));
				}
			}
			else
			{
				while (true)
				{
					auto item = distributor(random);
					if (!intDeque.push_front(item))
						break;
					char buf[BUF_SIZE] = {0};
					snprintf(buf, sizeof(buf), "thread %u push_front %d\n", std::this_thread::get_id(), item);
					std::cout << buf;
					//low cpu load
					//std::this_thread::sleep_for(std::chrono::seconds(1));
				}
			}
		});
	}

	for (auto i = 0; i < THREAD_NUM; i++)
	{
		vecComsumer.emplace_back([&intDeque, i]() {
			if (i & 1)
			{
				while (true)
				{
					int item;
					// if (!intDeque.pop_back(item, WAIT_SECONDS))
					if (!intDeque.pop_back(item))
						break;
					char buf[BUF_SIZE] = {0};
					snprintf(buf, sizeof(buf), "thread %u pop_back %d\n", std::this_thread::get_id(), item);
					std::cout << buf;
				}
			}
			else
			{
				while (true)
				{
					int item;
					// if (!intDeque.pop_front(item, WAIT_SECONDS))
					if (!intDeque.pop_front(item))
						break;
					char buf[BUF_SIZE] = {0};
					snprintf(buf, sizeof(buf), "thread %u pop_front %d\n", std::this_thread::get_id(), item);
					std::cout << buf;
				}
			}
		});
	}

	std::this_thread::sleep_for(std::chrono::seconds(SLEEP_SECONDS));
	intDeque.close();

	std::for_each(vecProducer.begin(), vecProducer.end(), [](std::thread &t) {
		t.join();
	});

	std::for_each(vecComsumer.begin(), vecComsumer.end(), [](std::thread &t) {
		t.join();
	});

	std::cout << "main thread closed deque after sleep " << SLEEP_SECONDS << "s\n";

	return 0;
}
