#include <iostream>
#include <random>
#include <ctime>
using namespace std;

bool g_bInputInvalid = false;
bool CheckInvalidArray(int *numbers, int length)
{
	g_bInputInvalid = false;
	if (!numbers || length <= 0)
		g_bInputInvalid = true;

	return g_bInputInvalid;
}

bool CheckMoreThanHalf(int *numbers, int length, int number)
{
	int times = 0;
	for (int i = 0; i < length; i++)
	{
		if (numbers[i] == number)
			times++;
	}

	bool isMoreThanHalf = true;
	if (times * 2 <= length)
	{
		g_bInputInvalid = true;
		isMoreThanHalf = false;
	}
	return isMoreThanHalf;
}

int Partition(int *data, int length, int start, int end)
{
	if (!data || length <= 0 || start < 0 || end >= length)
	{
		g_bInputInvalid = true;
		return 0;
	}

	static std::default_random_engine e(time(0));
	std::uniform_int_distribution<> u(start, end);

	int index = u(e);
	std::swap(*(data + index), *(data + end));

	int small = start - 1;
	for (index = start; index < end; ++index)
	{
		if (data[index] < data[end])
		{
			++small;
			if (small != index)
				std::swap(*(data + index), *(data + small));
		}
	}
	++small;
	std::swap(*(data + small), *(data + end));

	return small;
}

int MoreThanHalfNum(int *numbers, int length)
{
	if (CheckInvalidArray(numbers, length))
		return 0;

	int middle = length >> 1;
	int start = 0;
	int end = length - 1;
	int index = Partition(numbers, length, start, end);
	while (index != middle)
	{
		if (index > middle)
		{
			end = index - 1;
			index = Partition(numbers, length, start, end);
		}
		else
		{
			start = index + 1;
			index = Partition(numbers, length, start, end);
		}
	}

	int result = numbers[middle];
	if (!CheckMoreThanHalf(numbers, length, result))
		return 0;

	return result;
}

int MoreThanHalfNum_V2(int *numbers, int length)
{
	if (CheckInvalidArray(numbers, length))
		return 0;

	int result = numbers[0];
	int times = 1;
	for (int i = 1; i < length; i++)
	{
		if (times == 0)
		{
			result = numbers[i];
			times = 1;
		}
		else if (numbers[i] == result)
			times++;
		else
			times--;
	}

	if (!CheckMoreThanHalf(numbers, length, result))
		result = 0;

	return result;
}

int main(int argc, const char *argv[])
{
	int arr[] = {1, 2, 2, 6, 2, 2, 5, 4, 2};
	int ret = MoreThanHalfNum(arr, sizeof(arr) / sizeof(int));
	if (g_bInputInvalid)
	{
		std::cout << "invalid input";
		exit(1);
	}

	std::cout << "target number:" << ret << std::endl;

	return 0;
}
