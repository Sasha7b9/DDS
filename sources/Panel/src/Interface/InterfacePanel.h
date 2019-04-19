#pragma once
#include "Message.h"
#include "Utils/List.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ��������� �������� ������ ��� ������������� �������, ������������� � Interface
struct Task
{
friend class Interface;

    Task(SimpleMessage *msg, bool (*process)(SimpleMessage *), bool (*equal)(Task *, Task *));
    /// ����������. � �� ����� ������� ���������
    ~Task();
    /// ������� ���������
    bool Equals(Task *, Task *);
    /// ���������� ��� ���������
    SimpleMessage *message;
    /// ���������� ��������� �� ������� � ������������� (�� ���������� ����������) ���������
    SimpleMessage *GetMessage();
private:
    /// ���� ����������� ����� �������������� ������ � Interface ��� ���������
    Task(SimpleMessage *msg);
    /// ����� ��������� �������� ���������
    uint timeLast;
    /// ������� ���������
    bool (*funcEqual)(Task *, Task *);
    /// ������� ��������� ������
    bool (*funcProcess)(SimpleMessage *);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Interface
{
    friend class SimpleMessage;
public:

    /// ��� ����� ��������� �� ����������
    static void Update();
    /// ���������� �������. ���� �� ����������, ���������� false
    static void AddTask(Task *task);

private:
    static void AddMessageForTransmit(SimpleMessage *message);
    /// ������������ answer, ���� ������ �� ���� ���� � ������� �������. ���������� true, ���� ��� ���
    static bool ProcessTask(SimpleMessage *answer);
    /// ������������ ������� �������, ������� ��������� ��� �� ���, ������� ���������� �������
    static void SendTasks();
    /// ���������� true, ���� ������ ������� ���� ������� ����� ���������� ������� ���������
    static bool PassedLittleTimeAfterSend(Task *task);
    /// ���������� ����� �� �������
    static void RunAnswer(ListElement<Task> *element, SimpleMessage *answer);

};
