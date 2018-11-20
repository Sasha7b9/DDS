#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "Transceiver.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
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
            LOG_WRITE_FINALIZE("�������� �� �������");
            return false;
        }

        if (!SPI4_::Receive(recvPacket.Begin(), recvPacket.Size()))     // � ��������� �����
        {
            LOG_WRITE_FINALIZE("������������� �� ���������");
            return false;
        }
    }

    if (!recvPacket.IsEquals(packet))
    {
        LOG_WRITE_FINALIZE("������ �� ���������");
    }

    return recvPacket.IsEquals(packet);                                 // ���������� false, ���� ���������� � �������� ������ �� ���������
}
