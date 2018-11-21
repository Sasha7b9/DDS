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
    LOG_WRITE_FINALIZE("������� %d ����. ������� %d", message->Size(), *message->Data());


    SPI4_::WaitFalling();                                               // ������� �������� ����� ���������� ������� � ��������� "��������"

    bool result = false;

    for (int i = 1; i < 3; i++)
    {
        uint size = message->Size();

        if (!SPI4_::Transmit(&size, 4))                                 // ������� ������ ������������ ������
        {
            break;
        }

        if (!SPI4_::Transmit(message->Data(), message->Size()))         // ������� ��������������� ������
        {
            break;
        }

        uint newSize = 0;
        if (!SPI4_::Receive(&newSize, 4))                               // ������ ��������� ������ ������, ������� ����� �������� ��� ����������
        {
            break;
        }

        if (newSize == message->Size())
        {
            result = true;
        }

        if (SPI4_::ReceiveAndCompare(message->Data(), message->Size()))
        {
            result = true;
        }
    }

    static uint all = 0;
    static uint failed = 0;
    all++;


    if (!result)
    {
        failed++;
        LOG_WRITE_FINALIZE("%d �� %d ������� �� ��������. %f ��������� ��������", failed, all, (float)failed / all * 100.0f);
    }

    return result;
}
