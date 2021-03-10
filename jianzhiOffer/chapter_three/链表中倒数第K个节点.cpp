#include <iostream>
using namespace std;

struct ListNode
{
	int m_nValue;
	ListNode *m_pNext;
};

ListNode *CreateNode(int *arr, int length)
{
	if (!arr || length <= 0)
		return nullptr;

	ListNode *pHead{nullptr};
	ListNode *pNext{nullptr};
	for (int i = 0; i < length; i++)
	{
		ListNode *pNode = new ListNode();
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

ListNode *FindKthToTail(ListNode *pListHead, unsigned int k)
{
	if (!pListHead || k <= 0)
		return nullptr;

	ListNode *pAhead = pListHead;
	ListNode *pBhead = nullptr;

	for (decltype(k) i = 0; i < k - 1; i++)
	{
		if (pAhead->m_pNext)
			pAhead = pAhead->m_pNext;
		else
			return nullptr;
	}

	pBhead = pListHead;
	while (pAhead->m_pNext)
	{
		pAhead = pAhead->m_pNext;
		pBhead = pBhead->m_pNext;
	}

	return pBhead;
}

int main(int argc, const char *argv[])
{
	int arr[] = {5, 3, 2, 9, 1, 8, 4, 6};
	ListNode *pHead = CreateNode(arr, sizeof(arr) / sizeof(int));
	int k = 8;
	ListNode *pNode = FindKthToTail(pHead, k);
	if (pNode)
	{
		std::cout << "found the " << k << "th node: " << pNode->m_nValue << std::endl;
	}
	else
	{
		std::cout << "not found the " << k << "th node" << std::endl;
	}

	return 0;
}
