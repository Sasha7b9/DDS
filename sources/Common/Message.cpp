#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "structs.h"
#include "Command.h"
#include "Message.h"
#include "Hardware/CPU.h"
#include "log.h"
#include <cstring>
#include <cstdlib>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Message::Message() : allocated(0), buffer(0), used(0), taken(0)
{

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::~Message()
{
    FreeMemory();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::Message(uint8 v0, char *string) : allocated(0), buffer(0), used(0), taken(0)
{
    //          v0 | string              | �����������_����
    uint size = 1 +  std::strlen(string) + 1;

    Create(size, v0);

    std::strcpy(String(1), string);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::Message(uint8 v0, uint8 v1, char *string) : allocated(0), buffer(0), used(0), taken(0)
{
    Create(v0, v1, string);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::Message(uint8 v0, uint8 v1, uint8 v2, char *string) : allocated(0), buffer(0), used(0), taken(0)
{
    Create(v0, v1, v2, string);
}

Message::Message(uint8 d0, uint d1, char *string) : allocated(0), buffer(0), used(0), taken(0)
{
    Create(d0, d1, string);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::Message(uint size, uint8 v0) : allocated(0), buffer(0), used(0), taken(0)
{
    Create(size, v0);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::Message(uint size, uint8 v0, uint v1, uint v2) : allocated(0), buffer(0), used(0), taken(0)
{
    Create(size, v0, v1, v2);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::Message(uint size, uint8 com, uint8 d0, uint d1) : allocated(0), buffer(0), used(0), taken(0)
{
    Create(size, com, d0, d1);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::Message(uint size, uint8 v0, uint8 v1) : allocated(0), buffer(0), used(0), taken(0)
{   
    Create(size, v0, v1);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::Message(uint size, uint8 v0, uint8 v1, uint8 v2) : allocated(0), buffer(0), used(0), taken(0)
{
    Create(size, v0, v1, v2);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::Message(uint size, uint8 v0, uint8 v1, float v2) : allocated(0), buffer(0), used(0), taken(0)
{
    Create(size, v0, v1, v2);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message::Message(uint size, uint8 v0, uint8 v1, uint64 v2) : allocated(0), buffer(0), used(0), taken(0)
{
    Create(size, v0, v1);

    BitSet64 bs(v2);

    for (int i = 0; i < 8; i++)
    {
        PutByte(bs.byte[i]);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Message *Message::Clone()
{
    Message *result = new Message();
    if (result->AllocateMemory(Size()))
    {
        std::memcpy(result->buffer, buffer, allocated);
        result->used = used;
        result->taken = taken;
    }
    
    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::Create(uint size, uint8 v0)
{
    if (AllocateMemory(size))
    {
        PutByte(v0);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::Create(uint size, uint8 v0, uint v1, uint v2)
{
    if (AllocateMemory(size))
    {
        PutByte(v0); //-V525
        PutWord(v1);
        PutWord(v2);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::Create(uint size, uint8 com, uint8 d0, uint d1)
{
    if (AllocateMemory(size))
    {
        PutByte(com);
        PutByte(d0);
        PutWord(d1);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::Create(uint size, uint8 v0, uint8 v1)
{
    if (AllocateMemory(size))
    {
        PutByte(v0);
        PutByte(v1);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::Create(uint8 v0, uint8 v1, char *string)
{
    //          v0 | v1 | string              | �����������_����
    uint size = 1 +  1 +  std::strlen(string) + 1;

    if (AllocateMemory(size))
    {
        PutByte(v0);
        PutByte(v1);
        std::strcpy(String(2), string);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::Create(uint8 v0, uint8 v1, uint8 v2, char *string)
{
    uint size = 1 + 1 + 1 + std::strlen(string) + 1;
    if (AllocateMemory(size))
    {
        PutByte(v0);
        PutByte(v1);
        PutByte(v2);
        std::strcpy(String(3), string);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::Create(uint8 v0, uint v1, char *string)
{
    //          v0 | v1 | string              | �����������_����
    uint size = 1 + 1 + std::strlen(string) + 1;

    if (AllocateMemory(size))
    {
        PutByte(v0);
        PutWord(v1);
        std::strcpy(String(2), string);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::Create(uint size, uint8 v0, uint8 v1, uint8 v2)
{
    if (AllocateMemory(size))
    {
        PutByte(v0);
        PutByte(v1);
        PutByte(v2);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::Create(uint size, uint8 v0, uint8 v1, float v2)
{
    if (AllocateMemory(size))
    {
        PutByte(v0);
        PutByte(v1);
        PutFloat(v2);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::Create(uint size, uint8 value0, uint8 value1, uint8 value2, uint16 value3)
{
    if (AllocateMemory(size))
    {
        PutByte(value0);
        PutByte(value1);
        PutByte(value2);
        PutHalfWord(value3);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Message::CreateAllocate(uint8 *_buffer, uint _size)
{
    if (AllocateMemory(_size))
    {
        std::memcpy(buffer, _buffer, _size); //-V595
        used = _size;
    }

    return buffer != 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Message::CreateFromMessage(Message *message)
{
    if (AllocateMemory(message->Size()))
    {
        std::memcpy(buffer, message->buffer, message->allocated); //-V595
        used = message->used;
    }

    return buffer != 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::PutByte(uint8 data)
{
     buffer[used] = data;
     used += sizeof(data);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::PutHalfWord(int16 data)
{
    PutHalfWord((uint16)data);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::PutHalfWord(uint16 data)
{
    BitSet16 bs(data);
    bs.WriteToBuffer(buffer + used);
    used += sizeof(data);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::PutWord(uint data)
{
     BitSet32 bs(data);
     bs.WriteToBuffer(buffer + used);
     used += sizeof(data);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::PutData(uint8 *data, uint length)
{
    std::memcpy(buffer + used, data, length);
    used += length;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::PutFloat(float data)
{
    BitSet32 bs(data);
    bs.WriteToBuffer(buffer + used);
    used += sizeof(data);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 Message::TakeByte()
{
    uint8 result = buffer[taken];
    taken += sizeof(result);

    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint16 Message::TakeHalfWord()
{
    BitSet16 bs(buffer + taken);
    uint16 result = bs.halfWord;
    taken += sizeof(result);

    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint Message::TakeWord()
{
    BitSet32 bs(buffer + taken);
    uint result = bs.word;
    taken += sizeof(result);

    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint64 Message::TakeDoubleWord()
{
    BitSet64 bs(buffer + taken);
    uint64 result = bs.dword;
    taken += sizeof(result);

    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float Message::TakeFloat()
{
    BitSet32 bs(buffer + taken);
    float result = bs.floatValue;
    taken += sizeof(result);

    return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::TakeRemainigData(uint8 *data)
{
    uint size = allocated - taken;
    std::memcpy(data, buffer, size);
    taken = allocated;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 *Message::RemainingData() const
{
    return &buffer[taken];
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
        LOG_ERROR_FINALIZE("������������ ������ ��� %x ����", size);
    }

    return buffer != 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Message::FreeMemory()
{
    allocated = 0;
    used = 0;
    std::free(buffer);
    buffer = 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint8 *Message::Data(int pos)
{
    return buffer + pos;
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

    return std::memcmp(message->buffer, buffer, allocated) == 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char *Message::String(int pos)
{
    return (char *)&buffer[pos];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString Message::Trace()
{
    if (Size() == 0)
    {
        return "";
    }

    static Command command(buffer[0]);
    return command.Trace(0);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MessageFreqMeasure::MessageFreqMeasure(uint frequency) : Message(5, Command::FreqMeasure)
{
    PutWord(frequency);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MessageRequestData::MessageRequestData() : Message(1, Command::RequestData)
{
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MessageEnableChannel::MessageEnableChannel(uint8 ch, uint8 enable) : Message(3, Command::EnableChannel)
{
    PutByte(ch);
    PutByte(enable);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MessageSetFromWave::MessageSetFromWave(uint8 ch, uint8 form) : Message(3, Command::SetFormWave)
{
    PutByte(ch);
    PutByte(form);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MessageSetFrequency::MessageSetFrequency(uint8 ch, uint64 frequency) : Message(10, Command::SetFrequency)
{
    PutByte(ch);
    BitSet64 bs(frequency);
    PutWord(bs.word0);
    PutWord(bs.word1);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MessageSetAmplitude::MessageSetAmplitude(uint8 ch, uint64 amplitude) : Message(10, Command::SetAmplitude)
{
    PutByte(ch);
    BitSet64 bs(amplitude);
    PutWord(bs.word0);
    PutWord(bs.word1);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MessageSetOffset::MessageSetOffset(uint8 ch, uint64 offset) : Message(10, Command::SetOffset)
{
    PutByte(ch);
    BitSet64 bs(offset);
    PutWord(bs.word0);
    PutWord(bs.word1);
}
