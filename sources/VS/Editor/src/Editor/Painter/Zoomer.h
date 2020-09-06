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

    static int Right();

    // ���������� y ��������� ������ ���������
    static int Y();

    // ������ ������ ���������
    static int Width();

    // ������ ������ ���������
    static int Height();

    static int Bottom();

    // ������ ������ ��������� �����
    static int IndexFirsPoint();

    // ���������� ��������� �����
    static int NumberDrawingPoints();

    // ���������� true, ���� ��������� ��� �����
    static bool UnderMouse(int mouseX, int mouseY);

    static void MoveMouse(int mouseX);

    // ��������� �����
    static bool Grab(int mouseX, int mouseY);

    // �������� �� ����
    static bool UnGrab();

private:

    static int scale;
    static int indexFirstPoint;         // ������ ������ ��������� �����
    static int indexMiddlePoint;        // ������ ������� ��������� �����
    static int numberDrawingPoints;     // ���������� ��������� �����

    // ���������� �������� �������� �����
    static void CalculateIndexesPoints();
};
