#include <iostream>
using namespace std;

int InversePairsCore(int *data, int *copy, int start, int end)
{
	if (start == end)
	{
		copy[start] = data[start];
		return 0;
	}

	int length = (end - start) / 2;
	int left = InversePairsCore(copy, data, start, start + length);
	int right = InversePairsCore(copy, data, start + length + 1, end);
	int i = start + length;
	int j = end;
	int indexCopy = end;
	int count = 0;
	while (i >= start && j >= start + length + 1)
	{
		if (data[i] > data[j])
		{
			copy[indexCopy--] = data[i--];
			count += j - start - length;
		}
		else
		{
			copy[indexCopy--] = data[j--];
		}
	}
	for (; i >= start; --i)
		copy[indexCopy--] = data[i];

	for (; j >= start + length + 1; --j)
		copy[indexCopy--] = data[j];

	return left + right + count;
}

int InversePairs(int *data, int length)
{
	if (!data || length <= 0)
		return 0;

	int *copy = new int[length];
	for (int i = 0; i < length; i++)
		copy[i] = data[i];

	int count = InversePairsCore(data, copy, 0, length - 1);
	delete[] copy;
	return count;
}

int reverseCount = 0;

void merge(int *nums, int start, int mid, int end)
{
	int *temp = new int[end - start + 1];
	int p1 = start;
	int p2 = mid + 1;
	int p = 0;

	while (p1 <= mid && p2 <= end)
	{
		if (nums[p1] <= nums[p2])
		{
			temp[p++] = nums[p1++];
		}
		else
		{
			reverseCount += mid - p1 + 1;
			temp[p++] = nums[p2++];
		}
	}

	while (p1 <= mid)
		temp[p++] = nums[p1++];

	while (p2 <= end)
		temp[p++] = nums[p2++];

	for (int i = 0; i < p; i++)
		nums[start + i] = temp[i];

	delete[] temp;
}

void mergeSort(int *nums, int start, int end)
{
	if (start < end)
	{
		int mid = start + ((end - start) >> 1);
		mergeSort(nums, start, mid);
		mergeSort(nums, mid + 1, end);
		merge(nums, start, mid, end);
	}
}

int main(int argc, const char *argv[])
{
	int arr[] = {7, 5, 6, 4};
	constexpr int arrlen = sizeof(arr) / sizeof(int);

	int arr_b[arrlen];
	std::copy(arr, arr + arrlen, arr_b);

	std::cout << "array: ";
	for (auto &e : arr)
		std::cout << e << ' ';

	std::cout << "\nInverse count: " << InversePairs(arr, arrlen);

	mergeSort(arr_b, 0, arrlen - 1);
	std::cout << "\nInverse count: " << reverseCount << std::endl;

	return 0;
}
