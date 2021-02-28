#include <iostream>
#include <algorithm>

using namespace std;

int maxProductAfterCutting_solution1(int length)
{
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;

	int *products = new int[length + 1];
	products[0] = 0;
	products[1] = 1;
	products[2] = 2;
	products[3] = 3;

	int max = 0;
	for (int i = 4; i <= length; i++)
	{
		max = 0;
		for (int j = 1; j <= i / 2; j++)
		{
			int product = products[j] * products[i - j];
			if (max < product)
				max = product;
			products[i] = max;
		}
	}

	max = products[length];
	delete[] products;
	return max;
}

int maxProductAfterCutting_solution2(int length)
{
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;

	int timesOf3 = length / 3;
	if (length - timesOf3 * 3 == 1)
		timesOf3--;

	int timesOf2 = (length - timesOf3 * 3) / 2;
	return static_cast<int>(pow(3, timesOf3)) * static_cast<int>(pow(2, timesOf2));
}

int main(int argc, const char *argv[])
{
	int length = 18;
	std::cout << "maxProduct solution1: " << maxProductAfterCutting_solution1(length) << std::endl;
	std::cout << "maxProduct solution2: " << maxProductAfterCutting_solution2(length) << std::endl;
	return 0;
}
