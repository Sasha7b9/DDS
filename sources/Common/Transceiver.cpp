#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "Packet.h"
#include "Transceiver.h"
#include "Hardware/CPU.h"
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Transceiver::Send(uint8 *buffer, uint size)
{
    Packet packet;

    packet.Create(buffer, size);

    /// ��������� ��������, ���� �� ���������
    while (!Send(&packet))
    {
        //LOG_WRITE_FINALIZE("������ ��������");
    }
    
    LOG_WRITE_FINALIZE("�������� ��������");
}
