#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Transceiver.h"
#include "Hardware/CPU.h"
#include "Hardware/Modules/SPI.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Transceiver::Send(Packet *packet)
{
    SPI4_::WaitFalling();                                               // ������� �������� ����� ���������� ������� � ��������� "��������"

    Packet recvPacket;                                                  // ���� ����� ��������� �����

    for (int i = 0; i < 2; i++)                                         // ������ �������� �������� ����������, ����� ���������� ����� ����������� � �������� � ������� ����� � � �������������
    {
        if (!SPI4_::Transmit(packet->Begin(), packet->Size()))          // �������� �����
        {
            return false;
        }

        if (!SPI4_::Receive(recvPacket.Begin(), recvPacket.Size()))     // � ��������� �����
        {
            return false;
        }
    }

    return recvPacket.IsEquals(packet);                                 // ���������� false, ���� ���������� � �������� ������ �� ���������
}
