#pragma once
#include "Settings/SettingsTypes.h"
#include "Settings/Settings.h"


class Signal
{
public:
    /// ���������� ���������� � ���������� ������� �� ������
    static void Draw(Chan ch);
    /// ������� x ������� ��������� �������
    static int X();
    /// ������� y ������� ��������� �������
    static int Y(Chan ch);
    /// ������ ������� ��������� �������
    static int Width();
    /// ������ ������� ��������� �������
    static int Height();
private:
    
    static void DrawSignalUGO(Chan chan, int y0);

    static void DrawSignalParameters(Chan chan, int y0);

    static void DrawParameterValue(Chan chan, Wave::Parameter parameter, int x, int y);
};
