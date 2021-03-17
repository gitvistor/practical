#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode *m_pLeft;
    BinaryTreeNode *m_pRight;
};

BinaryTreeNode *createBinaryTree(int *arr, int length)
{
    if (!arr || length <= 0)
        return nullptr;

    BinaryTreeNode **nodes = new BinaryTreeNode *[length];
    for (int i = 0; i < length; i++)
    {
        if (arr[i] == 0)
        {
            nodes[i] = nullptr;
        }
        else
        {
            nodes[i] = new BinaryTreeNode();
            nodes[i]->m_nValue = arr[i];
        }
    }

    std::queue<BinaryTreeNode *> nodeQueue;
    nodeQueue.push(nodes[0]);

    BinaryTreeNode *node;
    int index = 1;
    while (index < length)
    {
        node = nodeQueue.front();
        nodeQueue.pop();
        if (!node)
            continue;
        nodeQueue.push(nodes[index++]);
        node->m_pLeft = nodeQueue.back();
        if (index < length)
        {
            nodeQueue.push(nodes[index++]);
            node->m_pRight = nodeQueue.back();
        }
    }
    return nodes[0];
}

void inOrder(BinaryTreeNode *pNode)
{
    if (!pNode)
        return;

    inOrder(pNode->m_pLeft);
    std::cout << pNode->m_nValue << ' ';
    inOrder(pNode->m_pRight);
}

void PrintInZigzag(BinaryTreeNode *pRoot)
{
    if (!pRoot)
        return;

    int current = 0;
    int next = 1;
    std::stack<BinaryTreeNode *> levels[2];
    levels[current].push(pRoot);

    while (!levels[0].empty() || !levels[1].empty())
    {
        BinaryTreeNode *pNode = levels[current].top();
        levels[current].pop();

        std::cout << pNode->m_nValue << ' ';
        if (current == 0)
        {
            if (pNode->m_pLeft)
            {
                levels[next].push(pNode->m_pLeft);
            }

            if (pNode->m_pRight)
            {
                levels[next].push(pNode->m_pRight);
            }
        }
        else
        {
            if (pNode->m_pRight)
                levels[next].push(pNode->m_pRight);

            if (pNode->m_pLeft)
                levels[next].push(pNode->m_pLeft);
        }

        if (levels[current].empty())
        {
            std::cout << "\n";
            current = 1 - current;
            next = 1 - next;
        }
    }
}

int main(int argc, const char *argv[])
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    BinaryTreeNode *pRoot = createBinaryTree(arr, sizeof(arr) / sizeof(int));

    std::cout << "inorder print: ";
    inOrder(pRoot);
    std::cout << std::endl;

    std::cout << "print in zigzag:\n";
    PrintInZigzag(pRoot);
    std::cout << std::endl;

    return 0;
}
