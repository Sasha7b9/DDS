#pragma once
#include "Message.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace FDrive
{
    /// ��������� �������������
    void Init();

    /// ��� ���������� - �������� ��� �����
    enum View
    {
        Dirs,
        Files
    };
    
    extern View view;

    /// ��������� �����-���������
    void Draw();
    /// ��������� ������� ������ "�����"
    void PressUp();
    /// ��������� ������� ������ "����"
    void PressDown();
    /// ��������� ������� ������ "�������"
    void PressChoose();

    char *CurrentDirectory();

    namespace Handler
    {
        bool Processing(SimpleMessage *msg);
    };
};
