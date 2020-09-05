#pragma once


/*

    "����������" - ��, ��� ������� � ����������

*/


class Selector
{
public:
    
    static void BeginSelect(int mouseX);
    
    static void MoveSelect(int mouseX);
    
    static void EndSelect(int mouseX, int mouseY);
    
    static void Draw();

    // ���������� true, ���� ������ ��������� ��� �������� ����������� �������
    static bool CursorOverBorder(int mouseX);

private:

    // ���������� true, ���� ������ ��������� ������ ����� � ����������� x
    static bool CursorOverPointX(int mouseX, int x);
};
