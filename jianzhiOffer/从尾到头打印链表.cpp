#include <iostream>
#include <stack>

using namespace std;

struct ListNode
{
	int m_nValue;
	ListNode *m_pNext;
};

void PrintList(ListNode *pHead)
{
	if (!pHead)
		return;
	ListNode *temp = pHead->m_pNext;
	while (temp)
	{
		cout << '\t' << temp->m_nValue;
		temp = temp->m_pNext;
	}
	cout << endl;
}

void PrintListIteratively(ListNode *pHead)
{
	if (!pHead)
		return;
	std::stack<ListNode *> nodes;
	ListNode *pNode = pHead->m_pNext;
	while (pNode != nullptr)
	{
		nodes.push(pNode);
		pNode = pNode->m_pNext;
	}
	while (!nodes.empty())
	{
		pNode = nodes.top();
		cout << '\t' << pNode->m_nValue;
		nodes.pop();
	}
}

void PrintListRecursively(ListNode *pNode)
{
	if (!pNode)
		return;
	PrintListRecursively(pNode->m_pNext);
	cout << '\t' << pNode->m_nValue;
}

ListNode *InitList()
{
	ListNode *head = (ListNode *)malloc(sizeof(ListNode));
	if (!head)
		return nullptr;
	head->m_pNext = nullptr;
	return head;
}

void InsertHead(ListNode *head, int newdata)
{
	if (!head)
		return;
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->m_nValue = newdata;
	node->m_pNext = head->m_pNext;
	head->m_pNext = node;
}

void InsertTail(ListNode *head, int newdata)
{
	if (!head)
		return;
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->m_nValue = newdata;
	node->m_pNext = nullptr;
	ListNode *temp = head;
	while (temp->m_pNext)
	{
		temp = temp->m_pNext;
	}
	temp->m_pNext = node;
}

void freeNode(ListNode *head)
{
	if (!head)
		return;
	ListNode *p, *temp;
	p = head;
	while (p)
	{
		temp = p->m_pNext;
		free(p);
		p = temp;
	}
}

int main(int argc, char *argv[])
{
	ListNode *head = InitList();
	if (!head)
		exit(1);

	cout << "InsertTail:";
	for (auto i = 1; i < 6; i++)
	{
		InsertTail(head, i);
	}
	PrintList(head);

	cout << "InsertHead:";
	for (auto i = 6; i < 10; i++)
	{
		InsertHead(head, i);
	}
	PrintList(head);

	cout << "Iteratively:";
	PrintListIteratively(head);
	cout << endl;

	cout << "Recursively:";
	PrintListRecursively(head->m_pNext);
	cout << endl;

	freeNode(head);

	return 0;
}