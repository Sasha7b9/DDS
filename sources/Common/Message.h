#pragma once


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Message
{
public:
    Message();
    Message(uint size, uint8 v0);
    Message(uint size, uint8 value0, uint8 value1);
    Message(uint size, uint8 value0, uint8 value1, uint8 value2);

    ~Message();

    void Create(uint size, uint8 v0);
    void Create(uint size, uint8 v0, uint v1);
    void Create(uint size, uint8 v0, uint8 v1, uint8 v2, uint16 v3);

    bool CreateFromMessage(Message *message);
    /// ������� ��������� � ���������� ������
    bool CreateAllocate(uint8 *buffer, uint size);
    /// �������� ����������� ���������� ������
    bool AllocateMemory(uint size);
    /// �������� �������� �����
    void PutHalfWord(int16 data);
    void PutHalfWord(uint16 data);
    /// �������� �����
    void PutWord(uint data);
    /// �������� float
    void PutFloat(float data);
    /// ����� ����
    uint8 TakeByte();
    /// ����� ���������
    uint16 TakeHalfWord();
    /// ����� �����
    uint TakeWord();

    uint64 TakeDoubleWord();

    float TakeFloat();
    /// ���������� ������
    void FreeMemory();
    /// ���������� ��������� �� ������
    uint8 *Data();
    /// ���������� ������ ������
    uint Size() const;
    /// ���������� true, ���� ��� null-����� (������ �� ��������)
    bool IsEmpty() const;
    /// ���������� true, ���� ��������� ���������
    bool IsEquals(const Message *message) const;

private:
    /// �������� ����
    void PutByte(uint8 data);


    /// ������ ���������� ������
    uint allocated;
    /// ����� ������ ������, ���� 0, ���� ������ �� ��������
    uint8 *buffer;
    /// ������� ������ ������ ��������� �������. ������������ ��� Put
    uint used;
    /// �� ����� ������� ���������. ������������ ��� Take
    uint taken;
};
