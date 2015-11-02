#include "buffer.h"
#include <string.h>
namespace FOS
{

Buffer::Buffer(uint8_t *Memory, size_t Size)
{
    init(Memory,Size);
}

Buffer::Buffer(size_t Size, Buffer *allocFrom)
{
    init(new uint8_t[Size],Size);
}

void Buffer::init(uint8_t *Memory, size_t Size)
{
    memory      = Memory;
    size        = Size;
    writeTo     = 0;
    readFrom    = 0;
    writeable   = true;
    readable    = false;
#ifndef NO_ACCESS
    writeAccess = 0;
    readAccess  = 0;
    access      = BufferDef::ReadWriteAccess;
    if(getSize() == 0)
    {
        access = BufferDef::NoAccess;
    }
#endif// NO_ACCESS
}

bool Buffer::write(uint8_t data)
{
    if(writeable)
    {
        memory[writeTo++] = data;
        if(writeTo == getSize())
            writeTo = 0;
        if(writeTo == readFrom)
            writeable = false;
        readable = true;
        return true;
    }
    return false;
}

bool Buffer::read(uint8_t &data)
{
    if(readable)
    {
        data = memory[readFrom++];
        if(readFrom == getSize())
            readFrom = 0;
        if(readFrom == writeTo)
            readable = false;
        writeable = true;
        return true;
    }
    return false;
}

size_t Buffer::write(uint8_t *data, size_t len)
{
    size_t written = 0;
    for(int i = 0; i < len; ++i)
    {
        if(!write(data[i]))
            return written;
        written++;
    }
    return written;
}

size_t Buffer::read(uint8_t *data, size_t len)
{
    size_t readPastform = 0;
    for(int i = 0; i < len; ++i)
    {
        if(!read(data[i]))
            return readPastform;
        readPastform++;
    }
    return readPastform;
}

bool Buffer::write(uint8_t data, size_t pos, bool asRAM)
{
    size_t writePos = pos;
    if(writePos >= getSize())
        return false; //! @note position do not exist.
    if(!asRAM)
    {
        writePos += writeTo;
        if(writePos >= getSize())
            writePos -= getSize();
        if(isOnHold(writePos))
            return false;
    }
    memory[writePos] = data;
    return true;
}

bool Buffer::read(uint8_t &data, size_t pos, bool asRAM)
{
    size_t readPos = pos;
    if(readPos >= getSize())
        return false; //! @note position do not exist.
    if(!asRAM)
    {
        readPos += readFrom;
        if(readPos >= getSize())
            readPos -= getSize();
        if(!isOnHold(readPos))
            return false;
    }
    data = memory[readPos];
    return true;
}

size_t Buffer::write(uint8_t *data, size_t pos, size_t len, bool asRAM)
{
    size_t written = 0;
    for(int i = 0; i < len; ++i)
    {
        if(!write(data[i],pos+i,asRAM))
            return written;
        written++;
    }
    return written;
}

size_t Buffer::read(uint8_t *data, size_t pos, size_t len, bool asRAM)
{
    size_t readPastform = 0;
    for(int i = 0; i < len; ++i)
    {
        if(!read(data[i],pos+i,asRAM))
            return readPastform;
        readPastform++;
    }
    return readPastform;
}

size_t Buffer::length() const
{
    if(isEmpty())
        return 0;
    else if(isFull())
        return size;
    else
    {
        if(writeTo > readFrom)
            return writeTo - readFrom;
        else
            return size - readFrom + writeTo;
    }
    return 0;
}

inline bool Buffer::isOnHold(size_t pos)
{
    if((writeTo < readFrom)||(isFull()))
        return((pos >= readFrom)||(pos < writeTo));
    else
        return((pos >= readFrom)&&(pos < writeTo));
}



}//namespace FOS
