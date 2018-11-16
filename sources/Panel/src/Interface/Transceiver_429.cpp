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
        return false;                   // ����� �� �������, ���� ��������� ��������� � ������ ��������. ��� ������ ��������� ����
    }

    CPU::SPI4_::WaitFreedom();          // ����� ���, ���� ������ ������� �� ��������� "�����" � ��������� "�����"

    CPU::SPI4_::Transmit(packet->Begin(), packet->Size());

    Packet recvPacket;

    CPU::SPI4_::Receive(recvPacket.Begin(), recvPacket.Size());

    return recvPacket.IsEquals(packet);
}
