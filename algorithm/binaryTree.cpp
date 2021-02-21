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

BinaryTreeNode *SearchBiTree(BinaryTreeNode *pNode, int key)
{
	if (!pNode)
		return nullptr;
	if (key == pNode->m_nValue)
		return pNode;
	else if (key < pNode->m_nValue)
		return SearchBiTree(pNode->m_pLeft, key);
	else
		return SearchBiTree(pNode->m_pRight, key);
}

void DeleteNode(BinaryTreeNode *&pNode)
{
	BinaryTreeNode *qNode, *sNode;
	if (!pNode->m_pRight)
	{
		qNode = pNode;
		pNode = pNode->m_pLeft;
		free(qNode);
	}
	else if (!pNode->m_pLeft)
	{
		qNode = pNode;
		pNode = pNode->m_pRight;
		free(qNode);
	}
	else
	{
		qNode = pNode;
		sNode = pNode->m_pLeft;
		while (sNode->m_pRight)
		{
			qNode = sNode;
			sNode = sNode->m_pRight;
		}
		pNode->m_nValue = sNode->m_nValue;
		if (qNode != pNode)
			qNode->m_pRight = sNode->m_pLeft;
		else
			qNode->m_pLeft = sNode->m_pLeft;
		free(sNode);
	}

	return;
}

void DeleteBiTree(BinaryTreeNode *&pNode, int key)
{
	if (!pNode)
		return;

	if (key == pNode->m_nValue)
		return DeleteNode(pNode);
	else if (key < pNode->m_nValue)
		return DeleteBiTree(pNode->m_pLeft, key);
	else
		return DeleteBiTree(pNode->m_pRight, key);
}

void PrintBiTreeInoder(BinaryTreeNode *pRoot)
{
	if (!pRoot)
		return;

	PrintBiTreeInoder(pRoot->m_pLeft);
	std::cout << pRoot->m_nValue << ' ';
	PrintBiTreeInoder(pRoot->m_pRight);
}

int main(int argc, char **argv)
{
	int array[] = {5, 2, 9, 4, 7, 6, 3, 1};
	BinaryTreeNode *pNode = CreateBiTree(array, sizeof(array) / sizeof(int));

	std::cout << "Inorder: ";
	PrintBiTreeInoder(pNode);
	std::cout << std::endl;

	int searchKey = 9;
	if (SearchBiTree(pNode, searchKey))
	{
		std::cout << "found " << searchKey;
	}
	else
	{
		std::cout << "not found " << searchKey;
	}
	std::cout << std::endl;

	int deletekey = 6;
	DeleteBiTree(pNode, deletekey);

	std::cout << "after delete " << deletekey << std::endl;
	std::cout << "Inorder: ";
	PrintBiTreeInoder(pNode);
	std::cout << std::endl;

	return 0;
}