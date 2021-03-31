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

int TreeDepth_Recursive(BinaryTreeNode *pRoot)
{
  if (!pRoot)
    return 0;

  int left = TreeDepth_Recursive(pRoot->m_pLeft);
  int right = TreeDepth_Recursive(pRoot->m_pRight);

  return left > right ? left + 1 : right + 1;
}

int TreeDepth(BinaryTreeNode *pRoot)
{
  if (!pRoot)
    return 0;

  std::queue<BinaryTreeNode *> que;
  que.push(pRoot);

  int level = 0;
  while (!que.empty())
  {
    level++;
    int len = que.size();
    while (len--)
    {
      BinaryTreeNode *temp = que.front();
      que.pop();

      if (temp->m_pLeft)
        que.push(temp->m_pLeft);

      if (temp->m_pRight)
        que.push(temp->m_pRight);
    }
  }
  return level;
}

int main(int argc, const char *argv[])
{
  int arr[] = {8, 6, 10, 5, 7, 9, 11, 13};
  BinaryTreeNode *pRoot = createBinaryTree(arr, sizeof(arr) / sizeof(int));

  std::cout << "tree: ";
  inOrderPrint(pRoot);
  std::cout << std::endl;

  std::cout << "tree depth: " << TreeDepth_Recursive(pRoot);
  std::cout << "\ntree depth: " << TreeDepth(pRoot);

  return 0;
}
