#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

#define ADD(x, y) (x) + (y)

int count = 1;
std::mutex mtx;

void run()
{
    int num = count;
    const char *prun = "runstr";
    for (;;)
    {
        std::cout << num << std::endl;
        mtx.lock();
        count++;
        mtx.unlock();
        num = count;
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
}

struct TEST_NODE
{
    char gender[10];
    int ID;
    char name[32];
};

void test_memory(int &num)
{
    const char *str = "hello";
    int number = 0x12345678;

    TEST_NODE *node = new TEST_NODE;
    node->ID = 100;
    strcpy(node->gender, "man");
    strcpy(node->name, "haiyang");
    printf("str is %s, number id is %d, test end\n", str, number, node->ID);
    delete node;

    number = 234;

    int iArray[] = {23, 4, 59, 12, 3};
    const char *strArray[] = {"kei", "eoo", "ciw", "akei"};

    int i = 0;
    while (i < sizeof(iArray) / sizeof(int))
    {
        iArray[i++]++;
    }

    i = 0;
    int len = sizeof(strArray) / sizeof(char *);
    while (2 * i < len)
    {
        const char *temp = strArray[i];
        strArray[i] = strArray[len - 1 - i];
        strArray[len - 1 - i] = temp;
        i++;
    }

    num++;
}

void cond_fun_test(int a, const char *pstr)
{
    for (int i = 0; i < 5; i++)
    {
        a++;
    }

    printf("a is %d,str is %s\n", a, pstr);
}

int main(int argc, char *argv[])
{
    int num = ADD(2, 3);

    test_memory(num);

    std::string str = "watch";
    const char *pstr = "hello";
    cond_fun_test(num, pstr);

    num++;

    std::thread t1{run};
    std::thread t2{run};
    t1.join();
    t2.join();

    return 0;
}
