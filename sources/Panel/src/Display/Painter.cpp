#include "Display.h"
#include "Painter.h"
#include "globals.h"
#include "Font/Font.h"
#include "Utils/Math.h"
#include <stdio.h>
#include <string.h>
#include <math.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint8 color;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Painter::BeginScene(Color col)
{
    color = col;

    for (int x = 0; x < 320; ++x)
    {
        for (int y = 0; y < 240; ++y)
        {
            SetPoint(x, y);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawHLine(int y, int x0, int x1)
{
    for(int x = x0; x <= x1; ++x)
    {
        SetPoint(x, y);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawLine(int x1, int y1, int x2, int y2)
{
    if ((x2 - x1) == 0 && (y2 - y1) == 0)
    {
        ++x1;
    }
    int x = x1;
    int y = y1;
    int dx = (int)fabsf((float)(x2 - x1));
    int dy = (int)fabsf((float)(y2 - y1));
    int s1 = Math_Sign(x2 - x1);
    int s2 = Math_Sign(y2 - y1);
    int temp;
    int exchange = 0;
    if (dy > dx)
    {
        temp = dx;
        dx = dy;
        dy = temp;
        exchange = 1;
    }
    int e = 2 * dy - dx;
    int i = 0;
    for (; i <= dx; i++)
    {
        Painter::SetPoint(x, y);
        while (e >= 0)
        {
            if (exchange)
            {
                x += s1;
            }
            else
            {
                y += s2;
            }
            e = e - 2 * dx;
        }
        if (exchange)
        {
            y += s2;
        }
        else
        {
            x += s1;
        }
        e = e + 2 * dy;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawRectangle(int x, int y, int width, int height)
{
    DrawHLine(y, x, x + width);
    DrawHLine(y + height, x, x + width);
    DrawVLine(x, y, y + height);
    DrawVLine(x + width, y, y + height);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawVLine(int x, int y0, int y1)
{
    for(int y = y0; y <= y1; ++y)
    {
        SetPoint(x, y);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::EndScene(void)
{
    Display::ToggleBuffers();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::FillRegion(int x, int y, int width, int height)
{
    for (int i = y; i <= y + height; ++i)
    {
        DrawHLine(i, x, x + width);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::RunDisplay(void)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetColor(Color col)
{
    color = col;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void CalculateCurrentColor(void)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetPoint(int x, int y)
{
    if(x >= 0 && x < 320 && y >= 0 && y < 240)
    {
        *(Display::GetBuffer() + y * 320 + x) = color;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::FillRegionC(int x, int y, int width, int height, Color col)
{
    Painter::SetColor(col);
    Painter::FillRegion(x, y, width, height);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawRectangleC(int x, int y, int width, int height, Color col)
{
    Painter::SetColor(col);
    Painter::DrawRectangle(x, y, width, height);
}
