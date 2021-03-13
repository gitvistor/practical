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

void preOrder(BinaryTreeNode *pNode)
{
    if (!pNode)
        return;

    std::cout << pNode->m_nValue << ' ';
    preOrder(pNode->m_pLeft);
    preOrder(pNode->m_pRight);
}

void inOrder(BinaryTreeNode *pNode)
{
    if (!pNode)
        return;

    inOrder(pNode->m_pLeft);
    std::cout << pNode->m_nValue << ' ';
    inOrder(pNode->m_pRight);
}

void postOrder(BinaryTreeNode *pNode)
{
    if (!pNode)
        return;

    postOrder(pNode->m_pLeft);
    postOrder(pNode->m_pRight);
    std::cout << pNode->m_nValue << ' ';
}

int main(int argc, const char *argv[])
{
    int arr[] = {1, 3, 7, 4, 0, 6, 0, 8, 9};
    int length = sizeof(arr) / sizeof(int);
    BinaryTreeNode *pNode = createBinaryTree(arr, length);

    inOrder(pNode);

    std::cout << std::endl;

    return 0;
}
