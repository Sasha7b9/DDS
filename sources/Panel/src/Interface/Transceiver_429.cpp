#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Transceiver.h"
#include "Hardware/CPU.h"
#include "Hardware/Modules/SPI.h"
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Transceiver::Send(Packet *packet)
{
    if (SPI4_::IsReady())
    {
        return false;                                               // ����� �� �������, ���� ��������� ��������� � ������ ��������. ��� ������ ��������� ����
    }

    SPI4_::WaitFreedom();                                      // ����� ���, ���� ������ ������� �� ��������� "�����" � ��������� "�����"

    if (!SPI4_::Transmit(packet->Begin(), packet->Size()))     // �������� �����
    {
        return false;
    }

    Packet recvPacket;

    if (!SPI4_::Receive(recvPacket.Begin(), recvPacket.Size()))    // � ��������� �����
    {
        return false;
    }

    return recvPacket.IsEquals(packet);                                 // ���������� false, ���� ���������� � �������� ������ �� ���������
}
