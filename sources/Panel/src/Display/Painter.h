#pragma once
#include "defines.h"
#include "Colors.h"
#include "DisplayTypes.h"
#include "PainterText.h"


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
    /// ���������� ���� ���������
    static void SetColor(Color color);

    static void SetPoint(int x, int y);

    static void DrawHLine(int y, int x0, int x1);

    static void DrawVLine(int x, int y0, int y1);

    static void DrawLine(int x0, int y0, int x1, int y1);

    static void DrawRectangle(int x, int y, int width, int height);

    static void FillRegion(int x, int y, int width, int height);

    static void DrawBigText(int x, int y, int size, const char *text);

    static int DrawTextC(int x, int y, const char *text, Color color);

    static void FillRegionC(int x, int y, int width, int height, Color color);

    static void DrawRectangleC(int x, int y, int width, int height, Color color);
};

#define WRITE_BYTE(offset, value)   *(command + offset) = (uint8)value
#define WRITE_SHORT(offset, value)  *((uint16*)(command + offset)) = (uint16)value

/** @} @}
 */
