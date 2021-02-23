#include <iostream>
#include <stack>

using namespace std;

template <typename T>
class CQueue
{
public:
	CQueue() = default;
	~CQueue() = default;
	void appendTail(const T &data);
	T deleteHead();
	bool empty();

private:
	std::stack<T> stack1;
	std::stack<T> stack2;
};

template <typename T>
void CQueue<T>::appendTail(const T &data)
{
	stack1.push(data);
}

template <typename T>
T CQueue<T>::deleteHead()
{
	if (stack2.empty())
	{
		while (!stack1.empty())
		{
			T &data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}

	T head = stack2.top();
	stack2.pop();
	return head;
}

template <typename T>
bool CQueue<T>::empty()
{
	return stack1.empty() && stack2.empty();
}

int main(int argc, char *argv[])
{
	int array[] = {1, 2, 3, 4, 5, 6};
	CQueue<int> queue;
	for (auto &e : array)
		queue.appendTail(e);

	std::cout << "delete data: ";
	while (!queue.empty())
	{
		std::cout << queue.deleteHead() << ' ';
	}
	std::cout << std::endl;

	return 0;
}
