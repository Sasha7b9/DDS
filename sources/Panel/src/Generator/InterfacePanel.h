#pragma once


class Interface
{
public:
    /// ������� � ���������� ������ �� ����
    static void ProcessDataFPGA();
    /// ������� � ��������� ������
    static void Send(const uint8 *buffer, uint16 size);

    static void Send(const Buffer &buffer);
    /// ������� numBytes ���� �� ���� � ��������� ��
    static void ReceiveAndRun(uint16 numBytes);
};
