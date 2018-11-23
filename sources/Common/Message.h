#pragma once


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Message
{
public:
    Message();
    Message(uint size, uint8);
    Message(uint size, uint8, uint8);
    Message(uint size, uint8, uint);
    Message(uint size, uint8, uint, uint);
    Message(uint size, uint8, uint8, uint8);
    Message(uint size, uint8, uint8, float);

    ~Message();

    void Create(uint size, uint8);
    void Create(uint size, uint8, uint8);
    void Create(uint size, uint8, uint);
    void Create(uint size, uint8, uint, uint);
    void Create(uint size, uint8, uint8, uint8);
    void Create(uint size, uint8, uint8, float);
    void Create(uint size, uint8, uint8, uint8, uint16);
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

    /// �������� ����
    void PutByte(uint8 data);
private:
    /// �������� �������� �����
    void PutHalfWord(int16 data);
    void PutHalfWord(uint16 data);
    /// �������� �����
    void PutWord(uint data);
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
};
