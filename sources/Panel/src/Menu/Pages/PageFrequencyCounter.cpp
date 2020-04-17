#include "PageFrequencyCounter.h"
#include "Settings/Settings.h"
#include "Menu/Menu.h"
#include "Log.h"


extern const PageBase pFrequencyCounter;
Page *PageFrequencyCounter::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pFrequencyCounter));


/// ��������� ��� �������� � ������������ � ������� ���������
static void Tune_Page();
static void OnPress_Interval(bool);
static void OnPress_BillingTime(bool);
static void OnPress_Resist(bool);
static void OnPress_Couple(bool);
static void OnPress_Filtr(bool);
static void OnPress_Test(bool);
static void OnPress_TimeStamps(bool);
static void OnPress_AvePeriod(bool);


static void OnPress_Measure(bool)
{
    Tune_Page();
    PageFrequencyCounter::WriteRegisterRG9();
}

DEF_CHOICE_3( cMeasure,                                                                                                                                      //--- ���������� - ��������� ---
    "���������", "Measurement",
    "��������� ������ ������", "Setting operation mode",
    "���������", "Off",       "��������� ���������", "Measurements off",
    "�������",   "Frequency", "��������� �������",   "Frequency measurement",
    "������",    "Period",    "��������� �������",   "Period measurement",
    FREQ_METER_MEASURE, pFrequencyCounter, Item::FuncActive, OnPress_Measure, FuncDraw
)


DEF_CHOICE_2( cInterval,                                                                                                                              //--- ���������� - �������� ������� ---
    "�������� �������", "Launch interval",
    "����� ��������� ������� ��������� �������", "Frequency start interval selection",
    "1 c",  "1 s",  "������ �������� ��������� ��������� ������������ � ���������� 1 �������",  "The process of measuring the frequency meter is started at intervals of 1 second",
    "10 �", "10 s", "������ �������� ��������� ��������� ������������ � ���������� 10 �������", "The measurement process starts with a 10 second interval",
    set.freq_interval, pFrequencyCounter, Item::FuncActive, OnPress_Interval, FuncDraw
)

volatile const ChoiceBase *pcInterval = &cInterval;

static void OnPress_Interval(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}


DEF_CHOICE_5( cBillingTime,                                                                                                                                //--- ���������� - ����� ����� ---
    "����� �����", "Counting time",
    "����� ������� ���������� ���������", "Timing measurement",
    "1 ��",     "1 ms",     "������������ ��������� 1 ������������",    "1 millisecond measurement duration",
    "10 ��",    "10 ms",    "������������ ��������� 10 �����������",    "Measurement duration 10 milliseconds",
    "100 ��",   "100 ms",   "������������ ��������� 100 �����������",   "Measurement duration 100 milliseconds",
    "1000 ��",  "1000 ms",  "������������ ��������� 1000 �����������",  "Measurement duration 1000 milliseconds",
    "10000 ��", "10000 ms", "������������ ��������� 10000 �����������", "Measurement duration 10000 milliseconds",
    FREQ_BILLING_TIME, pFrequencyCounter, Item::FuncActive, OnPress_BillingTime, FuncDraw
)

static void OnPress_BillingTime(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}


DEF_CHOICE_2(cResist,                                                                                                                              //--- ���������� - ������������� ����� ---
    "������������� �����", "Input impedance",
    "���������� �������������� ����� �����������", "Frequency counter input resistance control",
    "1 ���", "1 MOhm", "������������� ����� 1 ���", "Input impedance 1 MOhm",
    "50 ��", "50 Ohm", "������������� ����� 50 ��", "50 ohm input impedance",
    set.freq_resist, pFrequencyCounter, Item::FuncActive, OnPress_Resist, FuncDraw
)

static void OnPress_Resist(bool)
{
    PGenerator::LoadRegister(Register::FreqMeter_Resist, (uint)set.freq_resist);
}


