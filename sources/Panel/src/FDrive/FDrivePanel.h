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

    namespace Handler
    {
        bool Processing(SimpleMessage *msg);
    };

    /// ���� � �������� ��������
    extern char directory[255];
};
