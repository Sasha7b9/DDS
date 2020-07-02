#pragma once
#include "Display/DisplayTypes.h"
#include "Display/Text.h"
#include "Keyboard/Controls.h"


#define BUFFER_WIDTH    Display::WIDTH    // ������ ������ ��� ���������
#define BUFFER_HEIGHT   Display::HEIGHT   // ������ ������ ��� ���������


struct Display
{
    static const int WIDTH = 320;
    static const int HEIGHT = 240;

    static void Init();

    static void Update();

    static void DrawScreenSplash();

    static uint8 *GetBuffer();

    static uint8 *GetRow(int row);
    
    static void ShowWarning(String warning);
    static void ShowWarning(const char *warning);

    static void ClearWarnings();

    // �����
    static uint8 frontBuffer[BUFFER_WIDTH * BUFFER_HEIGHT];

    // ������ �����. � �� ���������� ���������, � ����� ����������� ���������� �� frontBuffer
    static uint8 backBuffer[BUFFER_WIDTH * BUFFER_HEIGHT];
};
