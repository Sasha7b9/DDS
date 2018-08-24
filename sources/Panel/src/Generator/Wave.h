#pragma once
#include "Settings/SettingsTypes.h"
#include "Settings/Settings.h"


class Signal
{
public:

    static pString Name(uint num, Language lang);
    /// ���������� ������� ����� ������� �� ������ ������
    static WaveForm GetForm(Chan ch = (Chan::E)CURRENT_CHANNEL);
    /// ������������� ������ ������� �� ������ �����
    static void SetForm(Chan ch, WaveForm form);

    /// �������� �� ����������� �������� �� ������
    class Graphic
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
    
        static void DrawParameterValue(Chan chan, WaveParameter parameter, int x, int y);
    };
};
