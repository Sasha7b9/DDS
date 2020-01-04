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
    /// ���� �������� �����
    float angle = 0.0F;

    wxTimer timer;

    struct StructCursor
    {
        /// true, ���� ����� ������ ������
        bool leftIsDown;
        /// ������� �������
        POINT position;
        /// ��������� VK_LBUTTON
        int state;
        /// ������������ dX � dY ����� position � newPosition
        int CalculateDelta(POINT *newPosition);
        /// ���������� true, ���� ������ ������ ����� ������ ����
        bool LeftIsDown();
    } cursor;

    void OnPaint(wxPaintEvent &);
    void OnMouseLeftDown(wxMouseEvent &);
    void OnMouseMove(wxMouseEvent &);
    void OnTimer(wxTimerEvent &);

    /// ���������� true, ���� ������ ���� ��������� ��� ������������ �����
    bool MouseOnGovernor(wxMouseEvent &);

    float Sin(float grad);
    float Cos(float grad);
};
