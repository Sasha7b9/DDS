#include "defines.h"
#include "log.h"
#include "Transceiver.h"
#include "Interface_p.h"
#include "Command.h"
#include "structs.h"
#include "Display/Console.h"
#include "Display/Painter.h"
#include "FDrive/FDrive_p.h"
#include "FreqMeter/FreqMeter_p.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"
#include "Utils/Debug.h"
#include "Utils/Queue.h"
#include "Handlers_p.h"
#include "Interface_p.h"
#include <cstdlib>


namespace Interface
{
    void AddMessageForTransmit(SimpleMessage *message);
    /// ������������ answer, ���� ������ �� ���� ���� � ������� �������. ���������� true, ���� ��� ���
    bool ProcessTask(SimpleMessage *answer);
    /// ������������ ������� �������, ������� ��������� ��� �� ���, ������� ���������� �������
    void SendTasks();
    /// ���������� ����� �� �������
    void RunAnswer(ListElement<Task> *element, SimpleMessage *answer);
}



static List<Task> tasks;



void Interface::AddMessageForTransmit(SimpleMessage *message)
{
    Transceiver::Transmit(message);
}


void Interface::Update()
{
    static uint time = 0;

    if (TIME_MS - time < 100)
    {
        return;
    }

    time = TIME_MS;

    Message::RequestData message;

    Transceiver::Transmit(&message);
    
    if (Transceiver::Receive(&message))
    {
        if (ProcessTask(&message) ||            // ������������ ���������, ���� ������ �� ���� ���� � ������� �������
            PHandlers::Processing(&message))    // ��� ������ ������������ � �������� ������
        {
            time = 0;
            Update();
        }
    }

    SendTasks();
}


void Interface::AddTask(Task *task)
{
    if(!tasks.IsMember(task))                   // ���� ������� ��� ��� � �������
    {
        task->TransmitMessage();                // �� �������� ��� ���������
        tasks.Append(task);                     // � ��������� � ������� ��������� ��� ��������� ��������
    }
}


void Task::TransmitMessage()
{
    message->Transmit();    // �������� ���������
    timeLast = TIME_MS;     // ���������� ����� �������
}


void Interface::SendTasks()
{
    ListElement<Task> *element = tasks.First();

    while (element)
    {
        Task *task = element->Get();

        if (!task->PassedLittleTimeAfterSend())
        {
            task->TransmitMessage();
        }

        element = element->Next();
    }
}


bool Task::PassedLittleTimeAfterSend()
{
    return (TIME_MS - timeLast) < 1000;
}


bool Interface::ProcessTask(SimpleMessage *answer)
{
    ListElement<Task> *element = tasks.First();

    Task taskAnswer(answer);

    while (element)
    {
        Task *task = element->Get();

        if (task->Equals(task, &taskAnswer))
        {
            RunAnswer(element, answer);
            return true;
        }

        element = element->Next();
    }


    return false;
}


void Interface::RunAnswer(ListElement<Task> *element, SimpleMessage *answer)
{
    element->Get()->funcProcess(answer);
    tasks.Remove(element->Get());
    delete element;
}


bool Task::Equals(Task *task1, Task *task2)
{
    return funcEqual(task1, task2);
}


Task::Task(SimpleMessage *msg) : funcProcess(nullptr), timeLast(0), funcEqual(nullptr)
{
    message = msg->Clone();
}


Task::Task(SimpleMessage *msg, bool(*process)(SimpleMessage *), bool(*equal)(Task *, Task *)) :funcProcess(process), timeLast(0), funcEqual(equal)
{
    message = msg->Clone();
}


Task::~Task()
{
    delete message;
}


SimpleMessage *Task::GetMessage()
{
    message->ResetPointer();
    return message;
}


void SimpleMessage::Transmit()
{
    Interface::AddMessageForTransmit(this);
}
