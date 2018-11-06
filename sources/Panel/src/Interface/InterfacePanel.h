#pragma once
#include "Utils/Buffer.h"


class Interface
{
public:
    /// ��� ����� ��������� �� ����������
    static void Update();
    /// ������� � ���������� ������ �� ����
    static void ProcessDataFPGA();
    /// ������� � ��������� ������
    static void Send(const uint8 *buffer, uint size);

    static void Send(const Buffer &buffer);
    /// ������� numBytes ���� �� ���� � ��������� ��
    static void ReceiveAndRun(uint16 numBytes);
};
