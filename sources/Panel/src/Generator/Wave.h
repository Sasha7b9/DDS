#pragma once
#include "Settings/SettingsTypes.h"
#include "Settings/Settings.h"


class Wave
{
public:

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
        static WaveForm Form(Chan ch = CURRENT_CHANNEL);
        /// ������������� ������ ������� �� ������ �����
        static void SetForm(Chan ch, WaveForm form);
    };
};
