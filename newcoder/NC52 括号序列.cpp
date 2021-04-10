#include <iostream>
#include <stack>

bool isValid(const std::string &str)
{
	if (str.empty())
		return false;

	std::stack<char> chStack;

	for (auto i = 0; i < str.length(); i++)
	{
		if (chStack.empty())
		{
			chStack.push(str[i]);
			continue;
		}

		if (str[i] == ')' && chStack.top() == '(')
		{
			chStack.pop();
		}
		else if (str[i] == '}' && chStack.top() == '{')
		{
			chStack.pop();
		}
		else if (str[i] == ']' && chStack.top() == '[')
		{
			chStack.pop();
		}
		else
		{
			chStack.push(str[i]);
		}
	}
	return chStack.empty();
}

int main(int argc, char *argv[])
{
	std::string str{"}"};
	std::cout << "sting: " << str << "  " << std::boolalpha << isValid(str) << std::endl;
	return 0;
}
