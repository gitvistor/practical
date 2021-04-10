#include <iostream>
#include <vector>

void QuickSort(std::vector<int> &vec, int start, int end)
{
	if (start >= end)
		return;

	int i = start;
	int j = end;
	int base = vec[end];

	while (i < j)
	{
		while (i < j && vec[i] >= base)
			i++;

		while (i < j && vec[j] <= base)
			j--;

		if (i < j)
			std::swap(vec[i], vec[j]);
	}

	vec[end] = vec[i];
	vec[i] = base;

	QuickSort(vec, start, i - 1);
	QuickSort(vec, j + 1, end);
}

int main(int argc, char *argv[])
{
	std::vector<int> vec{1, 6, 3, 5, 2, 2, 4};
	
	std::cout << "before QuickSort: ";
	for (auto e : vec)
		std::cout << e << ' ';
	std::cout << std::endl;

	QuickSort(vec, 0, vec.size() - 1);

	std::cout << "after QuickSort: ";
	for (auto e : vec)
		std::cout << e << ' ';
	std::cout << std::endl;

	return 0;
}
