#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
using namespace std;

#define ROW 4
#define COL 4

int getMaxValue_sloution(const int *values, int rows, int cols)
{
	if (!values || rows <= 0 || cols <= 0)
		return 0;

	int **maxValues = new int *[rows];

	for (int i = 0; i < rows; i++)
		maxValues[i] = new int[cols];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int left = 0;
			int up = 0;
			if (i > 0)
				up = maxValues[i - 1][j];

			if (j > 0)
				left = maxValues[i][j - 1];

			maxValues[i][j] = std::max(left, up) + values[i * cols + j];
		}
	}

	int maxValue = maxValues[rows - 1][cols - 1];
	for (int i = 0; i < rows; i++)
		delete[] maxValues[i];
	delete[] maxValues;

	return maxValue;
}

int main(int argc, const char *argv[])
{
	std::default_random_engine e(time(0));
	std::uniform_int_distribution<> u(1, 10);

	int arr[ROW * COL];
	std::cout << "array: \n";

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			arr[i * COL + j] = u(e);
			std::cout << std::setw(4) << arr[i * COL + j];
		}
		std::cout << std::endl;
	}

	std::cout << "\nmax value: " << getMaxValue_sloution(arr, ROW, COL) << std::endl;
	std::cout << std::endl;

	return 0;
}
