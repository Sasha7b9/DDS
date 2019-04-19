#pragma once
#include "Command.h"
#include "Message.h"
#include "Utils/Queue.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Interface
{
    friend class SimpleMessage;
    friend class Handlers;

public:

    static void Update();
    
private:
    /// ��������� ��������� � ������� ��������. ���� ������� ���������, ��������� ��������� � ������� ���������� false
    static bool AddMessageForTransmit(SimpleMessage *message);
    /// ������� ���������, ��������� ��������
    static Queue messages;
    /// ��������� �������� ��������, ��� ��� ������� �������� � ������ ��� ���������� ������������ ��������
    static uint freqForSend;
};
