#pragma once
#include "defines.h"
#include "Hardware/Controls.h"
#include "Settings/SettingsTypes.h"
#include "DisplayTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DISPLAY_SHOW_WARNING(warn)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Display
{
public:
    static void Init();

    static void Update();

    static uint8 *GetBuffer();

private:
    static void DrawFrequencyCounter();

    static void ShowStatistics();
    /// �������� ���������
    static void DrawHint();
    /// �����
    static uint8 *frontBuffer;
    /// ������ �����. � �� ���������� ���������, � ����� ����������� ���������� �� frontBuffer
    static uint8 *backBuffer;
    /// �����, ����������� �� ��������� ������ �����
    static int timeFrame;
    /// ����� ����� ����������� ����� ����� ���������
    static uint timeAccumFrames;
    /// ����� ��������� ���� ������ �� 1 �������
    static int timeAllFrames;
    /// ����� ������ ���������� 1-���������� �������, � ������� �������� ���������� ����� ����� ���������
    static uint timeStartFrames;
};
