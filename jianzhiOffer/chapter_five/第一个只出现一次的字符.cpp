#include <iostream>
using namespace std;

#define TALBE_SIZE 256

char FirstNotRepeating(const char *pStr)
{
	if (!pStr)
		return '\0';

	unsigned char hashTalbe[TALBE_SIZE];
	for (int i = 0; i < TALBE_SIZE; i++)
		hashTalbe[i] = 0;

	const char *pHashKey = pStr;
	while (*pHashKey != '\0')
		hashTalbe[*(pHashKey++)]++;

	pHashKey = pStr;
	while (*pHashKey != '\0')
	{
		if (hashTalbe[*pHashKey] == 1)
			return *pHashKey;
		pHashKey++;
	}

	return '\0';
}

int main(int argc, const char *argv[])
{
	const char *pStr = "abaccdeff";
	std::cout << "string: " << pStr << std::endl;
	std::cout << "first not repeating char: " << FirstNotRepeating(pStr) << std::endl;

	return 0;
}
