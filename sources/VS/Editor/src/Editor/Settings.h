#pragma once


struct ModeButtonLeft
{
    enum E
    {
        EditPoints,     // ����� �������������� ��������� �����
        EditLines       // ����� �������������� ���������������� �������
    };

    static E Get();

    static void Set(E v);
};
