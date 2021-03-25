#include <iostream>
using namespace std;

int longestSubStringWithoutDuplication(const std::string &str)
{
	int curLength = 0;
	int maxLength = 0;

	int *position = new int[26];
	for (int i = 0; i < 26; i++)
		position[i] = -1;

	for (int i = 0; i < str.length(); i++)
	{
		int preIndex = position[str[i] - 'a'];
		if (preIndex < 0 || i - preIndex > curLength)
			++curLength;
		else
		{
			if (curLength > maxLength)
				maxLength = curLength;

			curLength = i - preIndex;
		}
		position[str[i] - 'a'] = i;
	}

	delete[] position;

	if (curLength > maxLength)
		maxLength = curLength;

	return maxLength;
}

int main(int argc, const char *argv[])
{
	std::string str{"arabcacfr"};
	std::cout << "string: " << str << std::endl;
	std::cout << "max length: " << longestSubStringWithoutDuplication(str) << std::endl;

	return 0;
}
