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

    static void DrawSine(int x, int y, int width, int height);

    static void DrawRampPlus(int x, int y, int width, int height);

    static void DrawRampMinus(int x, int y, int width, int height);

    static void DrawMeander(int x, int y, int width, int height);

    static void DrawImpulse(int x, int y, int width, int height);

    static void DrawSignalParameters(Chan chan, int y0);

    static void DrawParameterValue(Chan chan, Wave::Form::Parameter parameter, int x, int y);
};
