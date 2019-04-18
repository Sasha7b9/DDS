#pragma once
#include "Message.h"
#include "Utils/List.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ��������� �������� ������ ��� ������������� �������, ������������� � Interface
struct Task
{
friend class Interface;

    Task(Message *msg, bool (*process)(Message *), bool (*equal)(Task *, Task *));
    /// ����������. � �� ����� ������� ���������
    ~Task();
    /// ������� ���������
    bool Equals(Task *, Task *);
    /// ���������� ��� ���������
    Message *message;
    /// ���������� ��������� �� ������� � ������������� (�� ���������� ����������) ���������
    Message *GetMessage();
private:
    /// ���� ����������� ����� �������������� ������ � Interface ��� ���������
    Task(Message *msg);
    /// ����� ��������� �������� ���������
    uint timeLast;
    /// ������� ���������
    bool (*funcEqual)(Task *, Task *);
    /// ������� ��������� ������
    bool (*funcProcess)(Message *);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Interface
{
    friend class Message;
public:

    /// ��� ����� ��������� �� ����������
    static void Update();
    /// ���������� �������. ���� �� ����������, ���������� false
    static void AddTask(Task *task);

private:
    static void AddMessageForTransmit(Message *message);
    /// ������������ answer, ���� ������ �� ���� ���� � ������� �������. ���������� true, ���� ��� ���
    static bool ProcessTask(Message *answer);
    /// ������������ ������� �������, ������� ��������� ��� �� ���, ������� ���������� �������
    static void SendTasks();
    /// ���������� true, ���� ������ ������� ���� ������� ����� ���������� ������� ���������
    static bool PassedLittleTimeAfterSend(Task *task);
    /// ���������� ����� �� �������
    static void RunAnswer(ListElement<Task> *element, Message *answer);

};
