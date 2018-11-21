#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "Transceiver.h"
#include "Hardware/CPU.h"
#include "Hardware/Modules/SPI.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Transceiver::Send(Message *message)
{
    uint timeout = (message->Size() > 1000U) ? 200U : 10U;

    SPI4_::WaitFalling();                                                   // ������� �������� ����� ���������� ������� � ��������� "��������"

    bool result = false;

    for (int i = 1; i < 3; i++)
    {
        uint size = message->Size();

        if (!SPI4_::Transmit(&size, 4, 10))                                 // ������� ������ ������������ ������
        {
//            LOG_WRITE_FINALIZE("�� ���� �������� ������");
        }

        if (!SPI4_::Transmit(message->Data(), message->Size(), timeout))    // ������� ��������������� ������
        {
//            LOG_WRITE_FINALIZE("�� ���� �������� ������");
        }

        uint newSize = 0;
        if (!SPI4_::Receive(&newSize, 4, 10))                               // ������ ��������� ������ ������, ������� ����� �������� ��� ����������
        {
//            LOG_WRITE_FINALIZE("�� ���� ������� ������");
        }

        if (newSize == message->Size())
        {
            result = true;
        }
        else
        {
            result = false;
//            LOG_WRITE_FINALIZE("������� �� ��������� %d %d", message->Size(), newSize);
        }

        if (SPI4_::ReceiveAndCompare(message->Data(), message->Size()))
        {
            result = true;
        }
        else
        {
            result = false;
//            LOG_WRITE_FINALIZE("��������� ������ ������ ��������");
        }
    }

    static uint all = 0;
    static uint failed = 0;
    all++;


    if (!result)
    {
        failed++;
//        LOG_WRITE_FINALIZE("%d �� %d ������� �� ��������. %f ��������� ��������", failed, all, (float)failed / all * 100.0f);
    }

    return result;
}
