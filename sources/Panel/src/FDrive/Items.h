#pragma once
#include "common/command.h"
#include "common/Message.h"
#include "Utils/String.h"



class File;

class Items
{
public:

    static void Init();
    /// true ��������, ��� ��� �������� ������ �� ����������
    static bool WaitAnswer()
    {
        return requestIsSend;
    }
    /// ������� ������ �� ���������� ������
    static void SendRequest();
    /// ���������� ���������� ������. -1 - ������ �� ���������
    static int NumberDirs();
    /// ��������� ������� ������ "�����"
    static void PressUp();
    /// ��������� ������� ������ "����"
    static void PressDown();
    /// ���������� ������������
    static void Draw(int x, int y);
    /// ���������� ����� �������� �����
    static int NumberCurrentFile();

    class Handler
    {
    public:
        static bool Processing(SimpleMessage *msg);
    };

private:
    /// ������ ������. ��������� �����
    static bool requestIsSend;
};
