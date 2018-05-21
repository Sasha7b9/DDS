#pragma once
#include "defines.h"
#include "Display/Colors.h"
#include "Display/DisplayTypes.h"

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
    /// ����� ������� �������. ����� ��� ����, ����� �������� ������ ��� ����������� �� �������� � ������
    static void ResetFlash();
    /// ���������� ���� ���������
    static void SetColor(Color color);
    /// ���������� ������� ���� ���������
    static Color GetColor();
    /// ������������� ����� �������� ��������. ����������� � ������� LoadPalette() ��� SetPalette()
    static void SetColorValue(Color color, col_val value);
    /// ��������� � ������� ��� �����
    static void LoadPalette();
    /// ��������� � ������� ��� ������� �����
    static void SetPalette(Color color);
    /// ���������� ����� ������� ������
    static void SetPoint(int x, int y);
    /// ���������� �������������� ����� �� x0 �� x1 ������� ����� ������ delta ��������
    static void DrawHPointLine(int y, int x0, int x1, float delta);
    /// ���������� ������������ ����� �� y0 �� y1 ������� ����� ������ delta ��������
    static void DrawVPointLine(int x, int y0, int y1, float delta);
    /// ���������� �������������� �����
    static void DrawHLine(int y, int x0, int x1, Color color = Color::NUMBER);
    /// ���������� ������������ �����
    static void DrawVLine(int x, int y0, int y1, Color color = Color::NUMBER);
    /// ���������� ������������ �����
    static void DrawLine(int x0, int y0, int x1, int y1, Color color = Color::NUMBER);
    /// \brief ������ ����������� �������������� �����. dFill - ����� ������, dEmpty - �����. ����� ��������. ����� ������ ���������� �� ������. 
    /// dStart ��������� �������� ������ �������� ����� ������������ ������ ������.
    static void DrawDashedHLine(int y, int x0, int x1, int dFill, int dEmpty, int dStart);
    /// ������ ����������� ������������ �����.
    static void DrawDashedVLine(int x, int y0, int y1, int dFill, int dEmpty, int dStart);

    static void DrawRectangle(int x, int y, int width, int height, Color color = Color::NUMBER);

    static void DrawFilledRectangle(int x, int y, int width, int height, Color colorFill, Color colorRect);

    static void FillRegion(int x, int y, int width, int height, Color color = Color::NUMBER);

    static void DrawVolumeButton(int x, int y, int width, int height, int thickness, Color normal, Color bright, Color dark, bool isPressed, bool isShade);

    static col_val ReduceBrightness(col_val colorValue, float newBrightness);

    static bool SaveScreenToFlashDrive();

    /************** ������� ������ � ������� ************************/
    
    /// ����� ������ � ������� x, y
    static int DrawFormText(int x, int y, Color color, pString text, ...);

    static int DrawStringInCenterRect(int x, int y, int width, int height, const char *text, Color color = Color::NUMBER);
    /// ����� ������ ������ � ������ �������(x, y, width, height)������ ColorText �� �������������� � ������� ������� widthBorder ����� colorBackground
    static void DrawStringInCenterRectOnBackgroundC(int x, int y, int width, int height, const char *text, Color colorText, int widthBorder, 
                                             Color colorBackground);

    static int DrawStringInCenterRectAndBoundItC(int x, int y, int width, int height, const char *text, Color colorBackground, Color colorFill);

    static void DrawTextInRect(int x, int y, int width, const char *text);

    static void Draw2SymbolsC(int x, int y, char symbol1, char symbol2, Color color1, Color color2);

    static void Draw10SymbolsInRect(int x, int y, char eChar);
    
    
    

private:

    static void CalculateCurrentColor();

    static int GetLenghtSubString(const char *text);

    static int DrawSubString(int x, int y, const char *text);

    static int DrawSpaces(int x, int y, const char *text, int *numSymbols);

    static Color currentColor;

    static TypeFont currentTypeFont;
};


#define WRITE_BYTE(offset, value)   *(command + offset) = (uint8)value
#define WRITE_SHORT(offset, value)  *((uint16 *)(command + offset)) = (uint16)value

/** @} @}
 */
