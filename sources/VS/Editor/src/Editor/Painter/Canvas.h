#pragma once
#include "Colors.h"

#pragma warning(push, 0)
#include <wx/wx.h>
#pragma warning(pop)


struct Grid
{
    static int X();
    static int Y();
    static int Width();
    static int Height();
    static int Bottom();
    static int Right();
    static void Draw();
    static void ChangeTypeGrid() { typeIsPercents = !typeIsPercents; }
    
    // ���������� true, ���� ����� ����� ��������� � ���������
    static bool TypeIsPercents() { return typeIsPercents; }
    
    // ���������� ���������� ����� ������������� ������� � ������ ��� ���������
    static wxString GetScale();

private:
    static bool typeIsPercents;
    static wxString sScale;
    static void DrawTypePercents();
    static void DrawTypePoints();
    static void DrawHorizontalLines();

    // ���������� ����� ����� � ������
    static int GetDeltaPoints();

    // ���������� ������ ����� � ���������. ������ ������� - ���� �������� ��������. 1% == 1000
    static int GetDeltaPercents();
};


class Canvas : public wxPanel
{
public:

    Canvas(wxWindow *parent);

    ~Canvas();

    void Draw();

    void Redraw();

private:
    
    bool mouseIsDown = false;       // true, ���� ��� ��������� � ������� ���������
    int mouseX = 0;
    int mouseY = 0;
    wxWindow *parent;

    void BeginScene();

    void EndScene();

    void OnPaint(wxPaintEvent &);

    void OnResize(wxSizeEvent &);

    void OnMouseMove(wxMouseEvent &);

    void OnMouseLeftDown(wxMouseEvent &);

    void OnMouseRightDown(wxMouseEvent &);

    void OnMouseLeftUp(wxMouseEvent &);

    void OnMouseRightUp(wxMouseEvent &);

    // ���������� ����������� ����� ������� ����
    void SetMouseCursor();
};


extern Canvas *TheCanvas;
