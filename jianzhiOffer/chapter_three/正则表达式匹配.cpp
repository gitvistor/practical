#include <iostream>
using namespace std;

bool matchCore(const char *str, const char *pattern)
{
	if (*str == '\0' && *pattern == '\0')
		return true;

	if (*str != '\0' && *pattern == '\0')
		return false;

	if (*(pattern + 1) == '*')
	{
		if (*pattern == *str || (*pattern == '.' && *str != '\0'))
			return matchCore(str + 1, pattern + 2) || matchCore(str + 1, pattern) || matchCore(str, pattern + 2);
		else
			return matchCore(str, pattern + 2);
	}

	if (*str == *pattern || (*pattern == '.' && *str != '\0'))
		return matchCore(str + 1, pattern + 1);

	return false;
}

bool match(const char *str, const char *pattern)
{
	if (!str || !pattern)
		return false;

	return matchCore(str, pattern);
}

int main(int argc, const char *argv[])
{
	const char *str = "aaa";
	const char *pattern = "ab*ac*a";
	std::cout << (match(str, pattern) ? "match" : "not match") << std::endl;

	return 0;
}
