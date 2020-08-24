#pragma once


class TextControl;


class ParametersDialog : public wxDialog
{
public:
    ParametersDialog(uint16 index, uint16 value);
private:
    
    TextControl *tcPosition;      // ����� ����� ������� ������ �����

    TextControl *tcValue;         // ����� ����� ������� �������� �������� �����

    void OnButtonApply(wxCommandEvent &);

    void OnButtonCancel(wxCommandEvent &);
};
