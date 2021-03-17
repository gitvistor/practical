#include <iostream>
#include <stack>
#include <ctime>
#include <random>
#include <cassert>
#include <iomanip>

using namespace std;

template <typename T>
class StackWithMin
{
public:
    void push(const T &value);
    void pop();
    const T &top();
    const T &min();
    bool empty();

private:
    std::stack<T> m_data;
    std::stack<T> m_min;
};

template <typename T>
void StackWithMin<T>::push(const T &value)
{
    m_data.push(value);
    if (m_min.empty() || value < m_min.top())
        m_min.push(value);
    else
        m_min.push(m_min.top());
}

template <typename T>
void StackWithMin<T>::pop()
{
    assert(!m_data.empty() && !m_min.empty());
    m_data.pop();
    m_min.pop();
}

template <typename T>
const T &StackWithMin<T>::top()
{
    assert(!m_data.empty() && !m_min.empty());
    return m_data.top();
}

template <typename T>
const T &StackWithMin<T>::min()
{
    assert(!m_data.empty() && !m_min.empty());
    return m_min.top();
}

template <typename T>
bool StackWithMin<T>::empty()
{
    return m_data.empty();
}

#define WIDTH 5

int main(int argc, const char *argv[])
{
    std::default_random_engine engine(time(NULL));
    std::uniform_int_distribution<int> distributor(10, 200);
    StackWithMin<int> stk;
    std::cout << "push: ";
    for (auto i = 0; i < 10; i++)
    {
        auto value = distributor(engine);
        stk.push(value);
        std::cout << value << ' ';
    }
    std::cout << "\n";
    std::cout << std::setw(WIDTH) << "top" << std::setw(WIDTH) << "min" << std::endl;
    while (!stk.empty())
    {
        std::cout << std::setw(WIDTH) << stk.top() << std::setw(WIDTH) << stk.min() << std::endl;
        stk.pop();
    }
    std::cout << std::endl;

    return 0;
}
