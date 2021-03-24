#include <iostream>
using namespace std;

int GetTranslation(const std::string &number)
{
	int length = number.length();
	int *counts = new int[length];
	int count = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		count = 0;
		if (i < length - 1)
			count = counts[i + 1];
		else
			count = 1;

		if (i < length - 1)
		{
			int digit1 = number[i] - '0';
			int digit2 = number[i + 1] - '0';
			int converted = digit1 * 10 + digit2;
			if (converted >= 10 && converted <= 25)
			{
				if (i < length - 2)
					count += counts[i + 2];
				else
					count++;
			}
		}

		counts[i] = count;
	}

	count = counts[0];
	delete[] counts;
	return count;
}

int GetTranslation(int num)
{
	if (num < 0)
		return 0;

	std::string strNum = std::to_string(num);
	return GetTranslation(strNum);
}

int main(int argc, const char *argv[])
{
	int number = 12765;
	std::cout << "number: " << number << std::endl;
	std::cout << "translation: " << GetTranslation(number) << std::endl;

	return 0;
}
