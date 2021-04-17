#include <iostream>
#include <vector>

using namespace std;

int lengthOfLongestSubstring(const std::string &str)
{
	std::vector<int> vec(128, 0);
	int ans = 0;
	int i = 0;
	for (int j = 0; j < str.size(); j++)
	{
		i = std::max(i, vec[str[j]]);
		vec[str[j]] = j + 1;
		ans = std::max(ans, j - i + 1);
	}
	return ans;
}

int main(int argc, char *argv[])
{
	std::string str = "rsdvdf";
	std::cout << lengthOfLongestSubstring(str) << std::endl;
	return 0;
}
