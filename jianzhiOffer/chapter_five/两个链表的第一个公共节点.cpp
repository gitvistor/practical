#include <iostream>
using namespace std;

struct ListNode
{
	int m_nKey;
	ListNode *m_pNext;
};

ListNode *pListNode1{nullptr};
ListNode *pListNode2{nullptr};

void createCommonNodeList(int *arr1, int len1, int *arr2, int len2)
{
	if (!arr1 || len1 <= 0 || !arr2 || len2 <= 0)
		return;

	int lenToTail = 0;
	for (int i = len1 - 1, j = len2 - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (arr1[i] != arr2[j])
			break;

		lenToTail++;
	}

	ListNode *pCommonNode{nullptr};
	ListNode *pNodeNext{nullptr};

	for (int i = 0; i < len1; i++)
	{
		ListNode *pNode = new ListNode();
		pNode->m_nKey = arr1[i];
		pNode->m_pNext = nullptr;

		if (i == 0)
		{
			pListNode1 = pNode;
		}
		else if (i + lenToTail == len1)
		{
			pCommonNode = pNode;
			pNodeNext->m_pNext = pNode;
		}
		else
		{
			pNodeNext->m_pNext = pNode;
		}

		pNodeNext = pNode;
	}

	if (!pCommonNode)
		return;

	for (int i = 0; i < len2; i++)
	{
		if (arr2[i] == pCommonNode->m_nKey)
		{
			if (i == 0)
				pListNode2 = pCommonNode;
			else
				pNodeNext->m_pNext = pCommonNode;

			return;
		}

		ListNode *pNode = new ListNode();
		pNode->m_nKey = arr2[i];
		pNode->m_pNext = nullptr;

		if (i == 0)
		{
			pListNode2 = pNode;
		}
		else
		{
			pNodeNext->m_pNext = pNode;
		}
		pNodeNext = pNode;
	}
}

void PrintListNode(ListNode *pNode)
{
	while (pNode)
	{
		std::cout << pNode->m_nKey << ' ';
		pNode = pNode->m_pNext;
	}
}

unsigned int GetListLength(ListNode *pHead)
{
	unsigned int nLength = 0;
	ListNode *pNode = pHead;
	while (pNode != nullptr)
	{
		++nLength;
		pNode = pNode->m_pNext;
	}
	return nLength;
}

ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2)
{
	unsigned int nLength1 = GetListLength(pHead1);
	unsigned int nLength2 = GetListLength(pHead2);

	int nLengthDif = nLength1 - nLength2;
	ListNode *pListHeadLong = pHead1;
	ListNode *pListHeadShort = pHead2;

	if (nLength2 > nLength1)
	{
		int nLengthDif = nLength2 - nLength1;
		pListHeadLong = pHead2;
		pListHeadShort = pHead1;
	}

	for (int i = 0; i < nLengthDif; i++)
		pListHeadLong = pListHeadLong->m_pNext;

	while (pListHeadLong && pListHeadShort && pListHeadLong != pListHeadShort)
	{
		pListHeadLong = pListHeadLong->m_pNext;
		pListHeadShort = pListHeadShort->m_pNext;
	}

	return pListHeadLong;
}

int main(int argc, const char *argv[])
{
	int arr1[] = {1, 2, 3, 6, 7};
	int arr2[] = {4, 5, 6, 7};

	createCommonNodeList(arr1, sizeof(arr1) / sizeof(int), arr2, sizeof(arr2) / sizeof(int));

	std::cout << "list1: ";
	PrintListNode(pListNode1);

	std::cout << "\nlist2: ";
	PrintListNode(pListNode2);

	ListNode *pCommonNode = FindFirstCommonNode(pListNode1, pListNode2);

	std::cout << "\ncommon: ";
	PrintListNode(pCommonNode);

	std::cout << '\n';

	return 0;
}
