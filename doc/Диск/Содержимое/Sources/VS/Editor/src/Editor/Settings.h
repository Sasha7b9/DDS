#pragma once


struct ModeButtonLeft
{
    enum E
    {
        EditPoints,     // ����� �������������� ��������� �����
        EditLines,      // ����� �������������� ���������������� �������
        SelectZone      // ����� ��������� ����
    };

    static E Get();

    static void Set(E v);
};
