#include <iostream>
#include <cstring>

using namespace std;

bool hasPathCore(const char *matrix, int rows, int cols, int row, int col, const char *str, int &pathLength, bool *visited)
{
	if (str[pathLength] == '\0')
		return true;

	bool hasPath = false;
	if (row >= 0 && row < rows && col >= 0 && col < cols && matrix[row * cols + col] == str[pathLength] && !visited[row * cols + col])
	{
		++pathLength;
		visited[row * cols + col] = true;
		hasPath = hasPathCore(matrix, rows, cols, row, col - 1, str, pathLength, visited)
			 || hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, visited)
			 || hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, visited)
			 || hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, visited);
		if (!hasPath)
		{
			--pathLength;
			visited[row * cols + col] = false;
		}
	}

	return hasPath;
}

bool hasPath(const char *matrix, int rows, int cols, const char *str)
{
	if (!matrix || rows < 1 || cols < 1 || !str)
		return false;

	bool *visited = new bool[rows * cols];
	memset(visited, 0, rows * cols);

	int pathLength = 0;
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			if (hasPathCore(matrix, rows, cols, row, col, str, pathLength, visited))
			{
				return true;
			}
		}
	}
	delete[] visited;
	return false;
}

int main(int argc, const char *argv[])
{
	const char *matrix = "abtgcfcsjdeh";
	const char *str = "cfbt";
	auto ret = hasPath(matrix, 3, 4, str);
	if (ret)
	{
		std::cout << "has path" << std::endl;
	}
	else
	{
		std::cout << "not has path" << std::endl;
	}

	return 0;
}
