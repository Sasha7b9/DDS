#pragma once


/*
    ����� ��� ��������� ������������ raw-��������� (��������� ��� ��� ������� � Command.h
*/

class RawData
{
public:
    /// ������������ ��������� ������ size
    RawData(uint size);
    RawData(uint size, uint8 value0, uint8 valu1);
    ~RawData();

    void Put(uint8 value);
    void Put(float value);

    uint8 *Data() { return buffer; }
    uint Size() const { return used; }

private:

    void Alloc(uint size);
    /// ��������� �� ������ ���������
    uint8 *buffer;
    /// ���������� ����, ���������� ��� ���������
    uint allocated;
    /// ���������� �������� ���� � ���������
    uint used;
};
