#include "defines.h"
#include "Editor/Form.h"
#include "Editor/Selector.h"
#include "Editor/Painter/Canvas.h"


struct Cursor
{
    static int delta;                       // ������ ��� ������� ����������� � ��������
    static Cursor *grabbing;                // ��������� �� "������������" ������
    int x = -1;                             // ���������� x �������
    void Set(int mouseX);                   // ���������� ������ � ������� ���� mouseX
    void Disable()   { x = -1; }            // ��������� ������
    bool IsEnabled() { return x >= 0; }
    bool OverMouseX(int mouseX);            // ���������� true, ���� ������ ��������� ������ ����� � ����������� x
    void Draw();
    bool IsGrabbing()  { return grabbing == this; }
    static void EndGrabbing() { grabbing = nullptr; }
};

int Cursor::delta = 5;
Cursor *Cursor::grabbing = nullptr;


static Cursor cursors[2];

#define cursor1 cursors[0]
#define cursor2 cursors[1]


void Selector::BeginGrab(int mouseX)
{
    if (cursor2.OverMouseX(mouseX))
    {
        cursor2.Set(mouseX);
    }
    else if (cursor1.OverMouseX(mouseX))
    {
        cursor1.Set(mouseX);
    }
    else if(!cursor1.IsEnabled())
    {
        cursor1.Set(mouseX);
        cursor2.Set(mouseX);
    }
}


void Selector::MoveBorder(int mouseX)
{
    if (cursor1.IsGrabbing())
    {
        cursor1.Set(mouseX);
    }
    else if (cursor2.IsGrabbing())
    {
        cursor2.Set(mouseX);
    }
}


void Selector::EndGrab()
{ 
    Cursor::EndGrabbing();
}


void Selector::Draw()
{
    cursor1.Draw();
    cursor2.Draw();
}


bool Selector::CursorOverBorder(int mouseX)
{
    return cursor1.OverMouseX(mouseX) || cursor2.OverMouseX(mouseX);
}


void Cursor::Draw()
{
    if (IsEnabled())
    {
        int coord = Point::PointToMouseX(x);

        TheCanvas->DrawLine(coord, 0, coord, TheCanvas->GetSize().y, Color::GREEN);
    }
}


bool Cursor::OverMouseX(int mouseX)
{
    if (!IsEnabled())
    {
        return false;
    }

    int point = Point::PointToMouseX(x);

    return Math::InBoundaries(point, mouseX - delta, mouseX + delta);
}


void Cursor::Set(int mouseX)
{
    x = Point::MouseToPointX(mouseX);
    grabbing = this;
}
