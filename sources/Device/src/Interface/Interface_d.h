#pragma once
#include "Command.h"
#include "Message.h"
#include "Utils/Queue.h"



namespace Interface
{
    void Update();
    /// ���������� ������ �� ������� ���������, ��������� ��������
    Queue &GetOutbox();

    void ResetFreqForSend();
};
