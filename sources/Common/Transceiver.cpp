#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "Message.h"
#include "Transceiver.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Transceiver::Send(uint8 *buffer, uint size)
{
    Message message;

    if (message.CreateFromRawData(buffer, size))
    {
        /// ��������� ��������, ���� �� ���������
        while (!Send(&message))
        {
        }
    }
    else
    {
        LOG_WRITE_FINALIZE("��� %d ���� ��� ���������", size);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Transceiver::Test()
{
    Message message;

    for (uint size = 12000; size < 20000; size += 1000)
    {
        message.AllocateMemory(size);

        while (!Send(&message))
        {
            LOG_WRITE_FINALIZE("�� ���� �������� ��������� ������ %d", message.Size());
        }

        LOG_WRITE_FINALIZE("������� �������� ��������� ������ %d ����", message.Size());

        Timer::PauseOnTime(5000);
    }
}
