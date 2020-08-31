#pragma once


class TextControlInt;


class ParametersDialog : public wxDialog
{
public:
    ParametersDialog(uint16 index, uint16 value);
private:
    
    TextControlInt *tcPosition;      // ����� ����� ������� ������ �����

    TextControlInt *tcValue;         // ����� ����� ������� �������� �������� �����

    void OnButtonApply(wxCommandEvent &);

    void OnButtonClose(wxCommandEvent &);
};
