#pragma once
#include "Display/InputWindow.h"
#include "Settings/Settings.h"
#include "Settings/SettingsSignals.h"
#include "Menu/MenuItems.h"
#include "AddPageInput.h"
#include "PageSettings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pSignals;
Page *PageSignals::pointer = (Page *)&pSignals;
extern ChoiceParameterBase parameters;
ChoiceParameter *PageSignals::cpParameters = (ChoiceParameter *)&parameters;

static uint8 waveForm = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Channel(bool)
{
    waveForm = WAVE_FORM.ToValue();
    InputWindowStruct::FillAllowParameters(CURRENT_CHANNEL, WAVE_FORM, &parameters.allowParameters);
    parameters.numParameter = (uint8 *)&CURRENT_PARAMETER(WAVE_FORM);
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
static void SetWaveForm(Channel ch, WaveForm form)
{
    set.sig_form[ch] = form;
    TuneGenerator(ch);
}
*/

void PageSignals::OnPress_Form(bool)
{
    WaveForm form = WaveForm(waveForm);

    /*
    if (form.type == Form_Saw || form.type == Form_Impulse)
    {
        SetWaveForm(A, form);
        SetWaveForm(B, form);
    }
    */

    WAVE_FORM = form;
    InputWindowStruct::FillAllowParameters(CURRENT_CHANNEL, WAVE_FORM, &parameters.allowParameters);
    parameters.numParameter = (uint8 *)&CURRENT_PARAMETER(WAVE_FORM);
    TuneGenerator(CURRENT_CHANNEL);
}

DEF_CHOICE_12( cForm,                                                                                              //--- ��������� �������� - ����� ---
    "�����", "FORM",
    "����� ����� �������.",
    "Select waveform.",
    FORM_RU(Sine),      FORM_EN(Sine),      "�����.",
                                            "Sinus.",
    FORM_RU(Cosine),    FORM_EN(Cosine),    "�������.",
                                            "Cosine.",
    FORM_RU(Meander),   FORM_EN(Meander),   "������.",
                                            "Meander.",
    FORM_RU(RampPlus),  FORM_EN(RampPlus),  "����������� ����.",
                                            "Growing saw.",
    FORM_RU(RampMinus), FORM_EN(RampMinus), "��������� ����.",
                                            "Wrecking saw.",
    FORM_RU(Triangle),  FORM_EN(Triangle),  "�����������.",
                                            "Triangle.",
    FORM_RU(Trapeze),   FORM_EN(Trapeze),   "��������.",
                                            "Trapeze.",
    FORM_RU(Impulse),   FORM_EN(Impulse),   "�������.",
                                            "Impulse.",
    FORM_RU(ExpPlus),   FORM_EN(ExpPlus),   "������������ ����������.",
                                            "Growing exponent.",
    FORM_RU(ExpMinus),  FORM_EN(ExpMinus),  "��������� ����������.",
                                            "Decreasing exponent.",
    FORM_RU(Noise),     FORM_EN(Noise),     "���.",
                                            "Noise.",
    FORM_RU(Free),      FORM_EN(Free),      "������������ ����� �������.",
                                            "Arbitrary waveform.",
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
    pSignals, FuncActive, OnPress_SetParameter, (CURRENT_PARAMETER(WaveForm(waveForm))),
    true, true, true, true, false, false, false, false
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageSignals::Init()
{
    waveForm = WAVE_FORM.ToValue();
    InputWindowStruct::FillAllowParameters(CURRENT_CHANNEL, WAVE_FORM, &parameters.allowParameters);
    parameters.numParameter = (uint8 *)&CURRENT_PARAMETER(WaveForm(waveForm));
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
