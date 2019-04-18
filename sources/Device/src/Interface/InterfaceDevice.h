#pragma once
#include "Command.h"
#include "Message.h"
#include "Utils/Queue.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Interface
{
    friend class Message;
    friend class Handlers;

public:

    static void Update();
    
private:
    /// ��������� ��������� � ������� ��������. ���� ������� ���������, ��������� ��������� � ������� ���������� false
    static bool AddMessageForTransmit(Message *message);
    /// ������� ���������, ��������� ��������
    static Queue messages;
    /// ��������� �������� ��������, ��� ��� ������� �������� � ������ ��� ���������� ������������ ��������
    static uint freqForSend;
};
