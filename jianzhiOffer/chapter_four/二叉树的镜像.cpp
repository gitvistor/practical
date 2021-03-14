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

void MirrorRecursively(BinaryTreeNode *pNode)
{
    if (!pNode)
        return;

    if (!pNode->m_pLeft && !pNode->m_pRight)
        return;

    BinaryTreeNode *pTemp = pNode->m_pLeft;
    pNode->m_pLeft = pNode->m_pRight;
    pNode->m_pRight = pTemp;

    if (pNode->m_pLeft)
        MirrorRecursively(pNode->m_pLeft);

    if (pNode->m_pRight)
        MirrorRecursively(pNode->m_pRight);
}

void inOrder(BinaryTreeNode *pNode)
{
    if (!pNode)
        return;

    inOrder(pNode->m_pLeft);
    std::cout << pNode->m_nValue << ' ';
    inOrder(pNode->m_pRight);
}

int main(int argc, const char *argv[])
{
    int arr[] = {8, 6, 10, 5, 7, 9, 11};
    int length = sizeof(arr) / sizeof(int);

    BinaryTreeNode *pRoot = createBinaryTree(arr, length);

    std::cout << "tree: ";
    inOrder(pRoot);
    std::cout << std::endl;

    MirrorRecursively(pRoot);

    std::cout << "mirror: ";
    inOrder(pRoot);
    std::cout << std::endl;

    return 0;
}
