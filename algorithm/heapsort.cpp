#include <iostream>

using namespace std;

void adjust(int *arr, int len, int index)
{
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int maxIdx = index;
	if (left < len && arr[left] > arr[maxIdx])
		maxIdx = left;
	if (right < len && arr[right] > arr[maxIdx])
		maxIdx = right;
	if (maxIdx != index)
	{
		swap(arr[maxIdx], arr[index]);
		adjust(arr, len, maxIdx);
	}
}

void heapsort(int *arr, int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		adjust(arr, size, i);
	}

	for (int i = size - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		adjust(arr, i, 0);
	}
}

int main(int argc, char *argv[])
{
	int arr[] = {8, 1, 14, 3, 2, -999, -21, 99, 0, 9};
	int length = sizeof(arr) / sizeof(int);
	heapsort(arr, length);
	for (int i = 0; i < length; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
	return 0;
}