DEF_CHOICE_2(cCouple,                                                                                                                                             //--- ���������� - ���� ---
    "����", "Couple",
    "����������/��������� ���������� ������������", "Skips / Disables DC",
    "�����", "Alternate", "���������� ������������ ��������� �� ���� �����������",    "The constant component is fed to the input of the frequency counter",
    "����",  "Direct",    "���������� ������������ �� ��������� �� ���� �����������", "The constant component does not go to the input of the frequency meter",
    set.freq_couple, pFrequencyCounter, Item::FuncActive, OnPress_Couple, FuncDraw
)

static void OnPress_Couple(bool)
{
    PGenerator::LoadRegister(Register::FreqMeter_Couple, (uint)set.freq_couple);
}


DEF_CHOICE_2_OLD(cFiltr,                                                                                                                                               //--- ���������� - ��� ---
    "���", "LPF",
    "��������/��������� ������ ������ ������ �� ����� �����������", "Enables / disables the low-pass filter at the input of the frequency meter",
    DISABLED_RU, DISABLED_EN, "��� �� ����� ����������� ��������",  "LPF at the input of the frequency meter is disabled",
    ENABLED_RU,  ENABLED_EN,  "��� �� ����� ����������� ���������", "Low-pass filter at the input of the frequency meter",
    FLAG, BIT_FREQ_FILTR, pFrequencyCounter, Item::FuncActive, OnPress_Filtr, FuncDraw
)

static void OnPress_Filtr(bool)
{
    PGenerator::LoadRegister(Register::FreqMeter_Filtr, (uint)FREQ_FILTR);
}

DEF_CHOICE_5(cAvePeriod,                                                                                                                                //--- ���������� - ����� �������� ---
    "����� ��������", "Number of periods",
    "����� ����� ����������� �������� � ������ ��������� �������", "Choosing the number of averaged periods in period measurement mode",
    "1",     "1",     "��������� ����������� �� ������ �������",          "Measurements on one period",
    "10",    "10",    "��������� ����������� �� ������ ��������",         "Measure over ten periods",
    "100",   "100",   "��������� ����������� �� ��� ��������",            "Measurements over a hundred periods",
    "1000",  "1000",  "��������� ����������� �� ������ ��������",         "Measure over a thousand periods",
    "10000", "10000", "��������� ����������� �� ������ ������� ��������", "Measure over ten thousand periods",
    FREQ_AVE_PERIOD, pFrequencyCounter, Item::FuncActive, OnPress_AvePeriod, FuncDraw
)

static void OnPress_AvePeriod(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}


DEF_CHOICE_5(cTimeStamps,                                                                                                                                //--- ���������� - ����� ������� ---
    "����� �������", "Time stamps",
    "", "",
    "1 ���",   "1 kHz",   "", "",
    "10 ���",  "10 kHz",  "", "",
    "100 ���", "100 kHz", "", "",
    "1 ���",   "1 MHz",   "", "",
    "10 ���",  "10 MHz",  "", "",
    FREQ_TIME_STAMPS, pFrequencyCounter, Item::FuncActive, OnPress_TimeStamps, FuncDraw
)

static void OnPress_TimeStamps(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}


DEF_CHOICE_2_OLD(cTest,                                                                                                                                               //--- ���������� - ���� ---
    "����", "Test",
    "���������/���������� ��������� ������", "Enable / disable test mode",
    DISABLED_RU, DISABLED_EN, "", "",
    ENABLED_RU,  ENABLED_EN,  "", "",
    FLAG, BIT_FREQ_TEST, pFrequencyCounter, Item::FuncActive, OnPress_Test, FuncDraw
)

static void OnPress_Test(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}



static void OnChange_FreqLevel()
{
    PFreqMeter::LoadLevel();
}

DEF_GOVERNOR( gLevel,                                                                                                                                          //--- ���������� - ������� ---
    "�������", "Level",
    "���������� ������ �������������", "Sync level adjustment",
    FREQ_LEVEL, -100, 100, pFrequencyCounter, Item::FuncActive, OnChange_FreqLevel, EmptyFuncVV, 0
)



static void OnChange_Hysteresis()
{
    PFreqMeter::LoadHysteresis();
}

DEF_GOVERNOR( gHysteresis,                                                                                                                                  //--- ���������� - ���������� ---
    "����������", "Hysteresis",
    "����� ���������� ��� ���������� ������� ����� �� �������� ���������", "Sets hysteresis to reduce the effect of interference on measurement accuracy",
    FREQ_HYSTERESIS, 0, 100, pFrequencyCounter, Item::FuncActive, OnChange_Hysteresis, EmptyFuncVV, 0
)

