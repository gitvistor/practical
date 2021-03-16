#include <iostream>
#include <iomanip>
using namespace std;

#define ROWS 3
#define COLS 2

void PrintMatrixInCircle(int (*numbers)[COLS], int cols, int rows, int start)
{
    int endX = cols - 1 - start;
    int endY = rows - 1 - start;

    for (int i = start; i <= endX; i++)
    {
        std::cout << numbers[start][i] << ' ';
    }

    if (start < endY)
    {
        for (int i = start + 1; i <= endY; i++)
        {
            std::cout << numbers[i][endX] << ' ';
        }
    }

    if (start < endX && start < endY)
    {
        for (int i = endX - 1; i >= start; i--)
        {
            std::cout << numbers[endY][i] << ' ';
        }
    }

    if (start < endX && start < endY - 1)
    {
        for (int i = endY - 1; i > start; i--)
        {
            std::cout << numbers[i][start] << ' ';
        }
    }
}

void PrintMatrixClockwisely(int (*numbers)[COLS], int cols, int rows)
{
    if (!numbers || cols <= 0 || rows <= 0)
        return;

    int start = 0;
    while (cols > start * 2 && rows > start * 2)
    {
        PrintMatrixInCircle(numbers, cols, rows, start);
        ++start;
    }
}

int main(int argc, const char *argv[])
{
    int value = 1;
    int numbers[ROWS][COLS];
    std::cout << "Matrix:\n";
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            numbers[i][j] = value++;
            std::cout << std::setw(4) << numbers[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << "\nPrintClockwisely: ";
    PrintMatrixClockwisely(numbers, COLS, ROWS);

    std::cout << std::endl;

    return 0;
}
