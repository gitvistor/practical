#include <iostream>
using namespace std;

bool scanUnsingedInteger(const char **str)
{
	const char *before = *str;
	while (**str != '\0' && **str >= '0' && **str <= '9')
		++(*str);
	return *str > before;
}

bool scanInteger(const char **str)
{
	if (**str == '+' || **str == '-')
		++(*str);
	return scanUnsingedInteger(str);
}

bool isNumeric(const char *str)
{
	if (!str)
		return false;

	bool numeric = scanInteger(&str);
	if (*str == '.')
	{
		++str;
		numeric = scanUnsingedInteger(&str) || numeric;
	}

	if (*str == 'e' || *str == 'E')
	{
		++str;
		numeric = numeric && scanInteger(&str);
	}

	return numeric && *str == '\0';
}

int main(int argc, const char *argv[])
{
	const char* str = "1.e2";
	std::cout << str << (isNumeric(str) ? " is numeric" : " is not numeric") << std::endl;
	return 0;
}
