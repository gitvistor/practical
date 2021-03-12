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

ListNode *ReverseList(ListNode *pHead)
{
    ListNode *pReversedHead = nullptr;
    ListNode *pNode = pHead;
    ListNode *pPrev = nullptr;
    while (pNode)
    {
        ListNode *pNext = pNode->m_pNext;
        if (!pNext)
            pReversedHead = pNode;

        pNode->m_pNext = pPrev;
        pPrev = pNode;
        pNode = pNext;
    }

    return pReversedHead;
}

void PrintNode(ListNode *pHead)
{
    if (!pHead)
        return;

    ListNode *pNode = pHead;
    while (pNode)
    {
        std::cout << pNode->m_nValue << ' ';
        pNode = pNode->m_pNext;
    }
}

int main(int argc, const char *argv[])
{
    int arr[] = {1, 2, 3, 4, 5, 6};
    ListNode *pHead = CreateNode(arr, sizeof(arr) / sizeof(int));

    std::cout << "original list: ";
    PrintNode(pHead);
    std::cout << std::endl;

    ListNode *pReversedHead = ReverseList(pHead);
    std::cout << "reversed list: ";
    PrintNode(pReversedHead);

    std::cout << std::endl;

    return 0;
}
