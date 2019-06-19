#pragma once


namespace SPI4_
{
    void Init();
    /// ��������� ������ ������
    bool Transmit(const void *buffer, uint size, uint timeout);

    bool Transmit(uint value, uint timeout);
    /// ������� ������ ������
    bool Receive(void *recv, uint size, uint timeout);
    /// ������� ��������� size ���� � ���������� �� � compared. ���������� ���������� ��������� ����
    uint ReceiveAndCompare(const void *compared, uint size);
    /// ���������� true, ���� ������ ����� � ������
    bool IsReady();
    /// ����� ���� ����������� ����������
    void WaitFreedom();
    /// �������� �������� ������� ���������� �� ��������� "�����" � ��������� "��������"
    void WaitFalling();
};
