#pragma once
#include "defines.h"
#include "Display/Colors.h"
#include "Display/DisplayTypes.h"
#include "Display/Font/Font.h"


namespace Text
{
    /// ������������� ������� ������� ��������� ��������
    void SetUpperCase(bool upper);
    
    int DrawChar(int x, int y, char symbol, Color color = Color::NUMBER);

    void Draw4SymbolsInRect(int x, int y, char eChar, Color color = Color::NUMBER);

    int DrawBigChar(int eX, int eY, int size, char symbol);

    void DrawBigText(int x, int y, int size, pString text, Color color = Color::NUMBER);

    void DrawTextRelativelyRight(int xRight, int y, pString text, Color color = Color::NUMBER);
    
    void Draw2Symbols(int x, int y, char symbol1, char symbol2, Color color1, Color color2);

    void Draw10SymbolsInRect(int x, int y, char eChar);

    /***************** ����� ���������������� ������ ***********************/
    /// ����� ������ � ������� x, y
    int DrawFormatText(int x, int y, pString text, ...);

    /*************** ����� ������ � ������� ������ **************************/

    void DrawTextInColumn(int x, int y, int width, pString text);
    /// ���������� ������ ���������� ��������������
    int DrawTextInBoundedRectWithTransfers(int x, int y, int width, pString text, Color colorBack, Color colorRect, Color colorText);
    /// ����� ����� � ����������
    int DrawTextInColumnWithTransfers(const int left, const int top, const int width, pString text, const Color color = Color::NUMBER);

    int DrawTextInColumnWithTransfersDiffColors(const int left, const int top, const int width, pString text, const Color colorDif,
                                                       const Color = Color::NUMBER);

    int DrawFormatTextInColumnWithTransfers(int x, int y, int width, pString text, ...);
    /// ������� ��������������� ����� � ������� ������� width. ��� ���� ����, ����������� � ������� �������, ��������� ������ color
    int DrawFormatTextInColumnWithTransfersDiffColors(int x, int y, int width, Color color, pString text, ...);

    int DrawStringInCenterRect(int x, int y, int width, int height, pString text, Color color = Color::NUMBER);

    int DrawFormatStringInCenterRect(int x, int y, int width, int height, pString text, ...);
    /// ����� ������ ������ � ������ �������(x, y, width, height)������ ColorText �� �������������� � ������� ������� widthBorder ����� colorBackground
    void DrawStringInCenterRectOnBackground(int x, int y, int width, int height, pString text, Color colorText, int widthBorder,
                                                    Color colorBackground);
    int DrawStringInCenterRectAndBoundIt(int x, int y, int width, int height, pString text, Color colorBackground, Color colorFill);
    /// ���� true, �� ��� ����� ��������� � ������� ��������
    bool IsUpperCase();

    int DrawText(int x, int y, pString text, Color color = Color::NUMBER);
};
