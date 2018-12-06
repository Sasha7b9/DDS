#pragma once


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Message
{
public:
    explicit Message();
    explicit Message(uint size, uint8);
    explicit Message(uint size, uint8, uint8);
    explicit Message(uint size, uint8, uint);
    explicit Message(uint size, uint8, uint, uint);
    explicit Message(uint size, uint8, uint8, uint8);
    explicit Message(uint size, uint8, uint8, float);
    explicit Message(uint8, char*);
    explicit Message(uint8, uint8, char *);
    explicit Message(uint size, uint8, uint8, uint64);

    ~Message();

    void Create(uint size, uint8);
    void Create(uint size, uint8, uint8);
    void Create(uint size, uint8, uint);
    void Create(uint size, uint8, uint, uint);
    void Create(uint size, uint8, uint8, uint8);
    void Create(uint size, uint8, uint8, float);
    void Create(uint size, uint8, uint8, uint8, uint16);
    void Create(uint8, uint8, char *string);
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
    uint8 *Data(int pos = 0);
    /// ���������� ������ ������
    uint Size() const;
    /// ���������� true, ���� ��� null-����� (������ �� ��������)
    bool IsEmpty() const;
    /// ���������� true, ���� ��������� ���������
    bool IsEquals(const Message *message) const;
    /// ���������� ��������� �� pos-� �������. ������ ��� ����������� �����
    char *String(int pos);

private:
    /// �������� ����
    void PutByte(uint8 data);
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
