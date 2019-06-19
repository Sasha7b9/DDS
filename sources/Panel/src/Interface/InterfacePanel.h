#pragma once
#include "Message.h"
#include "Utils/List.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ��������� �������� ������ ��� ������������� �������, ������������� � Interface
struct Task
{
    /// ���� ����������� ����� �������������� ������ � Interface ��� ���������
    Task(SimpleMessage *msg);

    Task(SimpleMessage *msg, bool (*process)(SimpleMessage *), bool (*equal)(Task *, Task *));
    /// ����������. � �� ����� ������� ���������
    ~Task();
    /// ������� ���������
    bool Equals(Task *, Task *);
    /// ���������� ��� ���������
    SimpleMessage *message;
    /// ���������� ��������� �� ������� � ������������� (�� ���������� ����������) ���������
    SimpleMessage *GetMessage();
    /// ������� ��������� �������
    void TransmitMessage();
    /// ���������� true, ���� ������ ������� ���� ������� ����� ���������� ������� ���������
    bool PassedLittleTimeAfterSend();
    /// ������� ��������� ������
    bool(*funcProcess)(SimpleMessage *);
private:
    /// ����� ��������� �������� ���������
    uint timeLast;
    /// ������� ���������
    bool (*funcEqual)(Task *, Task *);
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
    /// ���������� ����� �� �������
    static void RunAnswer(ListElement<Task> *element, SimpleMessage *answer);

};
