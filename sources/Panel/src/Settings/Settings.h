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


#define COLOR(x)                (set.disp_Colors[x])
#define CURRENT_PAGE            (set.menu_currentPage)

#define MENU_POS_ACT_ITEM(x)    (set.menu_posActItem[x])
#define MENU_CURRENT_SUBPAGE(x) (set.menu_currentSubPage[x])

#define FL(numBit)              ((FLAG >> (numBit)) & 0x01)
#define FL_DBG(numBit)          ((FLAG_DBG >> (numBit)) & 0x01)
#define SET_FL(numBit)          ((FLAG) |= (1 << (numBit)))
#define CLEAR_FL(numBit)        ((FLAG) &= (~(1 << (numBit))))

#define CURRENT_CHANNEL         (set.current)
#define CURRENT_CHANNEL_IS(ch)  (CURRENT_CHANNEL == (ch))

#define CONSOLE_ENABLED         (FL(BIT_CONSOLE))
#define DEBUG_MODE_ENABLED      (FL(BIT_DBG_MODE))
#define SHOW_STATISTICS         (FL(BIT_STATISTICS))
/// ���� true, �� ������� � ������ ����������� ��� ������ �������� �����
#define DEBUG_SHOW_SENDS        (FL(BIT_SHOW_SENDS))

#define LANGUAGE                (FL(BIT_LANGUAGE))

#define FREQ_FILTR                  ((FreqFiltr)FL(BIT_FREQ_FILTR))
#define FREQ_METER_MEASURE          (set.freq_measure)
#define FREQ_METER_MEASURE_IS_FREQ   (FREQ_METER_MEASURE == FreqMeasure::Freq)
#define FREQ_METER_MEASURE_IS_PERIOD (FREQ_METER_MEASURE == FreqMeasure::Period)
#define FREQ_METER_ENABLED           (FREQ_METER_MEASURE != FreqMeasure::Disable)
#define FREQ_AVE_PERIOD             (set.freq_avePeriod)
#define FREQ_BILLING_TIME           (set.freq_billingTime)
#define FREQ_TIME_STAMPS            (set.freq_timeStamps)
#define FREQ_TEST                   ((FreqTest)FL(BIT_FREQ_TEST))
#define FREQ_LEVEL                  (set.freq_level)
#define FREQ_HYSTERESIS             (set.freq_hysteresis)

#define BIG_SYMBOLS                 ((FL(BIT_BIG_SYMBOLS)))


#pragma pack(push, 1)

class Settings // -V690
{
public:
    uint16                  size;                                   // ������ ��������� Settings
    col_val                 disp_Colors[32];                        // �����
    Page*                   menu_currentPage;                       // ����� �������� �������� ����. 0, ���� ������� ������� ��������
    int8                    menu_posActItem[Page::Count];           // ������� ��������� ������ ���� ��� ������ ��������
    int8                    menu_currentSubPage[Page::Count];       // ����� ������� ����������� ��� ������ ��������
    PFreqMeter::BillingTime freq_billingTime;                       // ����� �����
    PFreqMeter::AvePeriod   freq_avePeriod;                         // ����� ����������� �������� � ������ ��������� �������
    FreqTimeStamps          freq_timeStamps;                        // ����� �������
    FreqMeasure::E          freq_measure;                           // ����� ��������� �����������
    int16                   freq_level;                             // ������� �������������
    int16                   freq_hysteresis;                        // �������� �����������
    FreqInterval::E         freq_interval;
    int8                    showConsole;
    bool                    dbgModeEnabled;
    bool                    enabled[2];
    Chan::E                 current;
    bool                    showStatistics;
    FreqResist::E           freq_resist;
    FreqCouple::E           freq_couple;

    uint                        flag;
    uint                        flagDBG;

#define FLAG                    set.flag
#define FLAG_DBG                set.flagDBG

#define BIT_PE15            0
#define BIT_PB10            1
#define BIT_PF0             2
#define BIT_PF5             3
#define BIT_PC13            4
#define BIT_PC14            5


#define BIT_FREQ_FILTR    16  // FreqFiltr   - ��� �����������
#define BIT_LANGUAGE      17  // ����
#define BIT_FREQ_TEST     18  // FreqTest    - ��������� ��������� ������
#define BIT_BIG_SYMBOLS   19  // ���� 1, �� ������� ��������� ���� ������������
#define BIT_SHOW_SENDS    20  // ���� 1, �� ����� ���������� ���������� ���������

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
