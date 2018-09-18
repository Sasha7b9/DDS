#include "PageFrequencyCounter.h"
#include "Settings/Settings.h"
#include "Generator/Generator.h"
#include "FrequencyMeter/FrequencyMeter.h"
#include "Menu/Menu.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pFrequencyCounter;
Page *PageFrequencyCounter::pointer = (Page *)&pFrequencyCounter;

static void OnPress_Measure(bool);
static void OnPress_Interval(bool);
static void OnPress_BillingTime(bool);
static void OnPress_Resist(bool);
static void OnPress_Couple(bool);
static void OnPress_Filtr(bool);
static void OnPress_Test(bool);
static void OnPress_TimeStamps(bool);
static void OnPress_AvePeriod(bool);



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2(cEnableFrequencyCounter,                                                                               //--- ���������� - ����������� ---
    "�����������", "DISPLAY",
    "�������� � ��������� ����� �����������.",
    "Turns the frequency meter output on and off.",
    DISABLED_RU, DISABLED_EN, "����������� ��������� ����������� ���������.",
                              "Display of frequency meter readings is disabled.",
    ENABLED_RU,  ENABLED_EN,  "� ������ ����� ������ ��������� ��������� �����������.",
                              "The bottom of the screen displays the frequency meter.",
    FLAG_1, BIT_FREQ_ENABLED, pFrequencyCounter, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cMeasure,                                                                                                //--- ���������� - ��������� ---
    "���������", "MEASURE",
    "��������� ������ ������",
    "Setting the operating mode",
    "�������", "Frequency", "��������� �������",
                            "Frequency measurement",
    "������", "Period",     "��������� �������",
                            "Period measurement",
    FLAG_1, BIT_FREQ_MEASURE, pFrequencyCounter, FuncActive, OnPress_Measure, FuncDraw
)

static void OnPress_Measure(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cInterval,                                                                                        //--- ���������� - �������� ������� ---
    "�������� �������", "START INTERVAL",
    "����� ��������� ������� ��������� �������.",
    "Selecting the frequency measurement start interval.",
    "1 c", "1 s",   "������ �������� ��������� ��������� ������������ � ���������� 1 �������.",
                    "The measurement of the frequency meter is started at intervals of 1 second.",
    "10 �", "10 s", "������ �������� ��������� ��������� ������������ � ���������� 10 �������.",
                    "The process of measuring the frequency meter is started at intervals of 10 seconds.",
    FLAG_1, BIT_FREQ_INTERVAL, pFrequencyCounter, FuncActive, OnPress_Interval, FuncDraw
)

