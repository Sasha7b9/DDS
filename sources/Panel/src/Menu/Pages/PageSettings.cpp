#pragma once
#include "Display/InputWindow.h"
#include "Settings/Settings.h"
#include "Menu/MenuItems.h"
#include "AddPageInput.h"
#include "PageSettings.h"
#include "Generator/Wave.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pSignals;
Page *PageSignals::pointer = (Page *)&pSignals;
extern ChoiceParameterBase parameters;
ChoiceParameter *PageSignals::cpParameters = (ChoiceParameter *)&parameters;

static uint8 waveForm = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Channel(bool)
{
    waveForm = Wave::Signal::Form();
    InputWindowStruct::FillAllowParameters(CURRENT_CHANNEL, Wave::Signal::Form(), &parameters.allowParameters);
    parameters.numParameter = (uint8 *)&CURRENT_PARAMETER(Wave::Signal::Form());
}

DEF_CHOICE_2( cChannel,                                                                                           //--- ��������� �������� - ����� ---
    "�����", "CHANNEL",
    "����� ������ ��� ���������.",
    "Selecting a channel to set up.",
    "A", "A", "���������� ����������� ������� �� ������ A.",
              "Controlling the signal parameters at output A.",
    "B", "B", "���������� ����������� ������� �� ������ B.",
              "Controlling the signal parameters at output B.",
    FLAG_2, BIT_CHANNEL, pSignals, FuncActive, OnPress_Channel, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
static void SetWaveForm(Chan ch, WaveForm form)
{
    set.sig_form[ch] = form;
    TuneGenerator(ch);
}
*/

void PageSignals::OnPress_Form(bool)
{
    WaveForm form = WaveForm((WaveForm::E)waveForm);

    /*
    if (form.type == Form_Saw || form.type == Form_Impulse)
    {
        SetWaveForm(A, form);
        SetWaveForm(B, form);
    }
    */

    Wave::Signal::SetForm(CURRENT_CHANNEL, form);
    InputWindowStruct::FillAllowParameters(CURRENT_CHANNEL, Wave::Signal::Form(), &parameters.allowParameters);
    parameters.numParameter = (uint8 *)&CURRENT_PARAMETER(Wave::Signal::Form());
    TuneGenerator(CURRENT_CHANNEL);
}

DEF_CHOICE_12( cForm,                                                                                              //--- ��������� �������� - ����� ---
    "�����", "FORM",
    "����� ����� �������.",
    "Select waveform.",
    FORM_RU(WaveForm::Sine),        FORM_EN(WaveForm::Sine),        "�����.",                       "Sinus.",
    FORM_RU(WaveForm::Cosine),      FORM_EN(WaveForm::Cosine),      "�������.",                     "Cosine.",
    FORM_RU(WaveForm::Meander),     FORM_EN(WaveForm::Meander),     "������.",                      "Meander.",
    FORM_RU(WaveForm::RampPlus),    FORM_EN(WaveForm::RampPlus),    "����������� ����.",            "Growing saw.",
    FORM_RU(WaveForm::RampMinus),   FORM_EN(WaveForm::RampMinus),   "��������� ����.",              "Wrecking saw.",
    FORM_RU(WaveForm::Triangle),    FORM_EN(WaveForm::Triangle),    "�����������.",                 "Triangle.",
    FORM_RU(WaveForm::Trapeze),     FORM_EN(WaveForm::Trapeze),     "��������.",                    "Trapeze.",
    FORM_RU(WaveForm::Impulse),     FORM_EN(WaveForm::Impulse),     "�������.",                     "Impulse.",
    FORM_RU(WaveForm::ExpPlus),     FORM_EN(WaveForm::ExpPlus),     "������������ ����������.",     "Growing exponent.",
    FORM_RU(WaveForm::ExpMinus),    FORM_EN(WaveForm::ExpMinus),    "��������� ����������.",        "Decreasing exponent.",
    FORM_RU(WaveForm::Noise),       FORM_EN(WaveForm::Noise),       "���.",                         "Noise.",
    FORM_RU(WaveForm::Free),        FORM_EN(WaveForm::Free),        "������������ ����� �������.",  "Arbitrary waveform.",
    waveForm, pSignals, FuncActive, PageSignals::OnPress_Form, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_SetParameter()
{
    InputWindow::Init();

    ADDITION_PAGE = (Page *)&pInput;
}

DEF_BUTTON( bSetParameter,                                                                    //--- ��������� �������� - ������ �������� ��������� ---
    "������ �������� ���������", "ENTER VALUE PARAMETER",
    "��������� ���� ����� ���������.",
    "Opens the parameter input window.",
    pSignals, FuncActive, OnPress_SetParameter, FuncDraw
)

DEF_CHOICE_PARAMETER(parameters,                                                                               //--- ��������� �������� - �������� ---
    "��������", "PARAMETER",
    "����� ��������� ��� ���������.",
    "Choosing a setting for customization.",
    pSignals, FuncActive, OnPress_SetParameter, (CURRENT_PARAMETER(WaveForm((WaveForm::E)waveForm))),
    true, true, true, true, false, false, false, false
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageSignals::Init()
{
    waveForm = Wave::Signal::Form();
    InputWindowStruct::FillAllowParameters(CURRENT_CHANNEL, Wave::Signal::Form(), &parameters.allowParameters);
    parameters.numParameter = (uint8 *)&CURRENT_PARAMETER(WaveForm((WaveForm::E)waveForm));
}

DEF_PAGE_4
(
    pSignals,
    "��������� ��������", "SIGNAL SETTINGS",
    "", "",
    cChannel,       ///< ��������� �������� - �����
    cForm,          ///< ��������� �������� - �����
    parameters,     ///< ��������� �������� - ��������
    bSetParameter,  ///< ��������� �������� - ������ �������� ���������
    Page_Settings, 0, FuncActive, FuncPress, FuncOnKey
)
