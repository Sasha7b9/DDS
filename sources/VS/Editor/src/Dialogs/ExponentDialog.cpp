#include "defines.h"
#include "Form.h"
#include "Utils.h"
#include "Dialogs/ExponentDialog.h"
#include "Dialogs/SpinControl.h"
#pragma warning(push, 0)
#include <wx/spinctrl.h>
#include <wx/statline.h>
#pragma warning(pop)
#include <vector>


enum
{
    ID_SPINCTRL_DONW,
    ID_SPINCTRL_UP,
    ID_SPINCTRL_FRONT_DELAY,
    ID_SPINCTRL_FRONT_TIME,
    ID_TEXTCTRL_FRONT_K,
    ID_TEXTCTRL_BACK_K,
    ID_RADIOBUTTON_DIRECT,
    ID_RADIOBUTTON_BACK
};


static double oldFrontK = 1.0;
static double oldBackK = 1.0;


static wxRadioButton *rbDirect = nullptr;
static wxRadioButton *rbBack = nullptr;
static SpinControl *scUp = nullptr;
static SpinControl *scDown = nullptr;

static SpinControl *scDelay = nullptr;          // �������� ����� ������� ����������������� ��������
static SpinControl *scFrontTime = nullptr;      // ����� �� ������ ����������������� �������� �� ������ �����
static wxTextCtrl *tcFrontK = nullptr;          // ����������� ����������
static wxTextCtrl *tcBackK = nullptr;


static wxPanel *CreatePanelPolarity(wxDialog *dlg)
{
    wxPanel *panel = new wxPanel(dlg);
    new wxStaticBox(panel, wxID_ANY, wxT("����������"), wxDefaultPosition, wxSize(90, 75));

    int y = 25, x = 5;

    rbDirect = new wxRadioButton(panel, ID_RADIOBUTTON_DIRECT, wxT("������"), wxPoint(x, y));
    dlg->Connect(ID_RADIOBUTTON_DIRECT, wxEVT_RADIOBUTTON, wxCommandEventHandler(Dialog::OnControlEvent));
    rbDirect->SetValue(true);

    rbBack = new wxRadioButton(panel, ID_RADIOBUTTON_BACK, wxT("��������"), wxPoint(x, y + 25));
    dlg->Connect(ID_RADIOBUTTON_BACK, wxEVT_RADIOBUTTON, wxCommandEventHandler(Dialog::OnControlEvent));

    return panel;
}


static wxPanel *CreatePanelLevels(wxDialog *dlg)
{
    wxPanel *panel = new wxPanel(dlg);

    new wxStaticBox(panel, wxID_ANY, wxT("������"), wxDefaultPosition, wxSize(130, 75));

    int y = 20, x = 10;

    scUp = new SpinControl(panel, ID_SPINCTRL_UP, wxT("100"), wxPoint(x, y), wxSize(50, 20), -100, 100, 100, dlg, wxCommandEventHandler(ExponentDialog::OnControlEvent), wxT("�������, %"));
    scDown = new SpinControl(panel, ID_SPINCTRL_DONW, wxT("-100"), wxPoint(x, y + 26), wxSize(50, 20), -100, 100, -100, dlg, wxCommandEventHandler(ExponentDialog::OnControlEvent), wxT("������, %"));

    return panel;
}


static wxPanel *CreatePanelParameters(wxDialog *dlg)
{
    wxPanel *panel = new wxPanel(dlg);

    new wxStaticBox(panel, wxID_ANY, wxT("���������"), wxDefaultPosition, wxSize(220, 75 + 26 * 2));

    int y = 20, x = 10, dY = 26;

    scDelay = new SpinControl(panel, ID_SPINCTRL_FRONT_DELAY, wxT("0"), wxPoint(x, y), wxSize(50, 20), 0, Point::NUM_POINTS, 0, dlg, wxCommandEventHandler(ExponentDialog::OnControlEvent), wxT("��������, �����"));
    scFrontTime = new SpinControl(panel, ID_SPINCTRL_FRONT_TIME, wxT("4095"), wxPoint(x, y + dY), wxSize(50, 20), 0, Point::NUM_POINTS, Point::NUM_POINTS / 2, dlg, wxCommandEventHandler(ExponentDialog::OnControlEvent), wxT("����� ����������, �����"));

    tcFrontK = new wxTextCtrl(panel, ID_TEXTCTRL_FRONT_K, Utils::DoubleToString(oldFrontK), wxPoint(x, y + 2 * dY), wxSize(75, 20));
    dlg->Connect(ID_TEXTCTRL_FRONT_K, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(ExponentDialog::OnControlEvent));

    tcBackK = new wxTextCtrl(panel, ID_TEXTCTRL_BACK_K, Utils::DoubleToString(oldBackK), wxPoint(x, y + 3 * dY), wxSize(75, 20));
    dlg->Connect(ID_TEXTCTRL_BACK_K, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(ExponentDialog::OnControlEvent));

    return panel;
}


ExponentDialog::ExponentDialog() : Dialog(wxT("��������� ����������������� �������"), wxSize(225, 252))
{
    wxBoxSizer *vBox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hBoxPanels = new wxBoxSizer(wxHORIZONTAL);

    hBoxPanels->Add(CreatePanelPolarity(this));
    hBoxPanels->AddStretchSpacer();
    hBoxPanels->Add(CreatePanelLevels(this));
    vBox->Add(hBoxPanels);
    vBox->Add(CreatePanelParameters(this));

    SetBoxSizer(vBox, { 221, 203 });
}


void ExponentDialog::DrawLine(int x1, int y1, int x2, int y2)
{
    float dX = static_cast<float>(x2 - x1);

    float dY = std::fabsf(static_cast<float>(y2 - y1));

    float k = dY / dX;

    if(y2 > y1)
    {
        for(int x = x1; x <= x2; x++)
        {
            data[x] = static_cast<uint16>(y1 + (x - x1) * k + 0.5F);
        }
    }
    else
    {
        for(int x = x1; x <= x2; x++)
        {
            data[x] = static_cast<uint16>(y1 - (x - x1) * k + 0.5F);
        }
    }
}


void ExponentDialog::SendAdditionForm()
{
    double frontK = Utils::StringToDouble(tcFrontK->GetValue());

    if(frontK == 0.0) //-V2550 //-V550
    {
        frontK = oldFrontK;
    }

    double backK = Utils::StringToDouble(tcBackK->GetValue());
    
    if(backK == 0.0) //-V2550 //-V550
    {
        backK = oldBackK;
    }

    int levelHI = static_cast<int>(Point::AVE_VALUE + (Point::MAX_VALUE + Point::MIN_VALUE) / 2.0F * scUp->GetValue() / 100.0F); //-V2007
    int levelLOW = static_cast<int>(Point::AVE_VALUE + (Point::MAX_VALUE + Point::MIN_VALUE) / 2.0F * scDown->GetValue() / 100.0F); //-V2007

    int min = levelLOW;
    int max = levelHI;

    if(rbBack->GetValue())
    {
        min = levelHI;
        max = levelLOW;
    }

    DrawLine(0, min, scDelay->GetValue(), min);

    int start = scDelay->GetValue();

    int topX = static_cast<int>(start + scFrontTime->GetValue());

    for(int i = start + 1; i < topX; i++)
    {
        double param = (i - start) * frontK;

        double d = min + std::log(param) * 500 * frontK;

        if(d < min)
        {
            d = static_cast<double>(min);
        }

        if(d > max)
        {
            d = static_cast<double>(max);
        }

        uint16 value = static_cast<uint16>(d);

        data[i] = value;
    }

    TheForm->SetAdditionForm(data);
}
