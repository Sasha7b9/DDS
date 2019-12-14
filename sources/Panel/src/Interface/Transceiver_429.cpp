#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "Transceiver.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Hardware/Modules/SPI.h"
#endif



void Transceiver::Transmit(SimpleMessage *message)
{
    uint timeout = (message->Size() > 1000U) ? 100U : 10U;

    bool result = false;
    
    uint failed = 0;

    while (!result)
    {
        SPI4_::WaitFalling();                                                   // ������� �������� ����� ���������� ������� � ��������� "��������"

        for (int i = 0; i < 2; i++)
        {
            SPI4_::Transmit(message->Size(), 10);                               // ������� ������ ������������ ������

            SPI4_::Transmit(message->Data(), message->Size(), timeout);         // ������� ��������������� ������

            uint newSize = 0;
            SPI4_::Receive(&newSize, 4, 10);                                    // ������ ��������� ������ ������, ������� ����� �������� ��� ����������

            uint trashedBytes = SPI4_::ReceiveAndCompare(message->Data(), message->Size());

            result = (trashedBytes == 0);
        }

        if (!result)
        {
            /// \todo ������� �� ��, ��� ��� ������� ������� ������ ����� ���������� ���������. �� �������� ���� �� ����������� � ��� ����.
            failed++;
            if(failed > 5)
            {
                break;
            }
        }
    };
}


bool Transceiver::Receive(SimpleMessage *message)
{
    SPI4_::WaitFalling();

    uint size = 0;
    SPI4_::Receive(&size, 4, 10);

    if (message->AllocateMemory(size))
    {
        SPI4_::Receive(message->Data(), message->Size(), 50);
        return true;
    }

    return message->Size() != 0;
}
