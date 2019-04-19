#pragma once


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Message																	// -V690
{
    friend class Transceiver;
public:
    explicit Message();
    explicit Message(uint size, uint8);
    explicit Message(uint size, uint8, uint8);
    explicit Message(uint size, uint8, uint8, uint);
    explicit Message(uint size, uint8, uint, uint);
    explicit Message(uint size, uint8, uint8, uint8);
    explicit Message(uint size, uint8, uint8, float);
    explicit Message(uint size, uint8, uint8, uint64);
    explicit Message(uint8, char*);
    explicit Message(uint8, uint8, char *);
    explicit Message(uint8, uint8, uint8, char *);
    explicit Message(uint8, uint, char*);

    ~Message();

    void Create(uint size, uint8);
    void Create(uint size, uint8, uint8);
    void Create(uint size, uint8, uint, uint);
    void Create(uint size, uint8, uint8, uint8);
    void Create(uint size, uint8, uint8, float);
    void Create(uint size, uint8, uint8, uint8, uint16);
    void Create(uint8, uint8, uint8, char *string);
    void Create(uint8, uint8, char *string);
    void Create(uint8, uint, char *);
    void Create(uint size, uint8 com, uint8 d0, uint d1);
    /// ���������� ��������� �� ��������� �����
    Message *Clone();
    /// ���������� ��������� ����������� ����������.
    void ResetPointer() { taken = 0; };

    bool CreateFromMessage(Message *message);
    /// ������� ��������� � ���������� ������
    bool CreateAllocate(uint8 *buffer, uint size);
    /// �������� ����������� ���������� ������
    bool AllocateMemory(uint size);
    /// ����� ����
    uint8 TakeByte();
    /// ����� ���������
    uint16 TakeHalfWord();
    /// ����� �����
    uint TakeWord();

    uint64 TakeDoubleWord();

    float TakeFloat();
    /// ����� ���������� ������. ����� ������ ���� ������� �������� �� ��������� ������ ������
    void TakeRemainigData(uint8 *data);
    /// ���������� ��������� �� ���������� ������. ������ ����� ������� �����
    uint8 *RemainingData() const;
    /// ���������� ������
    void FreeMemory();
    /// ���������� ��������� �� ������
    uint8 *Data(int pos = 0);
    /// ���������� ������ ������
    uint Size() const;
    /// ���������� true, ���� ��� null-����� (������ �� ��������)
    bool IsEmpty() const;
    /// ���������� true, ���� ��������� ���������
    bool IsEquals(const Message *message) const;
    /// ���������� ��������� �� pos-� �������. ������ ��� ����������� �����
    char *String(int pos);

    pString Trace();
    /// �������� �����
    void PutWord(uint data);
    /// �������� ������
    void PutData(uint8 *data, uint length);
    /// �������� ��������� ����������
    void Transmit();

protected:
    /// �������� ����
    void PutByte(uint8 data);
    /// �������� �������� �����
    void PutHalfWord(int16 data);

    void PutHalfWord(uint16 data);
    /// �������� float
    void PutFloat(float data);
    /// ������ ���������� ������
    uint allocated;
    /// ����� ������ ������, ���� 0, ���� ������ �� ��������
    uint8 *buffer;
    /// ������� ������ ������ ��������� �������. ������������ ��� Put
    uint used;
    /// �� ����� ������� ���������. ������������ ��� Take
    uint taken;

    Message(const Message &) {};
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ��������� - ��� ������ ����� ������������
class MessageRequestData : public Message
{
public:
    MessageRequestData();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������/��������� �����
class MessageEnableChannel : public Message
{
public:
    /// ch : 0 - A, 1 - B
    /// enable : 0 - ���������, 1 - ��������
    MessageEnableChannel(uint8 ch, uint8 enable);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ����� �������
class MessageSetFromWave : public Message
{
public:
    MessageSetFromWave(uint8 ch, uint8 form);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� �������
class MessageSetFrequency : public Message
{
public:
    MessageSetFrequency(uint8 ch, uint64 frequency);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ���������
class MessageSetAmplitude : public Message
{
public:
    MessageSetAmplitude(uint8 ch, uint64 amplitude);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� �������� ������� �� ������
class MessageSetOffset : public Message
{
public:
    MessageSetOffset(uint8 ch, uint64 offset);
};





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ��������� �����������
class MessageFreqMeasure : public Message
{
public:
    MessageFreqMeasure(uint frequency);
};

