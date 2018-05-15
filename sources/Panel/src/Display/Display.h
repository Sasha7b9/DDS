#pragma once
#include "defines.h"
#include "Hardware/Controls.h"
#include "Settings/SettingsTypes.h"
#include "DisplayTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DISPLAY_ADD_STRING(x)       Display::AddStringToIndicating(x)
#define DISPLAY_SHOW_WARNING(warn)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Display
{
public:
    static void Init();

    static void Update();

    static uint8 *GetBuffer();

    static void SetButton(PanelControl control);

    static void AddStringToConsole(char *string);

    static void AddStringToIndicating(pString string);

private:
    static void DrawSignal(Channel chan);

    static void DrawSignalUGO(Channel chan, int y0);

    static void DrawSignalParameters(Channel chan, int y0);

    static void DrawParameterValue(Channel chan, WaveParameter parameter, int x, int y);

    static void DrawConsole();

    static void DrawFrequencyCounter();

    static void ShowStatistics();

    static const char *text;

    static const int STRING_IN_CONSOLE = 29;

    static const int SYMBOLS_IN_STRING = 64;

    static char bufferConsole[STRING_IN_CONSOLE][SYMBOLS_IN_STRING];
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
