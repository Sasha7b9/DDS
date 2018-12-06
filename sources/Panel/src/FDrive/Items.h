#pragma once
#include "command.h"
#include "Message.h"
#include "Utils/String.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

    static int NumberFiles()
    {
        return numFiles;
    }
    /// ��������� ������� ������ "�����"
    static void PressUp();
    /// ��������� ������� ������ "����"
    static void PressDown();
    /// ���������� ������������
    static void DrawItems(int x, int y);

    class Handler
    {
        friend class FDrive;
        static bool Processing(Message *msg);
    };

private:
    /// ���������� ������ � ������� ��������
    static int numFiles;
    /// ������ ������. ��������� �����
    static bool requestIsSend;
    /// ���������� ��� i-�� �����
    static String GetNameItem(int i);
};
