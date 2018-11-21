#pragma once


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Message
{
public:
    Message();

    ~Message();

    bool CreateFromMessage(Message *message);
    /// ������� ��������� � ���������� ������
    bool CreateAllocate(uint8 *buffer, uint size);
    /// ������� ��������� ��� ��������� ������. ������������ ��������������� ������� �����
    bool CreateUsed(uint8 *buffer, uint size);
    /// �������� ����������� ���������� ������
    bool AllocateMemory(uint size);
    /// �������� ����
    void Put8(uint8 data);
    /// �������� �����
    void Put32(uint data);
    /// ����� ����
    uint8 Take8();
    /// ����� �����
    uint Take32();
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
    /// ������ ���������� ������
    uint allocated;
    /// ����� ������ ������, ���� 0, ���� ������ �� ��������
    uint8 *buffer;
    /// ������� ������ ������ ��������� �������. ������������ ��� Put
    uint used;
    /// �� ����� ������� ���������. ������������ ��� Take
    uint taken;
};
