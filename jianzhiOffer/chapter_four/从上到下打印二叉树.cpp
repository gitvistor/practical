#include <iostream>
#include <deque>
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

    std::deque<BinaryTreeNode *> nodeDeque;
    nodeDeque.push_back(nodes[0]);

    BinaryTreeNode *node;
    int index = 1;
    while (index < length)
    {
        node = nodeDeque.front();
        nodeDeque.pop_front();
        if (!node)
            continue;
        nodeDeque.push_back(nodes[index++]);
        node->m_pLeft = nodeDeque.back();
        if (index < length)
        {
            nodeDeque.push_back(nodes[index++]);
            node->m_pRight = nodeDeque.back();
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

void PrintFromTopToBottom(BinaryTreeNode *pRoot)
{
    if (!pRoot)
        return;

    std::deque<BinaryTreeNode *> dequeTreeNode;
    dequeTreeNode.push_back(pRoot);
    while (!dequeTreeNode.empty())
    {
        BinaryTreeNode *pNode = dequeTreeNode.front();
        dequeTreeNode.pop_front();

        std::cout << pNode->m_nValue << ' ';

        if (pNode->m_pLeft)
            dequeTreeNode.push_back(pNode->m_pLeft);

        if (pNode->m_pRight)
            dequeTreeNode.push_back(pNode->m_pRight);
    }
}

int main(int argc, const char *argv[])
{
    int arr[] = {8, 6, 10, 5, 7, 9, 11};
    BinaryTreeNode *pRoot = createBinaryTree(arr, sizeof(arr) / sizeof(int));

    std::cout << "inorder print: ";
    inOrder(pRoot);
    std::cout << std::endl;

    std::cout << "print from top: ";
    PrintFromTopToBottom(pRoot);
    std::cout << std::endl;

    return 0;
}
