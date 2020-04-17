#pragma once
#include "common/CommonTypes.h"
#include "Menu/MenuItems.h"
#include "FreqMeter/FreqMeter_p.h"
#include "Generator/Generator_p.h"
#include "Settings/SettingsTypes.h"


#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4623)
#endif


#define LANGUAGE                     (set.lang)
#define COLOR(x)                     (set.disp_Colors[x])
#define CURRENT_PAGE                 (set.menu_currentPage)
#define MENU_POS_ACT_ITEM(x)         (set.menu_posActItem[x])
#define MENU_CURRENT_SUBPAGE(x)      (set.menu_currentSubPage[x])
#define CURRENT_CHANNEL              (set.current)
#define CURRENT_CHANNEL_IS(ch)       (CURRENT_CHANNEL == (ch))
#define FREQ_METER_MEASURE           (set.freq_measure)
#define FREQ_METER_MEASURE_IS_FREQ   (FREQ_METER_MEASURE == FreqMeasure::Freq)
#define FREQ_METER_MEASURE_IS_PERIOD (FREQ_METER_MEASURE == FreqMeasure::Period)
#define FREQ_METER_ENABLED           (FREQ_METER_MEASURE != FreqMeasure::Disable)
#define FREQ_AVE_PERIOD              (set.freq_avePeriod)
#define FREQ_BILLING_TIME            (set.freq_billingTime)
#define FREQ_TIME_STAMPS             (set.freq_timeStamps)
#define FREQ_LEVEL                   (set.freq_level)
#define FREQ_HYSTERESIS              (set.freq_hysteresis)


#pragma pack(push, 1)

class Settings // -V690
{
public:
    uint16                  size;                             // ������ ��������� Settings
    col_val                 disp_Colors[32];                  // �����
    Page*                   menu_currentPage;                 // ����� �������� �������� ����. 0, ���� ������� ������� ��������
    int8                    menu_posActItem[Page::Count];     // ������� ��������� ������ ���� ��� ������ ��������
    int8                    menu_currentSubPage[Page::Count]; // ����� ������� ����������� ��� ������ ��������
    PFreqMeter::BillingTime freq_billingTime;                 // ����� �����
    PFreqMeter::AvePeriod   freq_avePeriod;                   // ����� ����������� �������� � ������ ��������� �������
    FreqTimeStamps          freq_timeStamps;                  // ����� �������
    FreqMeasure::E          freq_measure;                     // ����� ��������� �����������
    int16                   freq_level;                       // ������� �������������
    int16                   freq_hysteresis;                  // �������� �����������
    FreqInterval::E         freq_interval;
    int8                    showConsole;
    bool                    dbgModeEnabled;
    bool                    enabled[2];
    Chan::E                 current;
    bool                    showStatistics;
    FreqResist::E           freq_resist;
    FreqCouple::E           freq_couple;
    FreqFiltr::E            freq_filtr;
    uint8                   lang;
    FreqTest::E             freq_test;
    bool                    bigSymbols;                       // ���� 1, �� ������� ��������� ���� ������������
    bool                    showSends;
    uint8                   bitPE15;
    uint8                   bitPB10;
    uint8                   bitPF0;
    uint8                   bitPF5;
    uint8                   bitPC13;
    uint8                   bitPC14;

    void SaveToMemory();
    void LoadFromMemory();
    void LoadDefault();
    void LoadToDevice();

    Settings& operator=(const Settings &rhs);

private:
    // ���� ����� ��������� ������� ��������� �������� Store
    static Settings stored;
};

#pragma pack(pop)

extern Settings set;


#ifdef WIN32
#pragma warning(pop)
#endif
