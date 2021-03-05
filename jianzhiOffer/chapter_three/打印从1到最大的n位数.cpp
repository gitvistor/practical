#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

#define NUM 3
#define STR1(NUM) #NUM
#define STR2(NUM) STR1(NUM)
#define LINI_NUM 10

bool Increment(char *number)
{
	bool isOverFlow = false;
	int nTakeOver = 0;
	int nLength = strlen(number);
	for (int i = nLength - 1; i >= 0; i--)
	{
		int nSum = number[i] - '0' + nTakeOver;
		if (i == nLength - 1)
			nSum++;

		if (nSum >= 10)
		{
			if (i == 0)
			{
				isOverFlow = true;
				break;
			}
			else
			{
				nTakeOver = 1;
				nSum -= 10;
				number[i] = '0' + nSum;
			}
		}
		else
		{
			number[i] = '0' + nSum;
			break;
		}
	}

	return isOverFlow;
}

void PrintNumber(char *number)
{
	bool isBeginnig0 = true;
	int nLength = strlen(number);
	for (int i = 0; i < nLength; i++)
	{
		if (isBeginnig0 && number[i] != '0')
		{
			isBeginnig0 = false;
		}
		
		if (!isBeginnig0)
		{
			std::cout << number[i];
		}
	}
}

void Print1ToMaxOfNDigits(int n)
{
	if (n <= 0)
		return;

	char *number = new char[n + 1];
	memset(number, '0', n);
	number[n] = '\0';
	int num = 0;
	while (!Increment(number))
	{
		PrintNumber(number);
		std::cout << "\t";
		num++;
		if (num % LINI_NUM == 0)
			std::cout << std::endl;
	}
	delete[] number;
}

int main(int argc, const char *argv[])
{
	std::cout << "Print1ToMaxOfNDigits(" STR2(NUM) "):\n\n";
	Print1ToMaxOfNDigits(NUM);

	return 0;
}
