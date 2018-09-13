#pragma once
#include "Display/InputWindow.h"
#include "Settings/Settings.h"
#include "Menu/MenuItems.h"
#include "AddPageInput.h"
#include "PageSettings.h"
#include "Generator/Signals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pSignals;
Page *PageSignals::pointer = (Page *)&pSignals;
extern ChoiceParameterBase parameters;
ChoiceParameter *PageSignals::cpParameters = (ChoiceParameter *)&parameters;
/// ����� ������� ����� ������
static int numForm = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Channel(bool)
{
    parameters.form = FORM_CURRENT;
    numForm = FORM_CURRENT->value;
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
void OnPress_Form(bool)
{
    WAVE_CURRENT.SetNextForm();

    numForm = WAVE_CURRENT.GetCurrentForm()->value;

    parameters.form = FORM_CURRENT;

    Settings::TuneGenerator(CURRENT_CHANNEL);
}

DEF_CHOICE_5( cForm,                                                                                              //--- ��������� �������� - ����� ---
    "�����", "FORM",
    "����� ����� �������.",
    "Select waveform.",
    FORM_RU(Form::Sine),          FORM_EN(Form::Sine),          "�����.",               "Sinus.",
    FORM_RU(Form::RampPlus),      FORM_EN(Form::RampPlus),      "����������� ����.",    "Growing saw.",
    FORM_RU(Form::RampMinus),     FORM_EN(Form::RampMinus),     "��������� ����.",      "Wrecking saw.",
    FORM_RU(Form::Meander),       FORM_EN(Form::Meander),       "������.",              "Meander.",
    FORM_RU(Form::Impulse),       FORM_EN(Form::Impulse),       "�����������.",         "Triangle.",
    numForm, pSignals, FuncActive, OnPress_Form, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_SetParameter()
{
    if(PARAM_CURRENT->IsInputValue())
    {
        InputWindow::Init();

        ADDITION_PAGE = (Page *)&pInput;
    }
    else
    {
        FORM_CURRENT->OpenCurrentParameter();
    }
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
    pSignals, FuncActive, OnPress_SetParameter, WAVE(Chan::A).GetForm(0)
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageSignals::Init()
{
    OnPress_Channel(true);
}

