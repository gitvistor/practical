#include <iostream>
#include <cstring>
using namespace std;

int PowerBase10(unsigned int n)
{
	int result = 1;
	for (unsigned int i = 0; i < n; i++)
		result *= 10;
	return result;
}

int Numberof1(const char *strN)
{
	if (!strN || *strN < '0' || *strN > '9' || *strN == '\0')
		return 0;

	int first = *strN - '0';
	unsigned int length = static_cast<unsigned int>(strlen(strN));
	if (length == 1 && first == 0)
		return 0;

	if (length == 1 && first > 0)
		return 1;

	int numFirstDigit = 0;
	if (first > 1)
		numFirstDigit = PowerBase10(length - 1);
	else if (first == 1)
		numFirstDigit = atoi(strN + 1) + 1;

	int numOtherDigits = first * (length - 1) * PowerBase10(length - 2);
	int numRecursive = Numberof1(strN + 1);
	return numFirstDigit + numOtherDigits + numRecursive;
}

int NumberOf1Between1AndN(int n)
{
	if (n <= 0)
		return 0;

	char strN[50];
	sprintf(strN, "%d", n);
	return Numberof1(strN);
}

unsigned int CountDigit1(unsigned int n)
{
	unsigned int base = 1;
	unsigned int count = 0;

	while (base <= n)
	{
		//高位
		unsigned int high = n / (base * 10);
		//低位
		unsigned int low = n - (n / base) * base;
		//当前位
		unsigned int current = n / base % 10;
		if (current == 0)
			count = count + high * base;
		else if (current == 1)
			count = count + high * base + low + 1;
		else
			count = count + (high + 1) * base;
		
		base = base * 10;
	}
	return count;
}

int main(int argc, const char *argv[])
{
	unsigned int num = 21345;
	std::cout << "numbef of 1 between 1~" << num << " is " << NumberOf1Between1AndN(num) << std::endl;
	std::cout << "numbef of 1 between 1~" << num << " is " << CountDigit1(num) << std::endl;

	return 0;
}
