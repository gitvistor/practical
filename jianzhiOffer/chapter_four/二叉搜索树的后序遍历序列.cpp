#include <iostream>

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

bool VerifySequenceOfBST(int *sequence, int length)
{
    if (!sequence || length <= 0)
        return false;

    int root = sequence[length - 1];
    int i = 0;
    for (; i < length - 1; i++)
    {
        if (sequence[i] > root)
            break;
    }

    for (int j = i; j < length - 1; j++)
    {
        if (sequence[j] < root)
            return false;
    }

    bool left = true;
    if (i > 0)
    {
        left = VerifySequenceOfBST(sequence, i);
    }

    bool right = true;
    if (i < length - 1)
    {
        right = VerifySequenceOfBST(sequence + i, length - i - 1);
    }

    return left && right;
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
    int arr[] = {5, 7, 6, 9, 4, 11, 8};
    BinaryTreeNode *pRoot = CreateBiTree(arr, sizeof(arr) / sizeof(int));

    std::cout << "inOrder print: ";
    inOrder(pRoot);
    std::cout << std::endl;

    if (VerifySequenceOfBST(arr, sizeof(arr) / sizeof(int)))
    {
        std::cout << "valid BST\n";
    }
    else
    {
        std::cout << "invalid BST\n";
    }
    return 0;
}
