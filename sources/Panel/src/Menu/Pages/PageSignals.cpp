#pragma once
#include "Display/InputWindow.h"
#include "Settings/Settings.h"
#include "Settings/SettingsSignals.h"
#include "Menu/MenuItems.h"
#include "AddPageInput.h"
#include "PageSignals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Page *PageSignals::pointer = &pSignals;

static void OnPress_Channel();
static void OnPress_SetParameter();

static uint8 waveForm = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� �������� - �������� ---------------------------------------------------------------------------------------------------------------------
ChoiceParameter PageSignals::cpParameters =
{
    Item_ChoiceParameter, {}, OnPress_SetParameter,
    {
        "��������", "PARAMETER"
    },
    {{true, true, true, true, false, false, false, false}},
    (uint8 *)&(set.sig_parameter[(WaveForm)waveForm])
};

void PageSignals::Init()
{
    waveForm = (uint8)WAVE_FORM;
    InputWindowStruct::FillAllowParameters(CHANNEL, WAVE_FORM, &cpParameters.allowParameters);
    cpParameters.numParameter = (uint8 *)&(set.sig_parameter[(WaveForm)waveForm]);
}


// ��������� �������� - ����� ------------------------------------------------------------------------------------------------------------------------
static const Choice cChannel =
{
    Item_Choice, {}, OnPress_Channel,
    {
        "�����", "CHANNEL",
    },
    {
        "1", "1",
        "2", "2"
    },
    (uint8 *)&CHANNEL
};

// ��������� �������� - ����� ------------------------------------------------------------------------------------------------------------------------
static const Choice cForm =
{
    Item_Choice, {}, OnPress_Form,
    {
        "�����", "FORM"
    },
    {
        "�����",    "SINE",
        "����",     "SAW",
        "�������",  "IMPULSE"
    },
    (uint8*)&waveForm
};

static void SetWaveForm(Channel ch, WaveForm form)
{
    set.sig_form[ch] = form;
    TuneGenerator(ch);
}

void PageSignals::OnPress_Form()
{
    WaveForm form = (WaveForm)waveForm;

    if (form == Form_Saw || form == Form_Impulse)
    {
        SetWaveForm(A, form);
        SetWaveForm(B, form);
    }

    WAVE_FORM = form;
    InputWindowStruct::FillAllowParameters(CHANNEL, WAVE_FORM, &cpParameters.allowParameters);
    cpParameters.numParameter = (uint8 *)&(set.sig_parameter[WAVE_FORM]);
    TuneGenerator(CHANNEL);
}

static void OnPress_Channel()
{
    waveForm = (uint8)WAVE_FORM;
    InputWindowStruct::FillAllowParameters(CHANNEL, WAVE_FORM, &cpParameters.allowParameters);
    cpParameters.numParameter = (uint8 *)&(set.sig_parameter[WAVE_FORM]);
}

// ��������� �������� - ������ �������� ��������� ----------------------------------------------------------------------------------------------------
static const Button bSetParameter =
{
    Item_Button, {}, OnPress_SetParameter,
    {
        "������ �������� ���������", "ENTER VALUE PARAMETER"
    }
};

static void OnPress_SetParameter(void)
{
    InputWindow::Init();

    ADDITION_PAGE = &pInput;
}

const Page pSignals =
{
    Item_Page, {}, 0,
    {
        "��������� ��������", "SIGNAL SETTINGS"
    },
    {
        (void*)&cChannel,       ///< ��������� �������� - �����
        (void*)&cForm,          ///< ��������� �������� - �����
        (void*)&cpParameters,   ///< ��������� �������� - ��������
        (void*)&bSetParameter   ///< ��������� �������� - ������ �������� ���������
    }
};
