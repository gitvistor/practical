#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

#define DEFAULT_CAPACITY 100

template <typename T>
class BlockingQueue
{
public:
    explicit BlockingQueue(size_t capacity = DEFAULT_CAPACITY);
    ~BlockingQueue();
    BlockingQueue(const BlockingQueue<T> &) = delete;
    BlockingQueue &operator=(const BlockingQueue<T> &) = delete;
    bool put(const T &item);
    bool take(T &item);
    bool take(T &item, int waitTime);
    T front();
    T back();
    bool empty();
    bool full();
    size_t size();
    size_t capacity();
    void close();

private:
    std::queue<T> m_queue;
    size_t m_capacity;
    bool m_closed;
    std::mutex m_mtx;
    std::condition_variable m_consumer;
    std::condition_variable m_producer;
};

template <typename T>
BlockingQueue<T>::BlockingQueue(size_t capacity)
    : m_capacity(capacity), m_closed(false)
{
}

template <typename T>
BlockingQueue<T>::~BlockingQueue()
{
    close();
}

template <typename T>
bool BlockingQueue<T>::put(const T &item)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_producer.wait(lock, [this]() {
        return m_queue.size() < m_capacity || m_closed;
    });

    if (m_closed)
        return false;
    
    m_queue.push(item);
    m_consumer.notify_one();
    return true;
}

template <typename T>
bool BlockingQueue<T>::take(T &item)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_consumer.wait(lock, [this]() {
        return !m_queue.empty() || m_closed;
    });

    if (m_closed)
        return false;
    
    item = m_queue.front();
    m_queue.pop();
    m_producer.notify_one();
    return true;
}

template <typename T>
bool BlockingQueue<T>::take(T &item, int waitTime)
{
    std::unique_lock<std::mutex> lock(m_mtx);

    if (!m_consumer.wait_for(lock, std::chrono::seconds{waitTime}, [this]() {
            return !m_queue.empty() || m_closed;
        }))
    {
        return false;
    }

    if (m_closed)
        return false;

    item = m_queue.front();
    m_queue.pop();
    m_producer.notify_one();
    return true;
}

template <typename T>
T BlockingQueue<T>::front()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_queue.front();
}

template <typename T>
T BlockingQueue<T>::back()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_queue.back();
}

template <typename T>
bool BlockingQueue<T>::empty()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_queue.empty();
}

template <typename T>
bool BlockingQueue<T>::full()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_queue.size() >= m_capacity;
}

template <typename T>
size_t BlockingQueue<T>::size()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_queue.size();
}

template <typename T>
size_t BlockingQueue<T>::capacity()
{
    return m_capacity;
}

template <typename T>
void BlockingQueue<T>::close()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    if (m_closed)
        return;
    
    while (!m_queue.empty())
    {
        m_queue.pop();
    }
    m_closed = true;
    m_producer.notify_all();
    m_consumer.notify_all();
}