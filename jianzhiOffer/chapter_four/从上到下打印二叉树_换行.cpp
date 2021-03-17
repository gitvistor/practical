#include <iostream>
#include <queue>
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

void PrintWithNewLine(BinaryTreeNode *pRoot)
{
    if (!pRoot)
        return;

    std::queue<BinaryTreeNode *> queueTreeNode;
    queueTreeNode.push(pRoot);

    int toBePrinted = 1;
    int nNextLevel = 0;
    while (!queueTreeNode.empty())
    {
        BinaryTreeNode *pNode = queueTreeNode.front();
        queueTreeNode.pop();

        std::cout << pNode->m_nValue << ' ';

        if (pNode->m_pLeft)
        {
            queueTreeNode.push(pNode->m_pLeft);
            ++nNextLevel;
        }

        if (pNode->m_pRight)
        {
            queueTreeNode.push(pNode->m_pRight);
            ++nNextLevel;
        }

        --toBePrinted;
        if (toBePrinted == 0)
        {
            std::cout << "\n";
            toBePrinted = nNextLevel;
            nNextLevel = 0;
        }
    }
}

int main(int argc, const char *argv[])
{
    int arr[] = {8, 6, 10, 5, 7, 9, 11};
    BinaryTreeNode *pRoot = createBinaryTree(arr, sizeof(arr) / sizeof(int));

    std::cout << "inorder print: ";
    inOrder(pRoot);
    std::cout << std::endl;

    std::cout << "print with newline:\n";
    PrintWithNewLine(pRoot);
    std::cout << std::endl;

    return 0;
}
