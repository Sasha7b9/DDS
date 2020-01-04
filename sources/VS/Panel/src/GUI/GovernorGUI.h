#pragma once
#pragma warning(push, 0)
#include <wx/wx.h>
#pragma warning(pop)


class GovernorGUI : public wxPanel
{
public:
    GovernorGUI(wxWindow *parent, const wxPoint &position);
private:
    const int radius = 20;

    bool leftIsDown = false;

    POINT positionDown;

    void OnPaint(wxPaintEvent &);
    void OnMouseMove(wxMouseEvent &);
    void OnMouseLeftDown(wxMouseEvent &);
    void OnMouseLeftUp(wxMouseEvent &);
    void OnMouseLeave(wxMouseEvent &);
    /// ���������� ������ � ���� ����
    void SetMouseCursorHand();
    /// ���������� true, ���� ������ ���� ��������� ��� ������������ �����
    bool MouseOnGovernor(wxMouseEvent &);
};
