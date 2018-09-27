#pragma once
#include "Display/InputWindow.h"
#include "Settings/Settings.h"
#include "Menu/MenuItems.h"
#include "AddPageInput.h"
#include "PageSignals.h"
#include "Generator/Signals.h"
#include "Generator/Generator.h"
#include "Menu/Menu.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pSignals;
Page *PageSignals::pointer = (Page *)&pSignals;
extern ChoiceParameterBase cParameters;
/// ����� ������� ����� ������
static int numForm = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Channel(bool)
{
    cParameters.form = FORM_CURRENT;
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

    cParameters.form = FORM_CURRENT;

    Generator::TuneChannel(CURRENT_CHANNEL);
}

DEF_CHOICE_6( cForm,                                                                                              //--- ��������� �������� - ����� ---
    "�����", "FORM",
    "����� ����� �������.",
    "Select waveform.",
    FORM_RU(Form::Sine),            FORM_EN(Form::Sine),          "�����",               "Sinus",
    FORM_RU(Form::RampPlus),        FORM_EN(Form::RampPlus),      "����������� ����",    "Growing saw",
    FORM_RU(Form::RampMinus),       FORM_EN(Form::RampMinus),     "��������� ����",      "Wrecking saw",
    FORM_RU(Form::Meander),         FORM_EN(Form::Meander),       "������",              "Meander",
    FORM_RU(Form::Impulse),         FORM_EN(Form::Impulse),       "�����������",         "Triangle",
    FORM_RU(Form::PacketImpuls),    FORM_EN(Form::PacketImpuls),  "������",              "Packets",
    numForm, pSignals, FuncActive, OnPress_Form, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_ChnageParameter()
{
    if(PARAM_CURRENT->IsInputValue())
    {
        InputWindow::Init();

        Menu::SetAdditionPage((Page *)AddPageInput::pointer);
    }
    else if(PARAM_CURRENT->IsExitParameter())
    {
        FORM_CURRENT->CloseOpenedParameter();
    }
    else
    {
        FORM_CURRENT->OpenCurrentParameter();
    }
}

DEF_BUTTON( bChangeParameter,                                                                 //--- ��������� �������� - ������ �������� ��������� ---
    "��������", "Change",
    "��������� ���� ����� ���������.",
    "Opens the parameter input window.",
    pSignals, FuncActive, OnPress_ChnageParameter, FuncDraw
)

DEF_CHOICE_PARAMETER(cParameters,                                                                              //--- ��������� �������� - �������� ---
    "��������", "PARAMETER",
    "����� ��������� ��� ���������.",
    "Choosing a setting for customization.",
    pSignals, FuncActive, OnPress_ChnageParameter, WAVE(Chan::A).GetForm(0)
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cTypeTune,                                                                                         //--- ��������� �������� - ������� ---
    "�������", "SENDING",
    "���������� ������������� ������� �������� �������� � ���������� ����������.",
    "Specifies the frequency of sending signal settings to the control device.",
    "����������", "SINGLE",         "������� �������� ������� ���������� ����������, ����� ������� ������ �������������.",
                                    "The signal settings are sent once, after you press the confirm button.",
    "����������", "CONTINUOUSLY",   "������� �������� ������� ���������� ��������� � ���������� ���������� �� ������.",
                                    "Sending of signal settings occurs synchronously with changing information on the screen.",
    FLAG_1, BIT_TUNE_FULL, pSignals, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_ModeStartA(bool)
{
    Generator::LoadStartMode(Chan::A);
}


DEF_CHOICE_4(   cModeStartA,                                                                            //--- ��������� �������� A - ����� ������� ---
    "����� �������", "Launch mode",
    "����������� ����� �������",
    "Defines the launch mode",
    "����", "Auto",                 "",
                                    "",
    "���������� �", "Comparator A", "",
                                    "",
    "������������� B", "Shaper B",  "",
                                    "",
    "�����������", "Single",        "",
                                    "",
    START_MODE_A, pSignals, FuncActive, OnPress_ModeStartA, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_ModeStartB(bool)
{
    Generator::LoadStartMode(Chan::B);
}

DEF_CHOICE_4(   cModeStartB,                                                                            //--- ��������� �������� B - ����� ������� ---
    "����� �������", "Launch mode",
    "����������� ����� �������",
    "Defines the launch mode",
    "����", "Auto",                 "",
                                    "",
    "���������� �", "Comparator A", "",
                                    "",
    "������������� B", "Shaper B",  "",
                                    "",
    "�����������", "Single",        "",
                                    "",
    START_MODE_B, pSignals, FuncActive, OnPress_ModeStartB, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool OnKey(Control key)
{
    if(key.Is(Control::Esc) && key.action.IsRelease())
    {
        return FORM_CURRENT->CloseOpenedParameter();
    }

    return false;
}

DEF_PAGE_7( pSignals,
    "��������� ��������", "SIGNAL SETTINGS",
    "", "",
    cChannel,           ///< ��������� �������� - �����
    cForm,              ///< ��������� �������� - �����
    cParameters,        ///< ��������� �������� - ��������
    bChangeParameter,   ///< ��������� �������� - ������ �������� ���������
    cModeStartA,        ///< ��������� �������� - ����� ������� A
    cModeStartB,        ///< ��������� �������� - ����� ������� B
    cTypeTune,          ///< ��������� �������� - �������
    Page::Settings, Menu::mainPage, FuncActive, FuncPress, OnKey
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageSignals::Init()
{
    OnPress_Channel(true);
}
