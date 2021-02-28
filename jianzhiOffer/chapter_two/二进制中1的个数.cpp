#include <iostream>

using namespace std;

int NumberOf1_v1(int n)
{
	int count = 0;
	unsigned int flag = 1;
	while (flag)
	{
		if (n & flag)
			count++;
		flag = flag << 1;
	}
	return count;
}

int NumberOf1_v2(int n)
{
	int count = 0;
	while (n)
	{
		++count;
		n = (n - 1) & n;
	}
	return count;
}

int main(int argc, const char *argv[])
{
	int num = 15;
	std::cout << "number of 1.v1: " << NumberOf1_v1(num) << std::endl;
	std::cout << "number of 1.v2: " << NumberOf1_v2(num) << std::endl;
	return 0;
}
