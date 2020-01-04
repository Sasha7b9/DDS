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

        int dX;
        int dY;
        /// ���������� true, ���� position ��������� � �������� ������������ �������
        bool PositionEqualsCurrent(POINT *newPosition);
        /// ������������ dX � dY ����� position � newPosition
        void CalculateDeltas(POINT *newPosition);
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
