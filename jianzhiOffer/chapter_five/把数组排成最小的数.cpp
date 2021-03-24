#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int g_MaxNumberLength = 10;
char *g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];
char *g_StrCombine2 = new char[g_MaxNumberLength * 2 + 1];

int compare(const void *strNumber1, const void *strNumber2)
{
	strcpy(g_StrCombine1, *(const char **)strNumber1);
	strcat(g_StrCombine1, *(const char **)strNumber2);

	strcpy(g_StrCombine2, *(const char **)strNumber2);
	strcat(g_StrCombine2, *(const char **)strNumber1);

	return strcmp(g_StrCombine1, g_StrCombine2);
}

std::string PrintMinNumber_V1(int *number, int length)
{
	if (!number || length <= 0)
		return "";

	char **strNumbers = new char *[length];
	for (int i = 0; i < length; i++)
	{
		strNumbers[i] = new char[g_MaxNumberLength + 1];
		sprintf(strNumbers[i], "%d", number[i]);
	}

	qsort(strNumbers, length, sizeof(char *), compare);

	std::string minStrNumber;
	for (int i = 0; i < length; i++)
	{
		minStrNumber += strNumbers[i];
	}

	for (int i = 0; i < length; i++)
	{
		delete[] strNumbers[i];
	}
	delete[] strNumbers;

	return minStrNumber;
}

bool comp(const std::string &str1, const std::string &str2)
{
	auto s1 = str1 + str2;
	auto s2 = str2 + str1;
	return s1 < s2;
}

std::string PrintMinNumber_V2(int *number, int length)
{
	if (!number || length <= 0)
		return "";

	std::vector<std::string> strVec;
	for (auto i = 0; i < length; i++)
		strVec.emplace_back(std::to_string(number[i]));

	std::sort(strVec.begin(), strVec.end(), comp);

	std::string minStrNumber;
	for_each(strVec.begin(), strVec.end(), [&minStrNumber](const std::string &num) {
		minStrNumber += num;
	});

	return minStrNumber;
}

int main(int argc, const char *argv[])
{
	int number[] = {3, 27, 321, 1645};
	std::cout << "array: ";
	for (auto &e : number)
		cout << e << ' ';

	std::cout << "\nmin combined number: " << PrintMinNumber_V1(number, sizeof(number) / sizeof(int));
	std::cout << "\nmin combined number: " << PrintMinNumber_V2(number, sizeof(number) / sizeof(int));
	std::cout << std::endl;

	return 0;
}
