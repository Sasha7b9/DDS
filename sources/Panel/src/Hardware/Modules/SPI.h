#pragma once


class SPI4_
{
friend class CPU;
private:
    static void Init();
public:
    /// ��������� ������ ������
    static bool Transmit(const void *buffer, uint size, uint timeout = 200);
    /// ������� ������ ������
    static bool Receive(void *recv, uint size, uint timeout = 200);
    /// ������� ��������� size ���� � ���������� �� � compared. ���������� true, ���� ����� ���������
    static bool ReceiveAndCompare(const void *compared, uint size);
    /// ���������� true, ���� ������ ����� � ������
    static bool IsReady();
    /// ����� ���� ����������� ����������
    static void WaitFreedom();
    /// �������� �������� ������� ���������� �� ��������� "�����" � ��������� "��������"
    static void WaitFalling();
};
