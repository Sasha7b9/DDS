#pragma once
#include "command.h"
#include "Message.h"


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
    static int NumberDirs()
    {
        return numDirs;
    }
    static int NumberFiles()
    {
        return numFiles;
    }

    static pString GetNameItem(int i);

    class Handler
    {
        friend class FDrive;
        static bool Processing(Message *msg);
    };

private:
    /// ���������� ��������� � ������� ��������
    static int numDirs;
    /// ���������� ������ � ������� ��������
    static int numFiles;
    /// ������ ������. ��������� �����
    static bool requestIsSend;

};
