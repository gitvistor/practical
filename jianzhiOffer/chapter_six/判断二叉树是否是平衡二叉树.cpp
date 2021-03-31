#include <iostream>
#include <queue>
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

void inOrderPrint(BinaryTreeNode *pNode)
{
  if (!pNode)
    return;

  inOrderPrint(pNode->m_pLeft);
  std::cout << pNode->m_nValue << ' ';
  inOrderPrint(pNode->m_pRight);
}

int TreeDepth(BinaryTreeNode *pRoot)
{
  if (!pRoot)
    return 0;

  int left = TreeDepth(pRoot->m_pLeft);
  int right = TreeDepth(pRoot->m_pRight);

  return left > right ? left + 1 : right + 1;
}

bool IsBalanced_R(BinaryTreeNode *pRoot)
{
  if (!pRoot)
    return true;

  int left = TreeDepth(pRoot->m_pLeft);
  int right = TreeDepth(pRoot->m_pRight);

  int diff = left - right;
  if (diff > 1 || diff < -1)
    return false;

  return IsBalanced_R(pRoot->m_pLeft) && IsBalanced_R(pRoot->m_pRight);
}

bool IsBalanced(BinaryTreeNode *pRoot, int *depth)
{
  if (!pRoot)
  {
    *depth = 0;
    return true;
  }

  int left, right;
  if (IsBalanced(pRoot->m_pLeft, &left) && IsBalanced(pRoot->m_pRight, &right))
  {
    int diff = right - left;
    if (diff <= 1 && diff >= -1)
    {
      *depth = left > right ? left + 1 : right + 1;
      return true;
    }
  }
  return false;
}

bool IsBalanced(BinaryTreeNode *pRoot)
{
  int depth = 0;
  return IsBalanced(pRoot, &depth);
}

int main(int argc, const char *argv[])
{
  int arr[] = {8, 6, 5, 11, 4, 10, 7};
  BinaryTreeNode *pRoot = CreateBiTree(arr, sizeof(arr) / sizeof(int));

  std::cout << "tree: ";
  inOrderPrint(pRoot);

  std::cout << std::boolalpha;
  std::cout << "\nis balanced: " << IsBalanced_R(pRoot);
  std::cout << "\nis balanced: " << IsBalanced(pRoot);

  return 0;
}
