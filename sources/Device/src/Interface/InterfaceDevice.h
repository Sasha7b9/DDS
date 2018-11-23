#pragma once
#include "Command.h"
#include "Message.h"
#include "Utils/Queue.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Interface
{
    friend class Handlers;

public:

    static void Update();
    /// ��������� ��������� � ������� ��������. ���� ������� ���������, ��������� ��������� � ������� ���������� false
    static bool AddMessageInQueue(Message *message);

private:
    /// ������� ���������, ��������� ��������
    static Queue messages;
    /// ��������� �������� ��������, ��� ��� ������� �������� � ������ ��� ���������� ������������ ��������
    static uint freqForSend;
};
