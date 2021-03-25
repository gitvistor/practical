#include <iostream>
#include <chrono>
using namespace std;

bool IsUgly(int number)
{
	while (number % 2 == 0)
		number /= 2;

	while (number % 3 == 0)
		number /= 3;

	while (number % 5 == 0)
		number /= 5;

	return number == 1 ? true : false;
}

int GetUglyNumber(int index)
{
	if (index <= 0)
		return 0;

	int number = 0;
	int uglyCount = 0;

	while (uglyCount < index)
	{
		number++;
		if (IsUgly(number))
			uglyCount++;
	}

	return number;
}

int GetUglyNumber_Solution2(int index)
{
	if (index <= 0)
		return 0;

	int *pUglyNumbers = new int[index];
	pUglyNumbers[0] = 1;

	int nextUglyIndex = 1;
	int *pMultiply2 = pUglyNumbers;
	int *pMultiply3 = pUglyNumbers;
	int *pMultiply5 = pUglyNumbers;

	while (nextUglyIndex < index)
	{
		int min = std::min(std::min(*pMultiply2 * 2, *pMultiply3 * 3), *pMultiply5 * 5);
		pUglyNumbers[nextUglyIndex] = min;

		while (*pMultiply2 * 2 <= min)
			++pMultiply2;

		while (*pMultiply3 * 3 <= min)
			++pMultiply3;

		while (*pMultiply5 * 5 <= min)
			++pMultiply5;

		nextUglyIndex++;
	}

	int uglyNumber = pUglyNumbers[nextUglyIndex - 1];
	delete[] pUglyNumbers;

	return uglyNumber;
}

int main(int argc, const char *argv[])
{
	int index = 1200;
	
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	std::cout << "ugly number of index " << index << " is " << GetUglyNumber(index) << std::endl;
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	std::cout << "Solution1 cost " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms\n";

	t1 = std::chrono::steady_clock::now();
	std::cout << "\nugly number of index " << index << " is " << GetUglyNumber_Solution2(index) << std::endl;
	t2 = std::chrono::steady_clock::now();
	std::cout << "Solution2 cost " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms\n";

	return 0;
}
