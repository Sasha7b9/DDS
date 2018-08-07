#include "PageFrequencyCounter3.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pFrequencyCounte3;
Page *PageFrequencyCounter3::pointer = (Page *)&pFrequencyCounte3;


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
    FREQ_AVE_PERIOD, pFrequencyCounte3, FuncActive, FuncChangedChoice, FuncDraw
)

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
    FREQ_TIME_STAMPS, pFrequencyCounte3, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_2(pFrequencyCounte3,                                                                                                   //--- ���������� 3 ---
    "���������� 3", "FREQUENCY COUNTER 3",
    "���������� ��������� �����������",
    "Control of frequency meter functions",
    cAvePeriod,
    cTimeStamps,
    Page_FrequencyCounter3, 0, FuncActive, FuncPress
)
