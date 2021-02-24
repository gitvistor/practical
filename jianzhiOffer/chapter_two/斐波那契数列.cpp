#include <iostream>

using namespace std;

long long Fibonacci(unsigned int n)
{
	int result[2] = {0, 1};
	if (n < 2)
		return result[n];

	long long fibNMinusOne = 1;
	long long fibnMinusTwo = 0;
	long long fibN = 0;
	for (unsigned int i = 2; i <= n; i++)
	{
		fibN = fibNMinusOne + fibnMinusTwo;
		fibnMinusTwo = fibNMinusOne;
		fibNMinusOne = fibN;
	}

	return fibN;
}

int main(int argc, char *argv[])
{
	unsigned int n = 10;
	std::cout<<"Fibonacci("<<n<<")="<<Fibonacci(n)<<std::endl;
	
	return 0;
}
