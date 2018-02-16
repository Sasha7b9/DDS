#pragma once
#include "defines.h"
#include "Colors.h"
#include "DisplayTypes.h"
#include "PainterText.h"
#include "PainterC.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void CalculateCurrentColor();


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** @addtogroup Display
 *  @{
 *  @defgroup Painter
 *  @brief ������� ���������
 *  @{
 */

class Painter
{
public:
    /// ���������� � ������ ��������� ������� �����. ��������� ����� ������ color
    static void BeginScene(Color color);
    /// \brief ���������� ������� ���������� ����� ��������� � ���� �������, �� ��������� ����������� ��������� ������� EndScene(). 
    /// ����� ��������, ���� ������� ��������� ����� ��������� ������ ������ ������ �������. ��������, ����� �������������� ����� �������� �� ������ � 
    /// ������ ����������.
    static void RunDisplay();
    /// ���������� � ����� ��������� ������� �����. ��������� ���������� ������ �� �����
    static void EndScene();
    /// ������� ����������� �� ������� ���������� ����� USB ��� LAN. ���� first == true, �� ���������� �����
    static void SendFrame(bool first);
    /// ����� ������� �������. ����� ��� ����, ����� �������� ������ ��� ����������� �� �������� � ������
    static void ResetFlash();
    /// ���������� ���� ���������
    static void SetColor(Color color);

    static void LoadPalette();

    static void SetPoint(int x, int y);

    static void DrawHLine(int y, int x0, int x1);

    static void DrawVLine(int x, int y0, int y1);

    static void DrawHPointLine(int y, int x0, int x1, float delta);

    static void DrawVPointLine(int x, int y0, int y1, float delta);

    static void DrawMultiVPointLine(int numLines, int y, uint16 x[], int delta, int count, Color color);

    static void DrawMultiHPointLine(int numLines, int x, uint8 y[], int delta, int count, Color color);

    static void DrawLine(int x0, int y0, int x1, int y1);
    /// \brief ������ ����������� �������������� �����. dFill - ����� ������, dEmpty - �����. ����� ��������. ����� ������ ���������� �� ������. 
    /// dStart ��������� �������� ������ �������� ����� ������������ ������ ������.
    static void DrawDashedHLine(int y, int x0, int x1, int dFill, int dEmpty, int dStart);
    /// ������ ����������� ������������ �����.
    static void DrawDashedVLine(int x, int y0, int y1, int dFill, int dEmpty, int dStart);

    static void DrawRectangle(int x, int y, int width, int height);

    static void FillRegion(int x, int y, int width, int height);

    static void DrawVolumeButton(int x, int y, int width, int height, int thickness, Color normal, Color bright, Color dark, bool isPressed, bool isShade);
    /// ���������� ������� �������.
    static void SetBrightnessDisplay(int16 brightness);

    static uint16 ReduceBrightness(uint16 colorValue, float newBrightness);
    /// ���������� ������ ������������ �����. ����� �������� ���� �� ������. y0y1 - ������ ������������ ���������.
    static void DrawVLineArray(int x, int numLines, uint8 *y0y1, Color color);
    /// modeLines - true - �������, false - �������.
    static void DrawSignal(int x, uint8 data[281], bool modeLines);

    static void DrawPicture(int x, int y, int width, int height, uint8 *address);

    static void DrawBigText(int x, int y, int size, const char *text);

    static int DrawTextC(int x, int y, const char *text, Color color);
};

#define WRITE_BYTE(offset, value)   *(command + offset) = (uint8)value
#define WRITE_SHORT(offset, value)  *((uint16*)(command + offset)) = (uint16)value

/** @} @}
 */
