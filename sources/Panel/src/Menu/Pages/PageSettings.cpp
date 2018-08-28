#pragma once
#include "Display/InputWindow.h"
#include "Settings/Settings.h"
#include "Menu/MenuItems.h"
#include "AddPageInput.h"
#include "PageSettings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pSignals;
Page *PageSignals::pointer = (Page *)&pSignals;
extern ChoiceParameterBase parameters;
ChoiceParameter *PageSignals::cpParameters = (ChoiceParameter *)&parameters;

static Wave::Form waveForm = Wave::Form::Sine;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Channel(bool)
{
    waveForm = WAVE_FORM_CURRENT;
    InputWindow::FillAllowParameters(CURRENT_CHANNEL, WAVE_FORM_CURRENT, &parameters.allowParameters);
    parameters.numParameter = (uint8 *)&CURRENT_PARAMETER(WAVE_FORM_CURRENT);
}

DEF_CHOICE_2( cChannel,                                                                                           //--- ��������� �������� - ����� ---
    "�����", "CHANNEL",
    "����� ������ ��� ���������.",
    "Selecting a channel to set up.",
    "A", "A", "���������� ����������� ������� �� ������ A.",
              "Controlling the signal parameters at output A.",
    "B", "B", "���������� ����������� ������� �� ������ B.",
              "Controlling the signal parameters at output B.",
    FLAG_1, BIT_CHANNEL, pSignals, FuncActive, OnPress_Channel, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageSignals::OnPress_Form(bool)
{
    WAVE_FORM(CURRENT_CHANNEL) = waveForm;
    InputWindow::FillAllowParameters(CURRENT_CHANNEL, WAVE_FORM_CURRENT, &parameters.allowParameters);
    parameters.numParameter = (uint8 *)&CURRENT_PARAMETER(WAVE_FORM_CURRENT);
    Settings::TuneGenerator(CURRENT_CHANNEL);
}

DEF_CHOICE_3( cForm,                                                                                              //--- ��������� �������� - ����� ---
    "�����", "FORM",
    "����� ����� �������.",
    "Select waveform.",
    FORM_RU(Wave::Form::Sine),            FORM_EN(Wave::Form::Sine),        "�����.",                       "Sinus.",
    FORM_RU(Wave::Form::RampPlus),        FORM_EN(Wave::Form::RampPlus),    "����������� ����.",            "Growing saw.",
    FORM_RU(Wave::Form::RampMinus),       FORM_EN(Wave::Form::RampMinus),   "��������� ����.",              "Wrecking saw.",
//    FORM_RU(Wave::Form::Triangle),        FORM_EN(Wave::Form::Triangle),    "�����������.",                 "Triangle.",
//    FORM_RU(Wave::Form::Trapeze),         FORM_EN(Wave::Form::Trapeze),     "��������.",                    "Trapeze.",
//    FORM_RU(Wave::Form::Impulse),         FORM_EN(Wave::Form::Impulse),     "�������.",                     "Impulse.",
//    FORM_RU(Wave::Form::ExpPlus),         FORM_EN(Wave::Form::ExpPlus),     "������������ ����������.",     "Growing exponent.",
//    FORM_RU(Wave::Form::ExpMinus),        FORM_EN(Wave::Form::ExpMinus),    "��������� ����������.",        "Decreasing exponent.",
//    FORM_RU(Wave::Form::Noise),           FORM_EN(Wave::Form::Noise),       "���.",                         "Noise.",
//    FORM_RU(Wave::Form::Free),            FORM_EN(Wave::Form::Free),        "������������ ����� �������.",  "Arbitrary waveform.",
//    FORM_RU(Wave::Form::Cosine),          FORM_EN(Wave::Form::Cosine),      "�������.",                     "Cosine.",
//    FORM_RU(Wave::Form::Meander),         FORM_EN(Wave::Form::Meander),     "������.",                      "Meander.",
    waveForm, pSignals, FuncActive,     PageSignals::OnPress_Form, FuncDraw
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
    pSignals, FuncActive, OnPress_SetParameter, (CURRENT_PARAMETER(waveForm)),
    true, true, true, true, false, false, false, false
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageSignals::Init()
{
    waveForm = WAVE_FORM_CURRENT;
    InputWindow::FillAllowParameters(CURRENT_CHANNEL, WAVE_FORM_CURRENT, &parameters.allowParameters);
    parameters.numParameter = (uint8 *)&CURRENT_PARAMETER(Wave::Form(waveForm));
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
