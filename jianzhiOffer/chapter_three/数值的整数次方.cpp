#include <iostream>

using namespace std;

#define EPSINON 0.0000001
#define BASE 4
#define EXPONENT -1
#define STR1(R) #R
#define STR2(R) STR1(R)

bool g_InvalidInput = false;

bool equal(double num1, double num2)
{
	if ((num1 - num2 > -EPSINON) && (num1 - num2) < EPSINON)
		return true;
	else
		return false;
}

double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
	double result = 1.0;
	for (int i = 0; i < exponent; i++)
		result *= base;

	return result;
}

double PowerWithUnsignedExponent_V2(double base, unsigned int exponent)
{
	if (exponent == 0)
		return 1;
	
	if (exponent == 1)
		return base;

	double result = PowerWithUnsignedExponent_V2(base, exponent >> 1);
	result *= result;
	if (exponent & 1 == 1)
		result *= base;

	return result;
}

double Power(double base, int exponent)
{
	g_InvalidInput = false;

	if (equal(base, 0.0) && exponent < 0)
	{
		g_InvalidInput = true;
		return 0.0;
	}

	unsigned int absExponent = (unsigned int)(exponent);
	if (exponent < 0)
		absExponent = (unsigned int)(-exponent);

	// double result = PowerWithUnsignedExponent(base, absExponent);
	double result = PowerWithUnsignedExponent_V2(base, absExponent);
	if (exponent < 0)
		result = 1.0 / result;

	return result;
}

int main(int argc, const char *argv[])
{
	auto result = Power(BASE, EXPONENT);
	if (!g_InvalidInput)
		std::cout << "Power(" STR2(BASE) "," STR2(EXPONENT) ")=" << result << std::endl;
	else
		std::cout << "invalid input" << std::endl;

	return 0;
}
