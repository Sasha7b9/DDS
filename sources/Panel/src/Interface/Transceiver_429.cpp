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
    static uint time = 0;

    while (TIME_MS - time < 5000)
    {
    }

    time = TIME_MS;

    SPI4_::WaitFalling();                                               // ������� �������� ����� ���������� ������� � ��������� "��������"

    Message recvMessage;                                                // ���� ����� ��������� �����

    for (int i = 1; i < 3; i++)
    {
        uint size = message->Size();

        LOG_WRITE_FINALIZE("������� ������ %d-� ���", i);

        if (!SPI4_::Transmit(&size, 4))                                 // ������� ������ ������������ ������
        {
            LOG_WRITE_FINALIZE("..... �������");
            break;
        }

        LOG_WRITE_FINALIZE("������� ������ %d", size);

        LOG_WRITE_FINALIZE("������� ������ %d-� ���", i);

        if (!SPI4_::Transmit(message->Data(), message->Size()))         // ������� ��������������� ������
        {
            LOG_WRITE_FINALIZE("..... �������");
            break;
        }

        LOG_WRITE_FINALIZE("�������� ������ %d-� ���", i);

        uint newSize = 0;
        if (!SPI4_::Receive(&newSize, 4))                               // ������ ��������� ������ ������, ������� ����� �������� ��� ����������
        {
            LOG_WRITE_FINALIZE("..... �������");
            break;
        }

        LOG_WRITE_FINALIZE("������ ������ %d", newSize);

        LOG_WRITE_FINALIZE("�������� ������ %d-� ���", i);

        recvMessage.AllocateMemory(newSize);                            // �������� ����������� ���������� ������ ��� ����������� ������
        if (!SPI4_::Receive(recvMessage.Data(), recvMessage.Size()))    // � ��������� ����� ���������� ����������
        {
            LOG_WRITE_FINALIZE("..... �������");
            break;
        }

        if (recvMessage.IsEquals(message))
        {
            LOG_WRITE_FINALIZE("�������� � %d ��� ������ ��������� � �����������", i);
        }
        else
        {
            LOG_WRITE_FINALIZE("�������� � %d ��� ������ �� ��������� � �����������", i);
        }
    }

    bool result = recvMessage.IsEquals(message);

    if (!result)
    {
        LOG_WRITE_FINALIZE("�������� ����� �� ��������� � ����������");
    }
    else
    {
        LOG_WRITE_FINALIZE("����� ������� �������");
    }

    return result;
}
