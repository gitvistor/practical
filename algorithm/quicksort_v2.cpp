#include <iostream>
#include <vector>

using namespace std;

void QuickSort(int left, int right, vector<int> &vec)
{
	if (left >= right)
		return;

	int i = left, j = right, base = vec[left];

	while (i < j)
	{
		while (vec[j] >= base && i < j)
			j--;

		while (vec[i] <= base && i < j)
			i++;

		if (i < j)
		{
			std::swap(vec[i], vec[j]);
		}
	}

	vec[left] = vec[i];
	vec[i] = base;
	QuickSort(left, i - 1, vec);
	QuickSort(i + 1, right, vec);
}

int main(int argc, char *argv[])
{
	vector<int> vec{8, 3, 2, 7, 5, 4, 6};

	std::cout << "before QuickSort: ";
	for (auto e : vec)
		std::cout << e << ' ';
	std::cout << std::endl;

	QuickSort(0, vec.size() - 1, vec);

	std::cout << "after QuickSort: ";
	for (auto e : vec)
		std::cout << e << ' ';
	std::cout << std::endl;

	return 0;
}
