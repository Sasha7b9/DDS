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
bool Transceiver::Send(Message *message)
{
    SPI4_::WaitFalling();                                               // ������� �������� ����� ���������� ������� � ��������� "��������"

    Message recvMessage;                                                // ���� ����� ��������� �����

    for (int i = 0; i < 2; i++)
    {
        uint size = message->Size();
        if (!SPI4_::Transmit(&size, 4))                                 // ������� ������ ������������ ������
        {
            return false;
        }

        if (!SPI4_::Transmit(message->Data(), message->Size()))         // ������� ��������������� ������
        {
            return false;
        }

        uint newSize = 0;
        if (!SPI4_::Receive(&newSize, 4))                               // ������ ��������� ������ ������, ������� ����� �������� ��� ����������
        {
            return false;
        }

        recvMessage.AllocateMemory(newSize);                            // �������� ����������� ���������� ������ ��� ����������� ������
        if (!SPI4_::Receive(recvMessage.Data(), recvMessage.Size()))    // � ��������� ����� ���������� ����������
        {
            return false;
        }
    }

    bool result = recvMessage.IsEquals(message);

    if (!result)
    {
        LOG_WRITE_FINALIZE("�������� ����� �� ��������� � ����������");
    }

    return result;
}
