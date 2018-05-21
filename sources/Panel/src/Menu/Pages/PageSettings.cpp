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
    "����� ������ ��� ���������",
    "Selecting a channel to set up",
    "A", "A", "���������� ����������� ������� �� ������ A",
              "Controlling the signal parameters at output A",
    "B", "B", "���������� ����������� ������� �� ������ B",
              "Controlling the signal parameters at output B",
    CURRENT_CHANNEL, pSignals, FuncActive, OnPress_Channel, FuncDraw
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

DEF_CHOICE_7( cForm,                                                                                              //--- ��������� �������� - ����� ---
    "�����", "FORM",
    "����� ����� �������",
    "Select waveform",
    "�����",        "SINE",    "�����",
                               "Sinus",
    "�������",      "COSINE",  "�������",
                               "Cosine",
    "������",       "MEANDER", "������",
                               "Meander",
    "����+",        "SAW+",    "����������� ����",
                               "Growing saw",
    "����-",        "SAW-",    "��������� ����",
                               "Wrecking saw",
    "�������",      "IMPULSE", "��������",
                               "Impulses",
    "������������", "FREE",    "������������ ����� �������",
                               "Arbitrary waveform",
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
    "��������� ���� ����� ���������",
    "Opens the parameter input window",
    pSignals, FuncActive, OnPress_SetParameter, FuncDraw
)

DEF_CHOICE_PARAMETER(parameters,                                                                               //--- ��������� �������� - �������� ---
    "��������", "PARAMETER",
    "����� ��������� ��� ���������",
    "Choosing a setting for customization",
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
    Page_Settings, 0, FuncActive, FuncPress
)
