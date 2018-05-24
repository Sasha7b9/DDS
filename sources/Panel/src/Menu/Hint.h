#pragma once
#include "Menu/MenuItems.h"


class Hint
{
public:
    /// ���������� true, ���� ����� �������� ��������� �� �����
    static bool Show();
    /// ����������� ����� ��������� - ���� ���������� - �� ��������, � ��������
    static void Switch();
    /// ��������� ���������
    static void Draw();

    static void ClearItem();

    static void SetItem(const Control * const item);

private:
    /// ���� true - ����� �������� ��������� �� �����
    static bool show;
    /// �������, ��� �������� ����� �������� ���������
    static const Control *item;
};
