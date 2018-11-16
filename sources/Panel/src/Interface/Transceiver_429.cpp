#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Transceiver.h"
#include "Hardware/CPU.h"
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Transceiver::Send(Packet *packet)
{
    if (CPU::SPI4_::IsReady())
    {
        return false;                                               // ����� �� �������, ���� ��������� ��������� � ������ ��������. ��� ������ ��������� ����
    }

    CPU::SPI4_::WaitFreedom();                                      // ����� ���, ���� ������ ������� �� ��������� "�����" � ��������� "�����"

    if (!CPU::SPI4_::Transmit(packet->Begin(), packet->Size()))     // �������� �����
    {
        return false;
    }

    Packet recvPacket;

    if (!CPU::SPI4_::Receive(recvPacket.Begin(), recvPacket.Size()))    // � ��������� �����
    {
        return false;
    }

    return recvPacket.IsEquals(packet);                                 // ���������� false, ���� ���������� � �������� ������ �� ���������
}
