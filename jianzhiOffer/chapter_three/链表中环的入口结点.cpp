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
	ListNode *pMidNode{nullptr};
	ListNode *pLastNode{nullptr};

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

		if ((length - 1) / 2 == i)
		{
			pMidNode = pNode;
		}
		else if (length - 1 == i)
		{
			pLastNode = pNode;
		}
	}

	if (pLastNode)
	{
		pLastNode->m_pNext = pMidNode;
		std::cout << "mid node: " << pMidNode->m_nValue << std::endl;
		std::cout << "last node: " << pLastNode->m_nValue << std::endl;
	}

	return pHead;
}

ListNode *MeetingNode(ListNode *pHead)
{
	ListNode *pSlow = pHead->m_pNext;
	if (!pSlow)
		return nullptr;

	ListNode *pFast = pSlow->m_pNext;
	while (pFast)
	{
		if (pFast == pSlow)
			break;
		pFast = pFast->m_pNext;
		if (!pFast)
			return nullptr;
		pFast = pFast->m_pNext;
		pSlow = pSlow->m_pNext;
	}
	return pFast;
}

ListNode *EntryNodeOfLoop(ListNode *pHead)
{
	if (!pHead)
		return nullptr;

	ListNode *meetingnode = MeetingNode(pHead);
	if (!meetingnode)
		return nullptr;

	int nodesloop = 1;
	ListNode *pNode1 = meetingnode;
	while (pNode1->m_pNext != meetingnode)
	{
		pNode1 = pNode1->m_pNext;
		nodesloop++;
	}

	pNode1 = pHead;
	for (int i = 0; i < nodesloop; i++)
	{
		pNode1 = pNode1->m_pNext;
	}

	ListNode *pNode2 = pHead;
	while (pNode1 != pNode2)
	{
		pNode1 = pNode1->m_pNext;
		pNode2 = pNode2->m_pNext;
	}

	return pNode1;
}

int main(int argc, const char *argv[])
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	ListNode *pHead = CreateNode(arr, sizeof(arr) / sizeof(int));
	ListNode *pEntryNode = EntryNodeOfLoop(pHead);
	if (pEntryNode)
		std::cout << "found the entry node: " << pEntryNode->m_nValue << std::endl;
	else
		std::cout << "not found the entry node" << std::endl;

	return 0;
}
