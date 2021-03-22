#include <iostream>
#include <vector>
using namespace std;

bool g_InvaidInput = false;

int FindGreatestSumOfSubArray(int *pData, int length, std::vector<int> &subArray)
{
	if (!pData || length <= 0)
	{
		g_InvaidInput = true;
		return 0;
	}

	g_InvaidInput = false;
	int nCurSum = 0;
	int nGreatestSum = 0x80000000;
	int *pStart{nullptr}, *pEnd{nullptr};

	for (int i = 0; i < length; i++)
	{
		if (nCurSum <= 0)
		{
			nCurSum = pData[i];
			pStart = pData + i;
		}
		else
		{
			nCurSum += pData[i];
		}

		if (nCurSum > nGreatestSum)
		{
			pEnd = pData + i + 1;
			nGreatestSum = nCurSum;
		}
	}

	if (pStart && pEnd && pStart <= pEnd)
	{
		subArray.assign(pStart, pEnd);
	}

	return nGreatestSum;
}

int main(int argc, const char *argv[])
{
	int arr[] = {1, -2, 3, 10, -4, 7, -2, 5};

	std::cout << "test array: ";
	for (auto &e : arr)
	{
		std::cout << e << ' ';
	}

	std::vector<int> subArray;
	auto sum = FindGreatestSumOfSubArray(arr, sizeof(arr) / sizeof(int), subArray);

	if (!g_InvaidInput && !subArray.empty())
	{
		std::cout << "\nsub array: ";
		for (auto &e : subArray)
			std::cout << e << ' ';

		std::cout << "\ngreatest sum: " << sum << std::endl;
	}

	return 0;
}
