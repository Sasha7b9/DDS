#include "PageFrequencyCounter3.h"
#include "PageFrequencyCounter.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pFrequencyCounte3;
Page *PageFrequencyCounter3::pointer = (Page *)&pFrequencyCounte3;

static void OnPress_Test(bool);
static void OnPress_TimeStamps(bool);
static void OnPress_AvePeriod(bool);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_5(cAvePeriod,                                                                                       //--- ���������� 3 - ����� �������� ---
    "����� ��������", "NUMBER OF PERIODS",
    "����� ����� ����������� �������� � ������ ��������� �������",
    "Selecting the number of averaging periods in the period measurement mode",
    "1", "1",           "��������� ����������� �� ������ �������",
                        "Measurements should be made for one period",
    "10", "10",         "��������� ����������� �� ������ ��������",
                        "Measurements are made for ten periods",
    "100", "100",       "��������� ����������� �� ��� ��������",
                        "Measurements are made for a hundred periods",
    "1000", "1000",     "��������� ����������� �� ������ ��������",
                        "Measure to produce for a thousand periods",
    "10000", "10000",   "��������� ����������� �� ������ ������� ��������",
                        "Measurements are made for ten thousand periods",
    FREQ_AVE_PERIOD, pFrequencyCounte3, FuncActive, OnPress_AvePeriod, FuncDraw
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
    "1 ���",    "1 kHz",    "", "",
    "10 ���",   "10 kHz",   "", "",
    "100 ���",  "100 kHz",  "", "",
    "1 ���",    "1 MHz",    "", "",
    "10 ���",   "10 MHz",   "", "",
    FREQ_TIME_STAMPS, pFrequencyCounte3, FuncActive, OnPress_TimeStamps, FuncDraw
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
    ENABLED_RU,  ENABLED_EN,  "", "",
    FLAG_1, BIT_FREQ_TEST, pFrequencyCounte3, FuncActive, OnPress_Test, FuncDraw
)

static void OnPress_Test(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_3(pFrequencyCounte3,                                                                                                   //--- ���������� 3 ---
    "���������� 3", "FREQUENCY COUNTER 3",
    "���������� ��������� �����������",
    "Control of frequency meter functions",
    cAvePeriod,
    cTimeStamps,
    cTest,
    Page::FrequencyCounter3, 0, FuncActive, FuncPress, FuncOnKey
)
