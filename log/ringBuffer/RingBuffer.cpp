#include <chrono>
#include <thread>
#include <cstring>
#include <iostream>
#include "RingBuffer.h"
#include "Utility.h"

RingBuffer::RingBuffer()
    : m_readPos(0),
      m_writePos(0),
      m_consumablePos(0),
      m_trytime(0)
{
}

void RingBuffer::reset()
{
    m_writePos = m_readPos = 0;
}

size_t RingBuffer::reableBytes() const
{
    return m_writePos - m_readPos;
}

size_t RingBuffer::writableBytes() const
{
    return _SIZE_ - m_writePos + m_readPos;
}

size_t RingBuffer::offsetOfPos(size_t pos) const
{
    return pos & (_SIZE_ - 1);
}

size_t RingBuffer::consumableSize() const
{
    return m_consumablePos - m_readPos;
}

void RingBuffer::incConsumablePos(size_t len)
{
    m_consumablePos += len;
}

void RingBuffer::append(const char *from, size_t len)
{
    m_trytime = 0;

    while (len > writableBytes())
    {
        if (m_trytime++ > 3)
            return;

        std::this_thread::sleep_for(std::chrono::microseconds(50));
    }

    auto off2End = std::min(len, _SIZE_ - offsetOfPos(m_writePos));

    memcpy(m_buffer + offsetOfPos(m_writePos), from, off2End);

    memcpy(m_buffer, from + off2End, len - off2End);

    m_writePos += len;

#ifdef STATISTICS
    statistics(from, len);
#endif
}

size_t RingBuffer::retrieve(char *to, size_t len)
{
    auto avail = std::min(consumableSize(), len);

    auto off2End = std::min(avail, _SIZE_ - offsetOfPos(m_readPos));

    memcpy(to, m_buffer + offsetOfPos(m_readPos), off2End);

    memcpy(to + off2End, m_buffer, avail - off2End);

    m_readPos += avail;

    return avail;
}

void RingBuffer::statistics(const char *buf, size_t len)
{
    std::cout << "-------buffer info-------" << std::endl;
    std::cout << "thread: " << detail::gettid() << std::endl;
    std::cout << "size: " << _SIZE_ << std::endl;
    std::cout << "readPos: " << m_readPos << std::endl;
    std::cout << "offsetOfReadPos: " << offsetOfPos(m_readPos) << std::endl;
    std::cout << "consumePos: " << m_consumablePos << std::endl;
    std::cout << "writePos: " << m_writePos << std::endl;
    std::cout << "offsetOfWritePos: " << offsetOfPos(m_writePos) << std::endl;
    std::cout << "readable size: " << reableBytes() << std::endl;
    std::cout << "writable size: " << writableBytes() << std::endl;
    std::cout << "append: " << std::string(buf, len) << "\n\n";
}