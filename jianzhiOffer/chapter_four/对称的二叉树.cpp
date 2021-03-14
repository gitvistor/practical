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

bool isSymmetrical(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2)
{
    if (!pRoot1 && !pRoot2)
        return true;

    if (!pRoot1 || !pRoot2)
        return false;

    if (pRoot1->m_nValue != pRoot2->m_nValue)
        return false;

    return isSymmetrical(pRoot1->m_pLeft, pRoot2->m_pRight) && isSymmetrical(pRoot1->m_pRight, pRoot2->m_pLeft);
}

bool isSymmetrical(BinaryTreeNode *pRoot)
{
    return isSymmetrical(pRoot, pRoot);
}

int main(int argc, const char *argv[])
{
    int arr[] = {8, 6, 6, 5, 7, 7, 5};
    BinaryTreeNode *pRoot = createBinaryTree(arr, sizeof(arr) / sizeof(int));

    std::cout << "tree: ";
    inOrder(pRoot);
    std::cout << std::endl;

    bool ret = isSymmetrical(pRoot);
    std::cout << (ret ? "symmetrical" : "not symmetrical") << std::endl;

    return 0;
}
