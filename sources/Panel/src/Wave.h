#pragma once
#include "Settings/SettingsTypes.h"


class Wave
{
public:
    /// ���������� ���������� � ���������� ������� �� ������
    static void DrawSignal(Channel ch);
    /// ������� x ������� ��������� �������
    static int X();
    /// ������� y ������� ��������� �������
    static int Y(Channel ch);
    /// ������ ������� ��������� �������
    static int Width();
    /// ������ ������� ��������� �������
    static int Height();
private:

    static void DrawSignalUGO(Channel chan, int y0);

    static void DrawSignalParameters(Channel chan, int y0);

    static void DrawParameterValue(Channel chan, Type_WaveParameter parameter, int x, int y);
};
