#pragma once
#pragma once
#include "Settings/SettingsTypes.h"


class Parameter;


class WaveGraphics
{
public:
    // ���������� ���������� � ���������� ������� �� ������
    static void Draw(Chan::E ch);
    // ������� x ������� ��������� �������
    static int X();
    // ������� y ������� ��������� �������
    static int Y(Chan::E ch);
    // ������ ������� ��������� �������
    static int Width();
    // ������ ������� ��������� �������
    static int Height();
private:

    static void DrawParameters(Chan::E chan, int y0);

    static void DrawParameterValue(Parameter *parameter, int x, int y);
};
