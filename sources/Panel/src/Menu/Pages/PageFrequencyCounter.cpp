#include "PageFrequencyCounter.h"
#include "Settings/Settings.h"


extern const PageBase pFrequencyCounter;
Page *PageFrequencyCounter::pointer = (Page *)&pFrequencyCounter;


DEF_CHOICE_2(cEnableFrequencyCounter,
    "�����������", "DISPLAY",
    "�������� � ��������� ����� �����������",
    "Turns the frequency meter output on and off",
    DISABLED_RU, DISABLED_EN,
    ENABLED_RU,  ENABLED_EN,
    FREQ_COUNTER_ENABLED, pFrequencyCounter, FuncActive, FuncChangedChoice, FuncDraw
)


DEF_PAGE_1(pFrequencyCounter,
    "����������", "FRUENCY METER",
    "", "",
    cEnableFrequencyCounter,
    Page_FrequencyCounter, 0, FuncActive, FuncPress
)
