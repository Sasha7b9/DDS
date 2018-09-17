#include "PageFrequencyCounter2.h"
#include "Settings/Settings.h"
#include "Generator/Generator.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pFrequencyCounter2;
Page *PageFrequencyCounter2::pointer = (Page *)&pFrequencyCounter2;

static void OnPress_Resist(bool);
static void OnPress_Couple(bool);
static void OnPress_Filtr(bool);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2(cResist,
    "������������� �����", "INPUT RESISTANCE",
    "���������� �������������� ����� �����������",
    "Control of the resistance of the frequency meter input",
    "1 ���", "1 MOhm",  "������������� ����� 1 ���",
                        "Input Impedance 1 MOhm",
    "50 ��", "50 Ohm",  "������������� ����� 50 ��",
                        "Input Impedance 50 Ohm",
    FLAG_1, BIT_FREQ_RESIST, pFrequencyCounter2, FuncActive, OnPress_Resist, FuncDraw
)

static void OnPress_Resist(bool)
{
    Generator::LoadRegister(Register::FreqMeter_Resist, (uint)FREQ_RESIST);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cCouple,
    "����", "COUPLE",
    "����������/��������� ���������� ������������",
    "Skips / prohibits the DC component",
    "�����", "AC",  "���������� ������������ ��������� �� ���� �����������",
                    "The DC component is fed to the frequency meter input",
    "����", "DC",   "���������� ������������ �� ��������� �� ���� �����������",
                    "The DC component is not input to the frequency meter input",
    FLAG_1, BIT_FREQ_COUPLE, pFrequencyCounter2, FuncActive, OnPress_Couple, FuncDraw
)

static void OnPress_Couple(bool)
{
    Generator::LoadRegister(Register::FreqMeter_Couple, (uint)FREQ_COUPLE);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cFiltr,
    "���", "LPF",
    "��������/��������� ������ ������ ������ �� ����� �����������",
    "Enables / disables the low-pass filter at the input of the frequency meter",
    DISABLED_RU, DISABLED_EN,   "��� �� ����� ����������� ��������",
                                "LPF at the frequency meter input is disabled",
    ENABLED_RU, ENABLED_EN,     "��� �� ����� ����������� ���������",
                                "LPF at the input of the frequency meter is turned on",
    FLAG_1, BIT_FREQ_FILTR, pFrequencyCounter2, FuncActive, OnPress_Filtr, FuncDraw
)

static void OnPress_Filtr(bool)
{
    Generator::LoadRegister(Register::FreqMeter_Filtr, (uint)FREQ_FILTR);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_3(pFrequencyCounter2,
    "���������� 2", "FREQUENCY METER",
    "���������� ��������� �����������",
    "Control of frequency meter functions",
    cResist,
    cCouple,
    cFiltr,
    Page::Name::FrequencyCounter2, 0, FuncActive, FuncPress, FuncOnKey
)