static void OnPress_Interval(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_5(cBillingTime,                                                                                          //--- ���������� - ����� �ר�� ---
    "����� �ר��", "BILLING TIME",
    "����� ������� ���������� ���������.",
    "Selecting the measurement time.",
    "1 ��",     "1 ms",     "������������ ��������� 1 ������������.",
                            "The measurement duration is 1 millisecond.",
    "10 ��",    "10 ms",    "������������ ��������� 10 �����������.",
                            "The measurement duration is 10 milliseconds.",
    "100 ��",   "100 ms",   "������������ ��������� 100 �����������.",
                            "Duration of measurement 100 milliseconds.",
    "1000 ��",  "1000 ms",  "������������ ��������� 1000 �����������.",
                            "The measurement duration is 1000 milliseconds.",
    "10000 ��", "10000 ms", "������������ ��������� 10000 �����������.",
                            "The measurement duration is 10,000 milliseconds.",
    FREQ_BILLING_TIME, pFrequencyCounter, FuncActive, OnPress_BillingTime, FuncDraw
)

static void OnPress_BillingTime(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cResist,
             "������������� �����", "INPUT RESISTANCE",
             "���������� �������������� ����� �����������",
             "Control of the resistance of the frequency meter input",
             "1 ���", "1 MOhm", "������������� ����� 1 ���",
             "Input Impedance 1 MOhm",
             "50 ��", "50 Ohm", "������������� ����� 50 ��",
             "Input Impedance 50 Ohm",
             FLAG_1, BIT_FREQ_RESIST, pFrequencyCounter, FuncActive, OnPress_Resist, FuncDraw
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
             "�����", "AC", "���������� ������������ ��������� �� ���� �����������",
             "The DC component is fed to the frequency meter input",
             "����", "DC", "���������� ������������ �� ��������� �� ���� �����������",
             "The DC component is not input to the frequency meter input",
             FLAG_1, BIT_FREQ_COUPLE, pFrequencyCounter, FuncActive, OnPress_Couple, FuncDraw
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
             DISABLED_RU, DISABLED_EN, "��� �� ����� ����������� ��������",
             "LPF at the frequency meter input is disabled",
             ENABLED_RU, ENABLED_EN, "��� �� ����� ����������� ���������",
             "LPF at the input of the frequency meter is turned on",
             FLAG_1, BIT_FREQ_FILTR, pFrequencyCounter, FuncActive, OnPress_Filtr, FuncDraw
)

static void OnPress_Filtr(bool)
{
    Generator::LoadRegister(Register::FreqMeter_Filtr, (uint)FREQ_FILTR);
}

DEF_CHOICE_5(cAvePeriod,                                                                                       //--- ���������� 3 - ����� �������� ---
    "����� ��������", "NUMBER OF PERIODS",
    "����� ����� ����������� �������� � ������ ��������� �������",
    "Selecting the number of averaging periods in the period measurement mode",
    "1", "1", "��������� ����������� �� ������ �������",
    "Measurements should be made for one period",
    "10", "10", "��������� ����������� �� ������ ��������",
    "Measurements are made for ten periods",
    "100", "100", "��������� ����������� �� ��� ��������",
    "Measurements are made for a hundred periods",
    "1000", "1000", "��������� ����������� �� ������ ��������",
    "Measure to produce for a thousand periods",
    "10000", "10000", "��������� ����������� �� ������ ������� ��������",
    "Measurements are made for ten thousand periods",
    FREQ_AVE_PERIOD, pFrequencyCounter, FuncActive, OnPress_AvePeriod, FuncDraw
)

static void OnPress_AvePeriod(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_5(cTimeStamps,                                                                                       //--- ���������� 3 - ����� ������� ---
    "����� �������", "TIME STAMPS",
    "",
    "",
    "1 ���", "1 kHz", "", "",
    "10 ���", "10 kHz", "", "",
    "100 ���", "100 kHz", "", "",
    "1 ���", "1 MHz", "", "",
    "10 ���", "10 MHz", "", "",
    FREQ_TIME_STAMPS, pFrequencyCounter, FuncActive, OnPress_TimeStamps, FuncDraw
)

static void OnPress_TimeStamps(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cTest,                                                                                                      //--- ���������� 3 - ���� ---
    "����", "TEST",
    "���������/���������� ��������� ������",
    "Enable/disable test mode",
    DISABLED_RU, DISABLED_EN, "", "",
    ENABLED_RU, ENABLED_EN, "", "",
    FLAG_1, BIT_FREQ_TEST, pFrequencyCounter, FuncActive, OnPress_Test, FuncDraw
)

static void OnPress_Test(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_10(pFrequencyCounter,                                                                                                     //--- ���������� ---
    "����������", "FREQUENCY METER",
    "���������� ��������� �����������.",
    "Control of frequency meter functions.",
    cEnableFrequencyCounter,
    cMeasure,
    cInterval,
    cBillingTime,
    cResist,
    cCouple,
    cFiltr,
    cAvePeriod,
    cTimeStamps,
    cTest,
    Page::FrequencyCounter, Menu::mainPage, FuncActive, FuncPress, FuncOnKey
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageFrequencyCounter::WriteRegisterRG9()
{
    uint data = 0;

    //----------- ����� ������ ------------------

    static const uint maskMeasure[2] = {0, 1};
    data |= maskMeasure[FREQ_MEASURE];

    //----------- ����� ����������� �������� ----

    static const uint maskAvePeriod[5] =
    {
        BINARY_U8(00000000),    // 1
        BINARY_U8(00000010),    // 10
        BINARY_U8(00000110),    // 100
        BINARY_U8(00001010),    // 1000
        BINARY_U8(00001110)     // 10000
    };
    data |= maskAvePeriod[FREQ_AVE_PERIOD];

    //---------- ����� ��������� ----------------

    static const uint maskInterval[2] =
    {
        BINARY_U8(00000000),
        BINARY_U8(00010000)
    };
    data |= maskInterval[FREQ_INTERVAL];

    //--------- ����� ����� ---------------------

    static const uint maskTime[5] =
    {
        BINARY_U8(00000000),    // 1 ��
        BINARY_U8(00100000),    // 10 ��
        BINARY_U8(01000000),    // 100 ��
        BINARY_U8(01100000),    // 1 �
        BINARY_U8(10000000)     // 10 �
    };
    data |= maskTime[FREQ_BILLING_TIME];

    //--------- ����� ������� -------------------

    static const uint maskTimeStamp[5] =
    {
        BINARY_U8(00001010),    // 1 ���
        BINARY_U8(00000110),    // 10 ���
        BINARY_U8(00000010),    // 100 ���
        BINARY_U8(00000001),    // 1 ���
        BINARY_U8(00000000)     // 10 ���
    };

    data |= (maskTimeStamp[FREQ_TIME_STAMPS] << 8);

    if(FREQ_TEST)
    {
        _SET_BIT(data, 12);
    }

    Generator::LoadRegister(Register::FPGA_RG9_FreqMeter, data);
    FrequencyMeter::SetInactive();
}
