#include <iostream>
#include <algorithm>
using namespace std;

int countOfIntegers(int digits)
{
	if (digits == 1)
		return 10;

	int count = static_cast<int>(std::pow(10, digits - 1));
	return 9 * count;
}

int beginNumber(int digits)
{
	if (digits == 1)
		return 0;

	return static_cast<int>(std::pow(10, digits - 1));
}

int digitAtIndex(int index, int digits)
{
	int number = beginNumber(digits) + index / digits;
	int indexFromRight = digits - index % digits;
	for (int i = 1; i < indexFromRight; i++)
		number /= 10;

	return number % 10;
}

int digitAtIndex(int index)
{
	if (index < 0)
		return -1;

	int digits = 1;
	while (true)
	{
		int numbers = countOfIntegers(digits);
		if (index < numbers * digits)
			return digitAtIndex(index, digits);

		index -= digits * numbers;
		digits++;
	}
	return -1;
}

int main(int argc, const char *argv[])
{
	int index = 13;
	std::cout << "index of " << index << " is " << digitAtIndex(index) << std::endl;

	return 0;
}
