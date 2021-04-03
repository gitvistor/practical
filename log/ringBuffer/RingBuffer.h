#pragma once
#include <string>

#define _SIZE_  8192

class RingBuffer
{
public:
    RingBuffer();
    ~RingBuffer() = default;

    void reset();

    size_t reableBytes() const;
    size_t writableBytes() const;

    size_t offsetOfPos(size_t pos) const;
    size_t consumableSize() const;
    void incConsumablePos(size_t len);

    void append(const char *from, size_t len);
    
    size_t retrieve(char *to, size_t len);

    void statistics(const char* buf, size_t len);

private:
    char m_buffer[_SIZE_];
    size_t m_writePos;
    size_t m_readPos;
    size_t m_consumablePos;
    size_t m_trytime;
};
