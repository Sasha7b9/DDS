#pragma once
#include "Display/Colors.h"
#include "Display/DisplayTypes.h"
#include "Display/Font/Font.h"


struct Painter
{
    // ���������� � ������ ��������� ������� �����. ��������� ����� ������ color
    static void BeginScene(Color color);
    
    // ���������� � ����� ��������� ������� �����. ��������� ���������� ������ �� �����
    static void EndScene();
    
    // ��������� � ������� ��� �����
    static void LoadPalette();
   
    // ���������� �������������� �����
    static void DrawHLine(int y, int x0, int x1, Color color = Color::NUMBER);
    
    // ���������� ������������ �����
    static void DrawVLine(int x, int y0, int y1, Color color = Color::NUMBER);
    
    // ���������� ������������ �����
    static void DrawLine(int x0, int y0, int x1, int y1, Color color = Color::NUMBER);
    
    // \brief ������ ����������� �������������� �����. dFill - ����� ������, dEmpty - �����. ����� ��������. ����� ������ ���������� �� ������. 
    // dStart ��������� �������� ������ �������� ����� ������������ ������ ������.
    static void DrawDashedHLine(int y, int x0, int x1, int dFill, int dEmpty, int dStart);
    
    // ������ ����������� ������������ �����.
    static void DrawDashedVLine(int x, int y0, int y1, int dFill, int dEmpty, int dStart);

    static void DrawVolumeButton(int x, int y, int width, int height, int thickness, Color normal, Color bright, Color dark, bool isPressed, bool isShade);
};


namespace Primitives
{
    class Point
    {
    public:
        void Draw(int x, int y);
    };

    class Rectangle
    {
    public:
        Rectangle(int w, int h) : width(w), height(h) { };
        void Draw(int x, int y, Color color = Color::NUMBER);
        void Fill(int x, int y, Color color = Color::NUMBER);
        void DrawFilled(int x, int y, Color colorFill, Color colorRect);

    private:
        int width;
        int height;
    };

}
