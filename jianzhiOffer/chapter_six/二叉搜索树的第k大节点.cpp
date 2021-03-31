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

void inOrderPrint(BinaryTreeNode *pNode)
{
  if (!pNode)
    return;

  inOrderPrint(pNode->m_pLeft);
  std::cout << pNode->m_nValue << ' ';
  inOrderPrint(pNode->m_pRight);
}
int count1 = 0;
int count2 = 0;
BinaryTreeNode *KthNodeCore(BinaryTreeNode *pRoot, unsigned int &k)
{
  BinaryTreeNode *pTarget = nullptr;
  if (pRoot->m_pLeft)
    pTarget = KthNodeCore(pRoot->m_pLeft, k);

  if (!pTarget)
  {
    if (k == 1)
      pTarget = pRoot;
    k--;
  }

  if (!pTarget && pRoot->m_pRight)
    pTarget = KthNodeCore(pRoot->m_pRight, k);

  return pTarget;
}

BinaryTreeNode *KthNode(BinaryTreeNode *pRoot, unsigned int k)
{
  if (!pRoot || k <= 0)
    return nullptr;

  return KthNodeCore(pRoot, k);
}

int main(int argc, const char *argv[])
{
  int arr[] = {8, 6, 10, 5, 7, 9, 11};
  BinaryTreeNode *pRoot = createBinaryTree(arr, sizeof(arr) / sizeof(int));

  std::cout << "tree: ";
  inOrderPrint(pRoot);
  std::cout << std::endl;

  int k = 4;
  BinaryTreeNode *pNode = KthNode(pRoot, k);
  if (pNode)
    std::cout << k << "th node: " << pNode->m_nValue << std::endl;

  return 0;
}
