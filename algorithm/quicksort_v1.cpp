#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int Partition(int data[], int length, int start, int end)
{
	if (!data || length <= 0 || start < 0 || end >= length)
		return -1;

	std::default_random_engine engine(time(0));
	std::uniform_int_distribution<unsigned> distribution(start, end);

	int index = distribution(engine);
	std::swap(data[index], data[end]);

	int small = start - 1;
	for (index = start; index < end; ++index)
	{
		if (data[index] < data[end])
		{
			++small;
			if (small != index)
				std::swap(data[index], data[small]);
		}
	}
	++small;
	std::swap(data[small], data[end]);
	return small;
}

void QuickSort(int data[], int length, int start, int end)
{
	if (start >= end)
		return;
	
	int index = Partition(data, length, start, end);
	if (index > start)
		QuickSort(data, length, start, index - 1);
	
	if (index < end)
		QuickSort(data, length, index + 1, end);
}

int main(int argc, char *argv[])
{
	int array[] = {8, 3, 2, 7, 5, 4};
	int length = sizeof(array) / sizeof(int);
	std::cout << "before QuickSort: ";
	for (auto e : array)
		std::cout << e << ' ';
	std::cout << std::endl;

	QuickSort(array, length, 0, length - 1);
	std::cout << "after QuickSort: ";
	for (auto e : array)
		std::cout << e << ' ';
	std::cout << std::endl;

	cout << endl;
	return 0;
}
