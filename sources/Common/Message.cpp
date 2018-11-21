#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "Message.h"
#include "Hardware/CPU.h"
#include <cstring>
#include <cstdlib>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Message::Message() : allocated(0), buffer(0), used(0)
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::~Message()
{
    FreeMemory();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Message::CreateFromRawData(uint8 *_buffer, uint _size)
{
    if (AllocateMemory(_size))
    {
        std::memcpy(buffer, _buffer, _size);
    }

    return buffer != 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Message::CreateFromMessage(Message *message)
{
    if (AllocateMemory(message->Size()))
    {
        std::memcpy(buffer, message->Data(), message->Size());
    }

    return buffer != 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::Put(uint8 data)
{
    if (used < allocated)
    {
        buffer[used] = data;
        used++;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Message::AllocateMemory(uint size)
{
    FreeMemory();

    if (size == 0)
    {
        return false;
    }

    buffer = (uint8 *)std::malloc(size);
    if (buffer)
    {
        allocated = size;
    }
    else
    {
        LOG_WRITE("�� ���� �������� %d ����", size);
    }

    return buffer != 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::FreeMemory()
{
    allocated = 0;
    used = 0;
    std::free(buffer);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 *Message::Data()
{
    return buffer;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint Message::Size() const
{
    return allocated;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Message::IsEmpty() const
{
    return buffer != 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Message::IsEquals(const Message *message) const
{
    if (Size() != message->Size())
    {
        return false;
    }

    return std::memcmp(((Message *)message)->Data(), ((Message *)this)->Data(), Size()) == 0;
}
