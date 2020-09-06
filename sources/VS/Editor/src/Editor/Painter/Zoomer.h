#pragma once


/*
*   ���������� ��������� � ��������� ���� ������
*/


class Zoomer
{
public:

    // ��������� �������
    static void Increase(int mouseX = -1);

    // ��������� �������
    static void Decrease(int mouseX = -1);

    // ���������������� �� ������� ����������� �������
    static void SetOnRegion();

    static bool NoScaling();

    static int Scale();

    static void Draw();

    // ���������� x ��������� ������ ���������
    static int X();

    // ���������� y ��������� ������ ���������
    static int Y();

    // ������ ������ ���������
    static int Width();

    // ������ ������ ���������
    static int Height();

private:

    static int scale;
};
