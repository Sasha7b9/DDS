#pragma once
#pragma warning(push, 0)
#include <wx/wx.h>
#pragma warning(pop)


class ParametersDialog : public wxDialog
{
public:
    ParametersDialog();
private:
    
    wxTextCtrl *tcPosition;      // ����� ����� ������� ������ �����

    wxTextCtrl *tcValue;         // ����� ����� ������� �������� �������� �����

    void OnButtonApply(wxCommandEvent &);

    void OnButtonCancel(wxCommandEvent &);
};
