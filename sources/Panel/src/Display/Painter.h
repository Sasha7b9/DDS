#pragma once
#include "defines.h"
#include "Display/Colors.h"
#include "Display/DisplayTypes.h"
#include "Display/Font/Font.h"




/** @addtogroup Display
 *  @{
 *  @defgroup Painter
 *  @brief ������� ���������
 *  @{
 */

namespace Painter
{
    /// ���������� � ������ ��������� ������� �����. ��������� ����� ������ color
    void BeginScene(Color color);
    /// ���������� � ����� ��������� ������� �����. ��������� ���������� ������ �� �����
    void EndScene();
    /// ���������� ���� ���������
    void SetColor(Color color);
    /// ���������� ������� ���� ���������
    Color GetColor();
    /// ������������� ����� �������� ��������. ����������� � ������� LoadPalette() ��� SetPalette()
    void SetColorValue(Color color, col_val value);
    /// ��������� � ������� ��� �����
    void LoadPalette();
    /// ���������� ����� ������� ������
    void SetPoint(int x, int y);
    /// ���������� �������������� ����� �� x0 �� x1 ������� ����� ������ delta ��������
    void DrawHPointLine(int y, int x0, int x1, float delta);
    /// ���������� ������������ ����� �� y0 �� y1 ������� ����� ������ delta ��������
    void DrawVPointLine(int x, int y0, int y1, float delta);
    /// ���������� �������������� �����
    void DrawHLine(int y, int x0, int x1, Color color = Color::NUMBER);
    /// ���������� ������������ �����
    void DrawVLine(int x, int y0, int y1, Color color = Color::NUMBER);
    /// ���������� ������������ �����
    void DrawLine(int x0, int y0, int x1, int y1, Color color = Color::NUMBER);
    /// \brief ������ ����������� �������������� �����. dFill - ����� ������, dEmpty - �����. ����� ��������. ����� ������ ���������� �� ������. 
    /// dStart ��������� �������� ������ �������� ����� ������������ ������ ������.
    void DrawDashedHLine(int y, int x0, int x1, int dFill, int dEmpty, int dStart);
    /// ������ ����������� ������������ �����.
    void DrawDashedVLine(int x, int y0, int y1, int dFill, int dEmpty, int dStart);

    void DrawRectangle(int x, int y, int width, int height, Color color = Color::NUMBER);

    void DrawFilledRectangle(int x, int y, int width, int height, Color colorFill, Color colorRect);

    void FillRegion(int x, int y, int width, int height, Color color = Color::NUMBER);

    void DrawVolumeButton(int x, int y, int width, int height, int thickness, Color normal, Color bright, Color dark, bool isPressed, bool isShade);

    col_val ReduceBrightness(col_val colorValue, float newBrightness);

    extern Color currentColor;

    extern Font::Type currentTypeFont;
};

/** @} @}
 */
