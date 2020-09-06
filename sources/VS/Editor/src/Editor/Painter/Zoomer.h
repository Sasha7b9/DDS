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

    // ������ ������ ��������� �����
    static int IndexFirsPoint();

    // ���������� ��������� �����
    static int NumberDrawingPoints();

private:

    static int scale;

    static int indexFirstPoint;

    static int indexMiddlePoint;

    static int numberDrawingPoints;

    // ���������� ���� �����������, ������������� �� ������
    static void DrawWindow();

    // ���������� �������� �������� �����
    static void CalculateIndexesPoints();
};
