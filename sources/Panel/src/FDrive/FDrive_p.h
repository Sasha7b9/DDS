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

    /// ��������� �����-���������
    static void Draw();
    /// ��������� ������� ������ "�����"
    static void PressUp();
    /// ��������� ������� ������ "����"
    static void PressDown();
    /// ��������� ������� ������ "�������"
    static void PressChoose();

    static char *CurrentDirectory();

    struct Handler
    {
        static bool Processing(SimpleMessage *msg);
    private:
        static SimpleMessage *msg;
        static bool IsMount();
        static bool GetNumDirsAndFiles();
        static bool RequestFile();
        static bool RequestFileSize();
        static bool LoadFromExtStorage();
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
