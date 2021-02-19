#pragma once

#include <mutex>
#include <condition_variable>
#include <deque>
#include <chrono>

#define DEFAULT_CAPACITY 100

template <typename T>
class BlockingDeque
{
public:
    explicit BlockingDeque(size_t capacity = DEFAULT_CAPACITY);
    ~BlockingDeque();
    BlockingDeque(const BlockingDeque<T> &) = delete;
    BlockingDeque &operator=(const BlockingDeque<T> &) = delete;
    bool push_front(const T &item);
    bool push_back(const T &item);
    bool pop_front(T &item);
    bool pop_back(T &item);
    bool pop_front(T &item, int waitTime);
    bool pop_back(T &item, int waitTime);
    void clear();
    T front();
    T back();
    bool empty();
    bool full();
    size_t size();
    size_t capacity();
    void close();

private:
    std::deque<T> m_deque;
    size_t m_capacity;
    bool m_closed;
    std::mutex m_mtx;
    std::condition_variable m_consumer;
    std::condition_variable m_producer;
};

template <typename T>
BlockingDeque<T>::BlockingDeque(size_t capacity)
    : m_capacity(capacity), m_closed(false)
{
}

template <typename T>
BlockingDeque<T>::~BlockingDeque()
{
    close();
}

template <typename T>
bool BlockingDeque<T>::push_front(const T &item)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_producer.wait(lock, [this]() {
        return m_deque.size() < m_capacity || m_closed;
    });

    if (m_closed)
        return false;
    
    m_deque.push_front(item);
    m_consumer.notify_one();
    return true;
}

template <typename T>
bool BlockingDeque<T>::push_back(const T &item)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_producer.wait(lock, [this]() {
        return m_deque.size() < m_capacity || m_closed;
    });

    if (m_closed)
        return false;
    
    m_deque.push_back(item);
    m_consumer.notify_one();
    return true;
}

template <typename T>
bool BlockingDeque<T>::pop_front(T &item)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_consumer.wait(lock, [this]() {
        return !m_deque.empty() || m_closed;
    });

    if (m_closed)
        return false;
    
    item = m_deque.front();
    m_deque.pop_front();
    m_producer.notify_one();
    return true;
}

template <typename T>
bool BlockingDeque<T>::pop_back(T &item)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_consumer.wait(lock, [this]() {
        return !m_deque.empty() || m_closed;
    });

    if (m_closed)
        return false;
    
    item = m_deque.back();
    m_deque.pop_back();
    m_producer.notify_one();
    return true;
}

template <typename T>
bool BlockingDeque<T>::pop_front(T &item, int waitTime)
{
    std::unique_lock<std::mutex> lock(m_mtx);

    if (!m_consumer.wait_for(lock, std::chrono::seconds{waitTime}, [this]() {
            return !m_deque.empty() || m_closed;
        }))
    {
        return false;
    }

    if (m_closed)
        return false;

    item = m_deque.front();
    m_deque.pop_front();
    m_producer.notify_one();
    return true;
}

template <typename T>
bool BlockingDeque<T>::pop_back(T &item, int waitTime)
{
    std::unique_lock<std::mutex> lock(m_mtx);

    if (!m_consumer.wait_for(lock, std::chrono::seconds{waitTime}, [this]() {
            return !m_deque.empty() || m_closed;
        }))
    {
        return false;
    }

    if (m_closed)
        return false;

    item = m_deque.back();
    m_deque.pop_back();
    m_producer.notify_one();
    return true;
}

template <typename T>
void BlockingDeque<T>::clear()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    m_deque.clear();
}

template <typename T>
T BlockingDeque<T>::front()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_deque.front();
}

template <typename T>
T BlockingDeque<T>::back()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_deque.back();
}

template <typename T>
bool BlockingDeque<T>::empty()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_deque.empty();
}

template <typename T>
bool BlockingDeque<T>::full()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_deque.size() >= m_capacity;
}

template <typename T>
size_t BlockingDeque<T>::size()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_deque.size();
}

template <typename T>
size_t BlockingDeque<T>::capacity()
{
    return m_capacity;
}

template <typename T>
void BlockingDeque<T>::close()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    if (m_closed)
        return;
    m_deque.clear();
    m_closed = true;
    m_producer.notify_all();
    m_consumer.notify_all();
}