#include <iostream>
#include <array>
using namespace std;

#define SIZE 8
#define DEL_NUM 2

struct ListNode
{
	int m_nValue;
	ListNode *m_pNext;
};

using PListNode = ListNode *;

PListNode CreateNode(const std::array<int, SIZE> &arr)
{
	if (arr.empty())
		return nullptr;

	PListNode pHead{nullptr}, pNext{nullptr};
	for (int i = 0; i < arr.size(); i++)
	{
		PListNode pNode = new ListNode();
		pNode->m_nValue = arr[i];
		pNode->m_pNext = nullptr;
		if (0 == i)
		{
			pHead = pNode;
			pNext = pHead;
		}
		else
		{
			pNext->m_pNext = pNode;
			pNext = pNode;
		}
	}

	return pHead;
}

PListNode FindNode(PListNode pHead, int value)
{
	if (!pHead)
		return nullptr;

	PListNode pNode = pHead;
	while (pNode && pNode->m_nValue != value)
	{
		pNode = pNode->m_pNext;
	}
	return pNode;
}

void PrintNode(PListNode pHead)
{
	if (!pHead)
		return;

	PListNode pNode = pHead;
	while (pNode)
	{
		std::cout << pNode->m_nValue << ' ';
		pNode = pNode->m_pNext;
	}
	std::cout << std::endl;
}

void DeleteNode(PListNode *pListHead, PListNode pToBeDeleted)
{
	if (!pListHead || !pToBeDeleted)
		return;

	if (pToBeDeleted->m_pNext)
	{
		PListNode pNext = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = pNext->m_nValue;
		pToBeDeleted->m_pNext = pNext->m_pNext;
		delete pNext;
		pNext = nullptr;
	}
	else if (*pListHead == pToBeDeleted)
	{
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
		*pListHead = nullptr;
	}
	else
	{
		PListNode pNode = *pListHead;
		while (pNode->m_pNext != pToBeDeleted)
		{
			pNode = pNode->m_pNext;
		}
		pNode->m_pNext = pToBeDeleted->m_pNext;
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
	}
}

void DeleteDuplication(PListNode *pHeaad)
{
	if (!pHeaad || !*pHeaad)
		return;

	PListNode pPreNode{nullptr};
	PListNode pNode = *pHeaad;
	while (pNode)
	{
		PListNode pNext = pNode->m_pNext;
		bool needDelete = false;
		if (pNext && pNext->m_nValue == pNode->m_nValue)
			needDelete = true;

		if (!needDelete)
		{
			pPreNode = pNode;
			pNode = pNode->m_pNext;
		}
		else
		{
			int value = pNext->m_nValue;
			PListNode pToBeDel = pNode;
			while (pToBeDel && pToBeDel->m_nValue == value)
			{
				pNext = pToBeDel->m_pNext;
				delete pToBeDel;
				pToBeDel = nullptr;
				pToBeDel = pNext;
			}

			if (!pPreNode)
			{
				*pHeaad = pNext;
			}
			else
			{
				pPreNode->m_pNext = pNext;
			}
			pNode = pNext;
		}
	}
}

int main(int argc, const char *argv[])
{
	std::array<int, SIZE> arr{5, 5, 3, 2, 2, 9, 1, 1, 8, 4, 6};
	auto pHead = CreateNode(arr);
	std::cout << "original array: ";
	PrintNode(pHead);

	auto pNode = FindNode(pHead, DEL_NUM);
	if (pNode)
		DeleteNode(&pHead, pNode);

	std::cout << "after delete " << DEL_NUM << ": ";
	PrintNode(pHead);

	DeleteDuplication(&pHead);

	std::cout << "delete duplication: ";
	PrintNode(pHead);

	return 0;
}
