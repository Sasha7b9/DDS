#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Utils/Buffer.h"
#include "InterfacePanel.h"
#include "Command.h"
#include "structs.h"
#include "Display/Console.h"
#include "FDrive/FDrivePanel.h"
#include "FrequencyMeter/FrequencyMeter.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Utils/Debug.h"
#include "InterfacePanel.h"
#include <stdlib.h>
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::Send(const Buffer &buffer)
{
    Send(buffer.Data(), (uint16)buffer.Length());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::Update()
{
    static uint timePrev = 0;
    
    if (TIME_MS - timePrev > 100)
    {
        ProcessDataFPGA();
    
        timePrev = TIME_MS;
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::ProcessDataFPGA()
{
    /// \todo ������� ������ ����������� ������. ����� ��������� ���������� �� ������

    uint8 command = Command::RequestData;

    Send(&command, 1);

    uint16 numBytes = 0;

    CPU::SPI4_::Receive(&numBytes, 2);

    while (numBytes > 0)         // �������� �������� �������� ����� ����, ������� ��� �������� ��������������� �����������
    {
        ReceiveAndRun(numBytes);
        CPU::SPI4_::Receive(&numBytes, 2);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::Send(const uint8 *buffer, uint size)
{
    Command command(*buffer);
    if (Debug::ShowSends() && command.value != Command::RequestData)
    {
        //LOG_WRITE("������� %s", command.Trace(buffer));
    }

    CPU::SPI4_::Transmit(&size, 2);

    const uint8 *pointer = buffer;
    while (size > 0)
    {
        uint sizeChunk = (size > 1024u) ? 1024u : size; // ������ ����� ��� ��������

        size -= sizeChunk;

        CPU::SPI4_::Transmit(pointer, sizeChunk);

        pointer += sizeChunk;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::ReceiveAndRun(uint16 numBytes)
{
    uint8 *buffer = (uint8 *)malloc(numBytes);

    if (buffer)
    {
        CPU::SPI4_::Receive(buffer, numBytes);

        if (*buffer == Command::FreqMeasure)
        {
            BitSet32 bs;
            for (int i = 0; i < 4; i++)
            {
                bs.byte[i] = buffer[i + 1];
            }
            FrequencyMeter::SetMeasure(bs.word);
        }
        else if (*buffer == Command::Log)
        {
            char buf[LENGTH_SPI_BUFFER];
            for (int i = 0; i < LENGTH_SPI_BUFFER - 1; i++)
            {
                buf[i] = (char)buffer[i + 1];
            }
            buf[LENGTH_SPI_BUFFER - 1] = '\0';
            Console::AddString(buf);
        }
        else if(buffer[0] == Command::FDrive_Mount)
        {
            FDrive::HandlerInterface(buffer);
        }
        else if(*buffer == Command::FDrive_NumDirsAndFiles)
        {
            FDrive::HandlerInterface(buffer);
        }
        else if(*buffer == Command::FDrive_RequestDir)
        {
            FDrive::HandlerInterface(buffer);
        }
        else if(*buffer == Command::FDrive_RequestFile)
        {
            FDrive::HandlerInterface(buffer);
        }
    }

    free(buffer);
}
