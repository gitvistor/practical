#include <iostream>
#include <vector>
#include <ctime>
#include <random>

using namespace std;

struct ComplexListNode
{
    int m_nValue;
    ComplexListNode *m_pNext;
    ComplexListNode *m_pSibling;
};

ComplexListNode *CreateNode(int *arr, int length)
{
    if (!arr || length <= 0)
        return nullptr;

    ComplexListNode *pHead{nullptr};
    ComplexListNode *pNext{nullptr};
    std::vector<ComplexListNode *> vec;
    vec.reserve(length);

    for (int i = 0; i < length; i++)
    {
        ComplexListNode *pNode = new ComplexListNode();
        pNode->m_nValue = arr[i];
        pNode->m_pNext = nullptr;
        pNode->m_pSibling = nullptr;
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
        vec.emplace_back(pNode);
    }

    std::default_random_engine e(time(NULL));
    std::uniform_int_distribution<> d(0, length - 1);

    for (pNext = pHead; pNext != nullptr; pNext = pNext->m_pNext)
    {
        auto index = d(e);
        if (vec[index])
        {
            pNext->m_pSibling = vec[index];
            vec[index] = nullptr;
        }
    }
    return pHead;
}

void CloneNodes(ComplexListNode *pHead)
{
    ComplexListNode *pNode = pHead;
    while (pNode)
    {
        ComplexListNode *pCloned = new ComplexListNode();
        pCloned->m_nValue = pNode->m_nValue;
        pCloned->m_pNext = pNode->m_pNext;
        pCloned->m_pSibling = nullptr;

        pNode->m_pNext = pCloned;
        pNode = pCloned->m_pNext;
    }
}

void ConnectSiblingNodes(ComplexListNode *pHead)
{
    ComplexListNode *pNode = pHead;
    while (pNode)
    {
        ComplexListNode *pCloned = pNode->m_pNext;
        if (pNode->m_pSibling)
        {
            pCloned->m_pSibling = pNode->m_pSibling->m_pNext;
        }
        pNode = pCloned->m_pNext;
    }
}

ComplexListNode *ReconnectNodes(ComplexListNode *pHead)
{
    ComplexListNode *pNode = pHead;
    ComplexListNode *pClonedHead = nullptr;
    ComplexListNode *pClonedNode = nullptr;

    if (pNode)
    {
        pClonedHead = pClonedNode = pNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }

    while (pNode)
    {
        pClonedNode->m_pNext = pNode->m_pNext;
        pClonedNode = pClonedNode->m_pNext;
        pNode->m_pNext = pClonedNode->m_pNext;
        pNode = pNode->m_pNext;
    }

    return pClonedHead;
}

ComplexListNode *Clone(ComplexListNode *pHead)
{
    CloneNodes(pHead);
    ConnectSiblingNodes(pHead);
    return ReconnectNodes(pHead);
}

void PrintNode(ComplexListNode *pHead)
{
    if (!pHead)
        return;

    ComplexListNode *pNode = pHead;
    while (pNode)
    {
        std::cout << pNode->m_nValue << ' ';
        pNode = pNode->m_pNext;
    }
}

int main(int argc, const char *argv[])
{
    int arr[] = {5, 4, 12, 8, 10, 7};
    ComplexListNode *pHead = CreateNode(arr, sizeof(arr) / sizeof(int));

    std::cout << "list data: ";
    PrintNode(pHead);
    std::cout << std::endl;

    ComplexListNode *pClonedHead = Clone(pHead);
    std::cout << "clone data: ";
    PrintNode(pClonedHead);
    std::cout << std::endl;

    return 0;
}
