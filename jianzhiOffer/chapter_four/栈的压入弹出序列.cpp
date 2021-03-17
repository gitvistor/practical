#include <iostream>
#include <stack>

using namespace std;

bool IsPopInOrder(const int *pPush, const int *pPop, int nLength)
{
    if (!pPush || !pPop || nLength <= 0)
        return false;

    const int *pNextPush = pPush;
    const int *pNextPop = pPop;
    std::stack<int> data;
    while (pNextPop - pPop < nLength)
    {
        while (data.empty() || data.top() != *pNextPop)
        {
            if (pNextPush - pPush == nLength)
                break;
            data.push(*pNextPush++);
        }

        if (data.top() != *pNextPop)
            break;

        data.pop();
        pNextPop++;
    }

    if (data.empty() && pNextPop - pPop == nLength)
        return true;

    return false;
}

int main(int argc, const char *argv[])
{
    int stack1[] = {1, 2, 3, 4, 5};
    int stack2[] = {4, 5, 3, 2, 1};

    std::cout << "stack in: ";
    for (auto i = 0; i < sizeof(stack1) / sizeof(int); i++)
    {
        std::cout << stack1[i] << ' ';
    }
    std::cout << std::endl;

    std::cout << "stack out: ";
    for (auto i = 0; i < sizeof(stack2) / sizeof(int); i++)
    {
        std::cout << stack2[i] << ' ';
    }
    std::cout << std::endl;

    if (IsPopInOrder(stack1, stack2, sizeof(stack1) / sizeof(int)))
    {
        std::cout << "match\n";
    }
    else
    {
        std::cout << "not match\n";
    }

    return 0;
}
