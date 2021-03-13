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

ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
{
    if (!pHead1)
        return pHead2;
    else if (!pHead2)
        return pHead1;

    ListNode *pMergeHead = nullptr;
    if (pHead1->m_nValue < pHead2->m_nValue)
    {
        pMergeHead = pHead1;
        pMergeHead->m_pNext = Merge(pHead1->m_pNext, pHead2);
    }
    else
    {
        pMergeHead = pHead2;
        pMergeHead->m_pNext = Merge(pHead1, pHead2->m_pNext);
    }
    return pMergeHead;
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
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    ListNode *pHead1 = CreateNode(arr1, sizeof(arr1) / sizeof(int));
    ListNode *pHead2 = CreateNode(arr2, sizeof(arr2) / sizeof(int));

    std::cout << "list 1: ";
    PrintNode(pHead1);
    std::cout << std::endl;

    std::cout << "list 2: ";
    PrintNode(pHead2);
    std::cout << std::endl;

    ListNode *pMergedHead = Merge(pHead1, pHead2);
    std::cout << "merged list: ";
    PrintNode(pMergedHead);
    std::cout << std::endl;

    return 0;
}
