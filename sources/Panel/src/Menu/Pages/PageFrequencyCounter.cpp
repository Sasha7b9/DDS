#include "PageFrequencyCounter.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pFrequencyCounter;
Page *PageFrequencyCounter::pointer = (Page *)&pFrequencyCounter;


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
    FLAG_3, BIT_FREQ_MEASURE, pFrequencyCounter, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cInterval,                                                                                        //--- ���������� - �������� ������� ---
    "�������� �������", "START INTERVAL",
    "����� ��������� ������� ��������� �������.",
    "Selecting the frequency measurement start interval.",
    "1 c", "1 s",   "������ �������� ��������� ��������� ������������ � ���������� 1 �������.",
                    "The measurement of the frequency meter is started at intervals of 1 second.",
    "10 �", "10 s", "������ �������� ��������� ��������� ������������ � ���������� 10 �������.",
                    "The process of measuring the frequency meter is started at intervals of 10 seconds.",
    FLAG_1, BIT_FREQ_INTERVAL, pFrequencyCounter, FuncActive, FuncChangedChoice, FuncDraw
)

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
    BILLING_TIME, pFrequencyCounter, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_4(pFrequencyCounter,                                                                                                     //--- ���������� ---
    "����������", "FREQUENCY METER",
    "���������� ��������� �����������.",
    "Control of frequency meter functions.",
    cEnableFrequencyCounter,
    cMeasure,
    cInterval,
    cBillingTime,
    Page_FrequencyCounter, 0, FuncActive, FuncPress, FuncOnKey
)
