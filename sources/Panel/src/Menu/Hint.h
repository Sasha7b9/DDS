#pragma once
#include "Menu/MenuItems.h"
#include "Hardware/Controls.h"


class Hint
{
public:
    /// ��������� ���������
    static void Draw();
    /// ����� ����������. ���������� false, ���� ��������� �� ���������
    static bool ProcessControl(StructControl strCtrl);

private:
    /// ���� true - ����� �������� ��������� �� �����
    static bool show;
    /// �������, ��� �������� ����� �������� ���������
    static const Item *item;

    static Control control;
    /// ���������� ������� � ���������
    static int numPages;
};
