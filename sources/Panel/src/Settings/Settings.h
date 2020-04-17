#pragma once
#include "common/CommonTypes.h"
#include "Menu/MenuItems.h"
#include "FreqMeter/FreqMeter_p.h"
#include "Generator/Generator_p.h"
#include "Settings/SettingsTypes.h"


#define LANGUAGE                     (set.lang)
#define COLOR(x)                     (set.disp_Colors[x])
#define CURRENT_PAGE                 (set.menu_currentPage)
#define MENU_POS_ACT_ITEM(x)         (set.menu_posActItem[x])
#define MENU_CURRENT_SUBPAGE(x)      (set.menu_currentSubPage[x])
#define CURRENT_CHANNEL              (set.current)
#define CURRENT_CHANNEL_IS(ch)       (CURRENT_CHANNEL == (ch))
#define FREQ_METER_MEASURE           (set.freq.measure)
#define FREQ_METER_MEASURE_IS_FREQ   (FREQ_METER_MEASURE == FreqMeasure::Freq)
#define FREQ_METER_MEASURE_IS_PERIOD (FREQ_METER_MEASURE == FreqMeasure::Period)
#define FREQ_METER_ENABLED           (FREQ_METER_MEASURE != FreqMeasure::Disable)
#define FREQ_AVE_PERIOD              (set.freq.avePeriod)
#define FREQ_BILLING_TIME            (set.freq.billingTime)
#define FREQ_TIME_STAMPS             (set.freq.timeStamps)
#define FREQ_LEVEL                   (set.freq.level)
#define FREQ_HYSTERESIS              (set.freq.hysteresis)


struct SettingsFreqMeter
{
    PFreqMeter::BillingTime billingTime;   // ����� �����
    PFreqMeter::AvePeriod   avePeriod;     // ����� ����������� �������� � ������ ��������� �������
    FreqTimeStamps          timeStamps;    // ����� �������
    FreqMeasure::E          measure;       // ����� ��������� �����������
    int16                   level;         // ������� �������������
    int16                   hysteresis;    // �������� �����������
    FreqInterval::E         interval;
    FreqResist::E           resist;
    FreqCouple::E           couple;
    FreqFiltr::E            filtr;
    FreqTest::E             test;
};


struct Settings // -V690
{
    uint16    size;                             // ������ ��������� Settings
    col_val   disp_Colors[32];                  // �����
    Page*     menu_currentPage;                 // ����� �������� �������� ����. 0, ���� ������� ������� ��������
    int8      menu_posActItem[Page::Count];     // ������� ��������� ������ ���� ��� ������ ��������
    int8      menu_currentSubPage[Page::Count]; // ����� ������� ����������� ��� ������ ��������
    int8      showConsole;
    bool      dbgModeEnabled;
    bool      enabled[2];
    Chan::E   current;
    bool      showStatistics;
    uint8     lang;
    bool      bigSymbols;                       // ���� 1, �� ������� ��������� ���� ������������
    bool      showSends;
    uint8     bitPE15;
    uint8     bitPB10;
    uint8     bitPF0;
    uint8     bitPF5;
    uint8     bitPC13;
    uint8     bitPC14;

    SettingsFreqMeter freq;

    void SaveToMemory();
    void LoadFromMemory();
    void LoadDefault();
    void LoadToDevice();

    Settings& operator=(const Settings &rhs);

private:
    // ���� ����� ��������� ������� ��������� �������� Store
    static Settings stored;
};


extern Settings set;
