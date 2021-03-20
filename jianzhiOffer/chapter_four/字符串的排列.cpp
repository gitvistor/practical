
#include <iostream>
using namespace std;

void Permutation(char *pStr, char *pBegin)
{
	if (*pBegin == '\0')
	{
		std::cout << pStr << std::endl;
	}
	else
	{
		for (char *pCh = pBegin; *pCh != '\0'; ++pCh)
		{
			char temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;

			Permutation(pStr, pBegin + 1);

			temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;
		}
	}
}

void Permutation(char *pStr)
{
	if (!pStr)
		return;

	Permutation(pStr, pStr);
}

int main(int argc, const char *argv[])
{
	char str[] = "abc";
	Permutation(str);
	
	return 0;
}
