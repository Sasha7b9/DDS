#pragma once


/*
    ����� ��� ��������� ������������ raw-��������� (��������� ��� ��� ������� � Command.h
*/

class RawMessage
{
public:
    /// ������������ ��������� ������ size
    RawMessage(uint size);
    ~RawMessage();
private:
    /// ��������� �� ������ ���������
    uint8 *buffer;
    /// ���������� ����, ���������� ��� ���������
    uint allocated;
    /// ���������� �������� ���� � ���������
    uint used;
};
