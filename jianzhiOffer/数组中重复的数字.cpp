#include <iostream>
#include <algorithm>

using namespace std;

bool duplicate(int numbers[], int length, int *duplication)
{
	if (!numbers || length <= 0)
		return false;

	for (int i = 0; i < length; i++)
	{
		if (numbers[i] < 0 || numbers[i] > length - 1)
			return false;
	}

	for (int i = 0; i < length; i++)
	{
		while (numbers[i] != i)
		{
			if (numbers[i] == numbers[numbers[i]])
			{
				*duplication = numbers[i];
				return true;
			}
			std::swap(numbers[i], numbers[numbers[i]]);
		}
	}
	return false;
}

int main(int argc, char *argv[])
{
	int numbers[] = {2, 3, 1, 0, 4, 5, 3};
	int num;
	if (duplicate(numbers, sizeof(numbers) / sizeof(int), &num))
		std::cout << "found: " << num << std::endl;
	else
		std::cout << "not found" << std::endl;
	return 0;
}