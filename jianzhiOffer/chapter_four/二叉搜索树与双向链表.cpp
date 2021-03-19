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

void ConvertNode(BinaryTreeNode *pNode, BinaryTreeNode **pLastNodeInList)
{
	if (!pNode)
		return;

	BinaryTreeNode *pCurrent = pNode;
	if (pCurrent->m_pLeft)
		ConvertNode(pCurrent->m_pLeft, pLastNodeInList);

	pCurrent->m_pLeft = *pLastNodeInList;
	if (*pLastNodeInList)
		(*pLastNodeInList)->m_pRight = pCurrent;

	*pLastNodeInList = pCurrent;
	if (pCurrent->m_pRight)
		ConvertNode(pCurrent->m_pRight, pLastNodeInList);
}

BinaryTreeNode *Convert(BinaryTreeNode *pRoot)
{
	BinaryTreeNode *pLastNodeInList = nullptr;
	ConvertNode(pRoot, &pLastNodeInList);

	BinaryTreeNode *pHeadOfList = pLastNodeInList;
	while (pHeadOfList && pHeadOfList->m_pLeft)
		pHeadOfList = pHeadOfList->m_pLeft;

	return pHeadOfList;
}

void preOrder(BinaryTreeNode *pRoot)
{
	if (!pRoot)
		return;

	std::cout << pRoot->m_nValue << ' ';
	preOrder(pRoot->m_pLeft);
	preOrder(pRoot->m_pRight);
}

void inOrder(BinaryTreeNode *pRoot)
{
	if (!pRoot)
		return;

	inOrder(pRoot->m_pLeft);
	std::cout << pRoot->m_nValue << ' ';
	inOrder(pRoot->m_pRight);
}

void printList(BinaryTreeNode *pHead)
{
	BinaryTreeNode *pNode = pHead;
	while (pNode)
	{
		std::cout << pNode->m_nValue << ' ';
		pNode = pNode->m_pRight;
	}
}

int main(int argc, const char *argv[])
{
	int arr[] = {8, 4, 12, 5, 13, 10, 3};
	BinaryTreeNode *pHead = CreateBiTree(arr, sizeof(arr) / sizeof(int));

	std::cout << "preOrder: ";
	preOrder(pHead);
	std::cout << std::endl;

	std::cout << "inOrder: ";
	inOrder(pHead);
	std::cout << std::endl;

	std::cout << "print list: ";
	BinaryTreeNode *pListHead = Convert(pHead);
	printList(pListHead);

	return 0;
}
