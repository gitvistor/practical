#include <iostream>

using namespace std;

bool Find(int *matrix, int rows, int columns, int number)
{
	bool found = false;
	if (matrix != nullptr && rows > 0 && columns > 0)
	{
		int row = 0;
		int column = columns - 1;
		while (row < rows && column >= 0)
		{
			if (matrix[row * columns + column] == number)
			{
				found = true;
				break;
			}
			else if (matrix[row * columns + column] > number)
			{
				--column;
			}
			else
			{
				++row;
			}
		}
	}
	return found;
}

int main(int argc, char *argv[])
{
	int a[16] = {1, 2, 8, 9, 2, 4, 9, 12, 4, 7, 10, 13, 6, 8, 11, 15};
	if (Find(a, 4, 4, 15))
		std::cout << "found" << std::endl;
	else
		std::cout << "not found" << std::endl;

	return 0;
}
