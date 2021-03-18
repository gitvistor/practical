#include <iostream>
#include <vector>

using namespace std;

struct BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode *m_pLeft;
    BinaryTreeNode *m_pRight;
};

BinaryTreeNode *InsertBiTree(BinaryTreeNode *t, int key)
{
    if (!t)
    {
        t = new BinaryTreeNode();
        t->m_pLeft = t->m_pRight = nullptr;
        t->m_nValue = key;
    }
    else if (key < t->m_nValue)
    {
        t->m_pLeft = InsertBiTree(t->m_pLeft, key);
    }
    else
    {
        t->m_pRight = InsertBiTree(t->m_pRight, key);
    }
    return t;
}

BinaryTreeNode *CreateBiTree(int *array, int length)
{
    if (!array || length <= 0)
        return nullptr;

    BinaryTreeNode *pNode = nullptr;
    for (int i = 0; i < length; i++)
    {
        pNode = InsertBiTree(pNode, array[i]);
    }
    return pNode;
}

void FindPath(BinaryTreeNode *pRoot, int expectedSum, std::vector<int> &path, int currentSum)
{
    currentSum += pRoot->m_nValue;
    path.push_back(pRoot->m_nValue);

    bool isLeaf = !pRoot->m_pLeft && !pRoot->m_pRight;
    if (isLeaf && currentSum == expectedSum)
    {
        std::cout << "a path is found: ";
        for (auto &e : path)
            std::cout << e << ' ';
        std::cout << endl;
    }

    if (pRoot->m_pLeft)
        FindPath(pRoot->m_pLeft, expectedSum, path, currentSum);

    if (pRoot->m_pRight)
        FindPath(pRoot->m_pRight, expectedSum, path, currentSum);

    path.pop_back();
}

void FindPath(BinaryTreeNode *pRoot, int expectedSum)
{
    if (!pRoot)
        return;

    std::vector<int> path;
    int currentSum = 0;
    FindPath(pRoot, expectedSum, path, currentSum);
}

void preOrder(BinaryTreeNode *pNode)
{
    if (!pNode)
        return;

    std::cout << pNode->m_nValue << ' ';
    preOrder(pNode->m_pLeft);
    preOrder(pNode->m_pRight);
}

#define EXPECTSUM 29

int main(int argc, const char *argv[])
{
    int arr[] = {12, 8, 10, 5, 4, 7, 15, 13};
    BinaryTreeNode *pRoot = CreateBiTree(arr, sizeof(arr) / sizeof(int));

    std::cout << "preOrder print: ";
    preOrder(pRoot);
    std::cout << std::endl;

    FindPath(pRoot, EXPECTSUM);

    return 0;
}
