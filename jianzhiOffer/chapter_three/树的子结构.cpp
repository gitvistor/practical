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

bool DoesTree1HaveTree2(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2)
{
    if (!pRoot2)
        return true;

    if (!pRoot1)
        return false;

    if (pRoot1->m_nValue != pRoot2->m_nValue)
        return false;

    return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) 
            && DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}

bool HasSubtree(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2)
{
    bool result = false;
    if (pRoot1 && pRoot2)
    {
        if (pRoot1->m_nValue == pRoot2->m_nValue)
            result = DoesTree1HaveTree2(pRoot1, pRoot2);
        if (!result)
            result = HasSubtree(pRoot1->m_pLeft, pRoot2);
        if (!result)
            result = HasSubtree(pRoot1->m_pRight, pRoot2);
    }
    return result;
}

int main(int argc, const char *argv[])
{
    int arr1[] = {8, 8, 7, 9, 2, 0, 0, 0, 0, 4, 7};
    int arr2[] = {8, 9, 2};
    int length1 = sizeof(arr1) / sizeof(int);
    int length2 = sizeof(arr2) / sizeof(int);

    BinaryTreeNode *pRoot1 = createBinaryTree(arr1, length1);
    BinaryTreeNode *pRoot2 = createBinaryTree(arr2, length2);

    std::cout << "tree1: ";
    inOrder(pRoot1);
    std::cout << std::endl;

    std::cout << "tree2: ";
    inOrder(pRoot2);
    std::cout << std::endl;

    bool result = HasSubtree(pRoot1, pRoot2);
    if (result)
        std::cout << "tree2 is a subtree of tree1" << std::endl;
    else
        std::cout << "tree2 is not a subtree of tree1" << std::endl;

    return 0;
}
