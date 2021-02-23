#include <iostream>

using namespace std;

struct BinaryTreeNode
{
	BinaryTreeNode *m_pParent;
	BinaryTreeNode *m_pLeft;
	BinaryTreeNode *m_pRight;
};

BinaryTreeNode *GetNext(BinaryTreeNode *pNode)
{
	if (!pNode)
		return nullptr;

	BinaryTreeNode *pNext = nullptr;
	if (pNode->m_pRight)
	{
		BinaryTreeNode *pRight = pNode->m_pRight;
		while (pRight->m_pLeft)
		{
			pRight = pRight->m_pLeft;
		}
		pNext = pRight;
	}
	else if (pNode->m_pParent)
	{
		BinaryTreeNode *pCurrent = pNode;
		BinaryTreeNode *pParent = pNode->m_pParent;
		while (pParent && pCurrent == pParent->m_pRight)
		{
			pCurrent = pParent;
			pParent = pParent->m_pParent;
		}
		pNext = pParent;
	}
	return pNext;
}

int main(int argc, char *argv[])
{
	return 0;
}
