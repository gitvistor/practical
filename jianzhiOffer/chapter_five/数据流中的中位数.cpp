#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <random>
#include <ctime>

using namespace std;

template <typename T>
class DynamicArray
{
public:
	void Insert(T num)
	{
		if (((min.size() + max.size()) & 1) == 0)
		{
			if (max.size() > 0 && num < max[0])
			{
				max.push_back(num);
				std::push_heap(max.begin(), max.end(), less<T>());

				num = max[0];
				
				pop_heap(max.begin(), max.end(), less<T>());
				max.pop_back();
			}

			min.push_back(num);
			push_heap(min.begin(), min.end(), greater<T>());
		}
		else
		{
			if (min.size() > 0 && min[0] < num)
			{
				min.push_back(num);
				std::push_heap(min.begin(), min.end(), greater<T>());

				num = min[0];
				
				pop_heap(min.begin(), min.end(), greater<T>());
				min.pop_back();
			}

			max.push_back(num);
			push_heap(max.begin(), max.end(), less<T>());
		}
	}

	T GetMedian()
	{
		int size = min.size() + max.size();
		if (size == 0)
			throw "no numbers available";

		T median = 0;
		if ((size & 1) == 1)
			median = min[0];
		else
			median = (min[0] + max[0]) / 2;

		return median;
	}

	void PrintNumber()
	{
		std::cout << "max vector: ";
		for (auto iter = max.begin(); iter != max.end(); ++iter)
			std::cout << *iter << ' ';

		std::cout << "\nmin vector: ";
		for (auto iter = min.begin(); iter != min.end(); ++iter)
			std::cout << *iter << ' ';

		std::cout << "\nmedian: " << GetMedian() << endl;
	}

private:
	std::vector<T> min;
	std::vector<T> max;
};

#define LOW 10
#define HIGH 100
#define NUM 10

int main(int argc, const char *argv[])
{
	std::default_random_engine e(time(0));
	std::uniform_int_distribution<> u(10, 100);
	DynamicArray<int> array;

	for (auto i = 0; i < NUM; i++)
		array.Insert(u(e));

	array.PrintNumber();

	return 0;
}