volatile const GovernorBase *pgHysteresis = &gHysteresis;


DEF_PAGE_8( pFrequencyCounter,                                                                                                                                           //--- ���������� ---
    "����������", "FREQMETER", //-V641
    "���������� ��������� �����������", "Freqmeter control",
    &cMeasure,       ///< ���������� - ���������
    &gLevel,         ///< ���������� - �������
    Item::EmptyLight(),
    Item::EmptyLight(),
    &cResist,        ///< ���������� - �������������
    &cCouple,        ///< ���������� - ����
    &cFiltr,         ///< ���������� - ���
    &cTest,          ///< ���������� - ����
    Page::FrequencyCounter, Menu::mainPage, Item::FuncActive, Page::FuncEnter, FuncOnKey, Page::FuncDraw
)


static void Tune_Page()
{
    PageBase *page = const_cast<PageBase *>(&pFrequencyCounter);

    if (FREQ_METER_MEASURE_IS_FREQ)
    {
        page->items[2] = reinterpret_cast<Item *>(const_cast<ChoiceBase *>(&cBillingTime));
        page->items[3] = Item::EmptyLight();
    }
    else if (FREQ_METER_MEASURE_IS_PERIOD)
    {
        page->items[2] = reinterpret_cast<Item *>(const_cast<ChoiceBase *>(&cTimeStamps));
        page->items[3] = reinterpret_cast<Item *>(const_cast<ChoiceBase *>(&cAvePeriod));
    }
    else
    {
        page->items[2] = Item::EmptyLight();
        page->items[3] = Item::EmptyLight(); //-V656
    } //-V656
}

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4310)       // cast truncates constant value
#endif


void PageFrequencyCounter::WriteRegisterRG9()
{
    uint data = 0;

     //--- ����� ������ ------------------
    if(FREQ_METER_MEASURE_IS_PERIOD)
    {
        data |= 1;
    }

    //--- ����� ����������� �������� ----

    static const uint maskAvePeriod[5] =
    {
        BINARY_U8(00000000),    // -V2501   // 1
        BINARY_U8(00000010),    // -V2501   // 10
        BINARY_U8(00000110),    // -V2501   // 100
        BINARY_U8(00001010),    // -V2501   // 1000
        BINARY_U8(00001110)     // -V2501   // 10000
    };
    data |= maskAvePeriod[FREQ_AVE_PERIOD];

    //---------- ����� ��������� ----------------

    static const uint maskInterval[2] =
    {
        BINARY_U8(00000000),    // -V2501
        BINARY_U8(00010000)     // -V2501
    };
    data |= maskInterval[set.freq_interval];

    //--------- ����� ����� ---------------------

    static const uint maskTime[5] =
    {
        BINARY_U8(00000000),    // -V2501               // 1 ��
        BINARY_U8(00100000),    // -V2501               // 10 ��
        BINARY_U8(01000000),    // -V2501   // -V536    // 100 ��
        BINARY_U8(01100000),    // -V2501               // 1 �
        BINARY_U8(10000000)     // -V2501               // 10 �
    };
    data |= maskTime[FREQ_BILLING_TIME];

    //--------- ����� ������� -------------------

    static const uint maskTimeStamp[5] =
    {
        BINARY_U8(00001010),    // -V2501    // 1 ���
        BINARY_U8(00000110),    // -V2501    // 10 ���
        BINARY_U8(00000010),    // -V2501    // 100 ���
        BINARY_U8(00000001),    // -V2501    // 1 ���
        BINARY_U8(00000000)     // -V2501    // 10 ���
    };

    data |= (maskTimeStamp[FREQ_TIME_STAMPS] << 8);

    if(FREQ_TEST)
    {
        _SET_BIT(data, 12);
    }

    PGenerator::LoadRegister(Register::FPGA_RG9_FreqMeter, data);
    PFreqMeter::SetInactive();
}

#ifdef WIN32
#pragma warning(pop)
#endif
