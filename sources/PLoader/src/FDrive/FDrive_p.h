#pragma once
#include "common/Messages.h"



struct FDrive
{
    /// ��������� �������������
    static void Init();

    /// ��� ���������� - �������� ��� �����
    enum View
    {
        Dirs,
        Files
    };
    
    static View view;

    static char *CurrentDirectory();

    struct Handler
    {
        static bool Processing(SimpleMessage *msg);
    private:
        static SimpleMessage *msg;
        static bool E();
        static bool IsMount();
    };

private:
    enum Mount
    {
        Disconnect,
        Mounted,
        Failed
    };
    /// ������� ��������� ������
    static Mount mounted;
    /// ���� � �������� ��������
    static char directory[255];
    /// ���� true - ��� �������� ������� � ������ � ������
    static bool inStateWaitCompleteLoad;
};
