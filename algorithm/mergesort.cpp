#include <iostream>
#include <random>
#include <ctime>
using namespace std;

//merge_sort
template <typename T>
void merge_sort(T arr[], int len)
{
	T *a = arr;
	T *b = new T[len];

	for (int seg = 1; seg < len; seg += seg)
	{
		for (int start = 0; start < len; start += seg + seg)
		{
			int low = start, mid = std::min(start + seg, len), high = std::min(start + seg + seg, len);
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;

			while (start1 < end1 && start2 < end2)
				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];

			while (start1 < end1)
				b[k++] = a[start1++];

			while (start2 < end2)
				b[k++] = a[start2++];
		}
		std::swap(a, b);
	}

	if (a != arr)
	{
		for (int i = 0; i < len; i++)
			b[i] = a[i];
		b = a;
	}

	delete[] b;
}

//merge_sort_recursive
template <typename T>
void merge_sort_recursive(T arr[], T reg[], int start, int end)
{
	if (start >= end)
		return;

	int len = end - start, mid = (len >> 1) + start;
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;

	merge_sort_recursive(arr, reg, start1, end1);
	merge_sort_recursive(arr, reg, start2, end2);

	int k = start;
	while (start1 <= end1 && start2 <= end2)
		reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];

	while (start1 <= end1)
		reg[k++] = arr[start1++];

	while (start2 <= end2)
		reg[k++] = arr[start2++];

	for (k = start; k <= end; k++)
		arr[k] = reg[k];
}

template <typename T>
void merge_sort_r(T arr[], const int len)
{
	T reg[len];
	merge_sort_recursive(arr, reg, 0, len - 1);
}

void merge(int *data, int start, int mid, int end, int *result)
{
	int i, j, k;
	i = start;
	j = mid + 1;
	k = 0;

	while (i <= mid && j <= end)
	{
		if (data[i] <= data[j])
			result[k++] = data[i++];
		else
			result[k++] = data[j++];
	}

	while (i <= mid)
		result[k++] = data[i++];

	while (j <= end)
		result[k++] = data[j++];

	for (i = 0; i < k; i++)
		data[start + i] = result[i];
}

void merge_sort_v2(int *data, int start, int end, int *result)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		merge_sort_v2(data, start, mid, result);
		merge_sort_v2(data, mid + 1, end, result);
		merge(data, start, mid, end, result);
	}
}

#define LEN 8

int main(int argc, const char *argv[])
{
	std::default_random_engine e(time(0));
	std::uniform_int_distribution<> u(1, 20);

	std::cout << "array: ";
	int arr_a[LEN];
	int arr_b[LEN];
	int arr_c[LEN];
	for (auto i = 0; i < LEN; i++)
	{
		arr_a[i] = u(e);
		arr_b[i] = arr_a[i];
		arr_c[i] = arr_a[i];
		std::cout << arr_a[i] << ' ';
	}
	std::cout << '\n';

	merge_sort(arr_a, LEN);

	std::cout << "merge_sort: ";
	for (auto i = 0; i < LEN; i++)
	{
		std::cout << arr_a[i] << ' ';
	}
	std::cout << '\n';

	std::cout << "merge_sort_recursive: ";

	merge_sort_r(arr_b, LEN);

	for (auto i = 0; i < LEN; i++)
	{
		std::cout << arr_b[i] << ' ';
	}
	std::cout << '\n';

	std::cout << "merge_sort_v2: ";

	int *result = new int[LEN];
	merge_sort_v2(arr_c, 0, LEN - 1, result);
	delete[] result;

	for (auto i = 0; i < LEN; i++)
	{
		std::cout << arr_c[i] << ' ';
	}
	std::cout << '\n';

	return 0;
}
