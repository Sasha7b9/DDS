#include "PageFrequencyCounter.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pFrequencyCounter;
Page *PageFrequencyCounter::pointer = (Page *)&pFrequencyCounter;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2(cEnableFrequencyCounter,                                                                               //--- ���������� - ����������� ---
    "�����������", "DISPLAY",
    "�������� � ��������� ����� �����������",
    "Turns the frequency meter output on and off",
    DISABLED_RU, DISABLED_EN, "",
                              "",
    ENABLED_RU,  ENABLED_EN,  "",
                              "",
    FREQ_COUNTER_ENABLED, pFrequencyCounter, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cInterval,                                                                                        //--- ���������� - �������� ������� ---
    "�������� �������", "START INTERVAL",
    "����� ��������� ������� ��������� �������",
    "Selecting the frequency measurement start interval",
    "1 c", "1 s",   "",
                    "",
    "10 �", "10 s", "",
                    "",
    INTERVAL, pFrequencyCounter, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_5(cBillingTime,
    "����� �ר��", "BILLING TIME",
    "����� ������� ���������� ���������",
    "Selecting the measurement time",
    "1 ��",     "1 ms",     "",
                            "",
    "10 ��",    "10 ms",    "",
                            "",
    "100 ��",   "100 ms",   "",
                            "",
    "1000 ��",  "1000 ms",  "",
                            "",
    "10000 ��", "10000 ms", "",
                            "",
    BILLING_TIME, pFrequencyCounter, FuncActive, FuncChangedChoice, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_3(pFrequencyCounter,
    "����������", "FRUENCY METER",
    "���������� ��������� �����������",
    "Control of frequency meter functions",
    cEnableFrequencyCounter,
    cInterval,
    cBillingTime,
    Page_FrequencyCounter, 0, FuncActive, FuncPress
)
