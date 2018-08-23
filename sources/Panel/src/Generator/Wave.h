#pragma once
#include "Settings/SettingsTypes.h"
#include "Settings/Settings.h"


class Wave
{
public:

    static pString Name(uint num, Language lang);

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

    /// �������� �� ��������� �������
    class Signal
    {
    public:
        /// ���������� ������� ����� ������� �� ������ ������
        static WaveForm Form(Chan ch = (Chan::E)CURRENT_CHANNEL);
        /// ������������� ������ ������� �� ������ �����
        static void SetForm(Chan ch, WaveForm form);
    };
};
