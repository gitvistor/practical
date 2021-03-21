#include <iostream>
#include <random>
#include <ctime>

using namespace std;

bool g_InvalidInput = false;

int Partition(int *data, int length, int start, int end)
{
	if (!data || length <= 0 || start < 0 || end >= length)
	{
		return -1;
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

void GetLeastNumbers(int *input, int length, int *output, int k)
{
	if (!input || !output || k > length || length <= 0 || k <= 0)
	{
		g_InvalidInput = true;
		return;
	}

	int start = 0;
	int end = length - 1;
	int index = Partition(input, length, start, end);
	if (index == -1)
	{
		g_InvalidInput = true;
		return;
	}

	while (index != k - 1)
	{
		if (index > k - 1)
		{
			end = index - 1;
		}
		else
		{
			start = index + 1;
		}
		index = Partition(input, length, start, end);
		if (index == -1)
		{
			g_InvalidInput = true;
			return;
		}
	}

	for (int i = 0; i < k; i++)
		output[i] = input[i];
}

int main(int argc, const char *argv[])
{
	int input[] = {4, 5, 1, 6, 2, 7, 3, 8};
	int output[sizeof(input) / sizeof(int)];
	int k = 4;

	GetLeastNumbers(input, sizeof(input) / sizeof(int), output, k);

	if (!g_InvalidInput)
	{
		std::cout << "output: ";
		for (int i = 0; i < k; i++)
		{
			std::cout << output[i] << ' ';
		}
	}
	else
	{
		std::cout << "invalid input";
	}

	return 0;
}
