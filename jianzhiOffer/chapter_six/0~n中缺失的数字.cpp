#include <iostream>
using namespace std;

int GetMissingNumber(int *numbers, int length)
{
	if (!numbers || length <= 0)
		return -1;

	int left = 0;
	int right = length - 1;
	while (left <= right)
	{
		int middle = (right + left) >> 1;
		if (numbers[middle] != middle)
		{
			if (middle == 0 || numbers[middle - 1] == middle - 1)
				return middle;
			right = middle - 1;
		}
		else
			left = middle + 1;
	}
	if (left == length)
		return length;

	return -1;
}

auto printNumber = [](int *arr, int length) {
	if (!arr || length <= 0)
		return;

	std::cout << "array: ";
	for (auto i = 0; i < length; i++)
	{
		std::cout << *(arr + i) << ' ';
	}
	std::cout << "\nmissing number: " << GetMissingNumber(arr, length) << "\n\n";
};

int main(int argc, const char *argv[])
{
	int arr1[] = {1, 2, 3, 4, 5};
	int arr2[] = {0, 1, 2, 3, 4};
	int arr3[] = {0, 1, 2, 3, 5};

	printNumber(arr1, sizeof(arr1) / sizeof(int));
	printNumber(arr2, sizeof(arr2) / sizeof(int));
	printNumber(arr3, sizeof(arr3) / sizeof(int));

	return 0;
}
