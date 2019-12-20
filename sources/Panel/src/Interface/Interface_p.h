#pragma once
#include "Message.h"
#include "Utils/List.h"




/// ��������� �������� ������ ��� ������������� �������, ������������� � Interface
struct Task
{
    /// ���� ����������� ����� �������������� ������ � Interface ��� ���������
    Task(SimpleMessage *msg);

    Task(SimpleMessage *msg, bool (*process)(SimpleMessage *), bool (*equal)(Task *, Task *));
    /// ����������. � ��� ����� ������� ���������
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



namespace PInterface
{
    /// ��� ����� ��������� �� ����������
    void Update();
    /// ���������� �������. ���� �� ����������, ���������� false
    void AddTask(Task *task);
};