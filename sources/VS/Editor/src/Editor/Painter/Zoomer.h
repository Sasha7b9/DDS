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

private:

    static int scale;
};
