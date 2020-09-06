#pragma once


/*

    "����������" - ��, ��� ������� � ����������

*/


class Selector
{
public:
    
    static void BeginGrab(int mouseX);
    
    static void MoveBorder(int mouseX);
    
    static void EndGrab();
    
    static void DrawRegion();

    static void DrawCursors();

    // ���������� true, ���� ������ ��������� ��� �������� ����������� �������
    static bool CursorOverBorder(int mouseX);
};
