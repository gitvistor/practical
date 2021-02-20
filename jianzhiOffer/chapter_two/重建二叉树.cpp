#include <iostream>
#include <exception>

using namespace std;

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode *m_pLeft;
	BinaryTreeNode *m_pRight;
};

BinaryTreeNode *ConstructCore(int *startPreoder, int *endPreorder, int *startInorder, int *endInorder)
{
	int rootValue = startPreoder[0];
	BinaryTreeNode *root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = nullptr;

	if (startPreoder == endPreorder)
	{
		if (startInorder == endInorder && *startPreoder == *startInorder)
		{
			return root;
		}
		else
		{
			throw std::exception();
		}
	}

	int *rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != rootValue)
		++rootInorder;

	if (rootInorder == endInorder && *rootInorder != rootValue)
		throw std::exception();

	int leftLength = rootInorder - startInorder;
	int *leftPreorderEnd = startPreoder + leftLength;
	if (leftLength > 0)
	{
		root->m_pLeft = ConstructCore(startPreoder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
	}
	if (leftLength < endPreorder - startPreoder)
	{
		root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
	}
	return root;
}

BinaryTreeNode *Construct(int *preorder, int *inorder, int length)
{
	if (!preorder || !inorder || length <= 0)
		return nullptr;
	return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}

void PreOrderPrint(BinaryTreeNode *root)
{
	if (!root)
		return;

	std::cout << root->m_nValue << ' ';
	PreOrderPrint(root->m_pLeft);
	PreOrderPrint(root->m_pRight);
}

void InOrderPrint(BinaryTreeNode *root)
{
	if (!root)
		return;

	InOrderPrint(root->m_pLeft);
	std::cout << root->m_nValue << ' ';
	InOrderPrint(root->m_pRight);
}

void PostOrderPrint(BinaryTreeNode *root)
{
	if (!root)
		return;

	PostOrderPrint(root->m_pLeft);
	PostOrderPrint(root->m_pRight);
	std::cout << root->m_nValue << ' ';
}

int main(int argc, char **argv)
{
	int preOrder[] = {1, 2, 4, 7, 3, 5, 6, 8};
	int inOrder[] = {4, 7, 2, 1, 5, 3, 8, 6};

	BinaryTreeNode *root = Construct(preOrder, inOrder, sizeof(preOrder) / sizeof(int));
	if (!root)
		exit(1);

	std::cout << "PreOrderPrint: ";
	PreOrderPrint(root);
	std::cout << endl;

	std::cout << "InOrderPrint: ";
	InOrderPrint(root);
	std::cout << endl;

	std::cout << "PostOrderPrint: ";
	PostOrderPrint(root);
	std::cout << endl;

	return 0;
}