#pragma once
#include "Menu/MenuItems.h"
#include "Hardware/Controls.h"


class Hint
{
public:
    /// ���������� true, ���� ����� �������� ��������� �� �����
    static bool Show();
    /// ����������� ����� ��������� - ���� ���������� - �� ��������, � ��������
    static void Switch();
    /// ��������� ���������
    static void Draw();
    /// ���������� ��������, ��� �������� ����� �������� ���������
    static void SetItem(const Item * const item);
    /// ���������� ������� ����� (�������� �������). ���������� false, �c�� ������� ����� �� ����������
    static void ProcessGovernor(Control gov);

private:
    /// ���� true - ����� �������� ��������� �� �����
    static bool show;
    /// �������, ��� �������� ����� �������� ���������
    static const Item *item;

    static Control control;
};
