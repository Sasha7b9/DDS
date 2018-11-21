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

    /*
    static uint time = 0;

    if (message->Size() > 100)
    {
        while (TIME_MS - time < 5000)
        {
        }

        time = TIME_MS;
    }
    */

    SPI4_::WaitFalling();                                               // ������� �������� ����� ���������� ������� � ��������� "��������"

    bool result = false;

    for (int i = 1; i < 3; i++)
    {
        uint size = message->Size();

        if (!SPI4_::Transmit(&size, 4))                                 // ������� ������ ������������ ������
        {
            LOG_WRITE_FINALIZE("�� ���� �������� ������");
        }

        if (!SPI4_::Transmit(message->Data(), message->Size()))         // ������� ��������������� ������
        {
            LOG_WRITE_FINALIZE("�� ���� �������� ������");
        }

        uint newSize = 0;
        if (!SPI4_::Receive(&newSize, 4))                               // ������ ��������� ������ ������, ������� ����� �������� ��� ����������
        {
            LOG_WRITE_FINALIZE("�� ���� ������� ������");
        }

        if (newSize == message->Size())
        {
            LOG_WRITE_FINALIZE("������� ���������");
            result = true;
        }
        else
        {
            result = false;
            LOG_WRITE_FINALIZE("������� �� ��������� %d %d", message->Size(), newSize);
            Timer::PauseOnTime(5000);
        }

        if (SPI4_::ReceiveAndCompare(message->Data(), message->Size()))
        {
            LOG_WRITE_FINALIZE("������ �������");
            result = true;
        }
        else
        {
            result = false;
            LOG_WRITE_FINALIZE("��������� ������ ������ ��������");
            Timer::PauseOnTime(5000);
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
