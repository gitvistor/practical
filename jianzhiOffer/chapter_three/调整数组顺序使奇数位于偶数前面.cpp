#include <iostream>
using namespace std;

bool isEven(int n)
{
	return (n & 1) == 0;
}

bool isOdd(int n)
{
	return !isEven(n);
}

void ReorderOddEven(int *pData, unsigned int length, bool (*func)(int))
{
	if (!pData || length <= 0)
	{
		return;
	}

	int *pBegin = pData;
	int *pEnd = pData + length - 1;
	while (pBegin < pEnd)
	{
		while (pBegin < pEnd && !func(*pBegin))
			pBegin++;

		while (pBegin < pEnd && func(*pEnd))
			pEnd--;

		if (pBegin < pEnd)
		{
			std::swap(*pBegin, *pEnd);
		}
	}
}

int main(int argc, const char *argv[])
{
	int array[] = {2, 1, 4, 9, 8, 3, 6, 5};
	ReorderOddEven(array, sizeof(array) / sizeof(int), isEven);
	for (auto &e : array)
		std::cout << e << ' ';

	std::cout << std::endl;
	return 0;
}
