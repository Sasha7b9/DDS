#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "Transceiver.h"
#include "InterfacePanel.h"
#include "Command.h"
#include "structs.h"
#include "Display/Console.h"
#include "Display/Painter.h"
#include "FDrive/FDrivePanel.h"
#include "FrequencyMeter/FrequencyMeter.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Hardware/Modules/SPI.h"
#include "Utils/Debug.h"
#include "Utils/Queue.h"
#include "HandlersPanel.h"
#include "InterfacePanel.h"
#include <cstdlib>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static List<Task> tasks;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::Send(Message *message)
{
    Transceiver::Transmit(message);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::Update()
{
    static uint time = 0;

    if (TIME_MS - time < 100)
    {
        return;
    }

    time = TIME_MS;

    Message message(1, Command::RequestData);

    Transceiver::Transmit(&message);

    if (Transceiver::Receive(&message))
    {
        if (ProcessTask(&message) ||            // ������������ ���������, ���� ������ �� ���� ���� � ������� �������
            Handlers::Processing(&message))     // ��� ������ ������������ � �������� ������
        {
            time = 0;
            Update();
        }
    }

    SendTasks();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::AddTask(Task *task)
{
    if (!tasks.Member(task))                    // ���� ������� ��� ��� � �������
    {
        Send(task->message);                    // �� �������� ���������
        task->timeLast = TIME_MS;               // ���������� ����� �������
        tasks.Append(task);                     // � ��������� � ������� ��������� ��� ��������� ��������
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::SendTasks()
{
    ListElement<Task> *element = tasks.First();

    while (element)
    {
        Task *task = element->Get();

        if (!PassedLittleTimeAfterSend(task))
        {
            Send(task->message);
        }

        element = element->Next();
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Interface::PassedLittleTimeAfterSend(Task *task)
{
    return (TIME_MS - task->timeLast) < 1000;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Interface::ProcessTask(Message * /*answer*/)
{
    return false;
}
