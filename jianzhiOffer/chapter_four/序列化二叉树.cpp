#include <iostream>
#include <deque>
#include <fstream>
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
			nodes[i]->m_pLeft = nullptr;
			nodes[i]->m_pRight = nullptr;
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

void Serialize(BinaryTreeNode *pRoot, std::ofstream &ofs)
{
	if (!pRoot)
	{
		ofs << "$,";
		return;
	}
	ofs << pRoot->m_nValue << ",";
	Serialize(pRoot->m_pLeft, ofs);
	Serialize(pRoot->m_pRight, ofs);
}

bool ReadStrem(std::ifstream &ifs, int *number)
{
	//TO DO
	return true;
}

void Deserialize(BinaryTreeNode **pRoot, std::ifstream &ifs)
{
	int number;
	if (ReadStrem(ifs, &number))
	{
		*pRoot = new BinaryTreeNode();
		(*pRoot)->m_nValue = number;
		(*pRoot)->m_pLeft = nullptr;
		(*pRoot)->m_pRight = nullptr;
		Deserialize(&((*pRoot)->m_pLeft), ifs);
		Deserialize(&((*pRoot)->m_pRight), ifs);
	}
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

#define FILE "test.txt"

int main(int argc, const char *argv[])
{
	int arr[] = {1, 2, 3, 4, 0, 5, 6};
	BinaryTreeNode *pHead = createBinaryTree(arr, sizeof(arr) / sizeof(int));

	std::cout << "preOrder: ";
	preOrder(pHead);
	std::cout << std::endl;

	std::ofstream ofs(FILE);
	if (!ofs.is_open())
	{
		std::cerr << "ofs open file failed\n";
		exit(1);
	}

	Serialize(pHead, ofs);

	// std::ifstream ifs(FILE);
	// if(!ifs.is_open())
	// {
	// 	std::cerr<<"ifs open file failed\n";
	// 	exit(1);
	// }

	return 0;
}
