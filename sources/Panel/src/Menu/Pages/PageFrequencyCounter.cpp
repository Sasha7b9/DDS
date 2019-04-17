#include "stdafx.h"
#ifndef WIN32
#include "PageFrequencyCounter.h"
#include "Settings/Settings.h"
#include "Menu/Menu.h"
#include "Log.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pFrequencyCounter;
Page *PageFrequencyCounter::pointer = (Page *)&pFrequencyCounter;


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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Measure(bool)
{
    Tune_Page();
    PageFrequencyCounter::WriteRegisterRG9();
}

DEF_CHOICE_3( cMeasure,                                                                                                                                      //--- ���������� - ��������� ---
    "���������",
    "��������� ������ ������"
    ,
    "���������", "��������� ���������",
    "�������",   "��������� �������",
    "������",    "��������� �������",
    FREQ_METER_MEASURE, pFrequencyCounter, Item::FuncActive, OnPress_Measure, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cInterval,                                                                                                                              //--- ���������� - �������� ������� ---
    "�������� �������",
    "����� ��������� ������� ��������� �������."
    ,
    "1 c", "������ �������� ��������� ��������� ������������ � ���������� 1 �������.",
    "10 �", "������ �������� ��������� ��������� ������������ � ���������� 10 �������.",
    FLAG_1, BIT_FREQ_INTERVAL, pFrequencyCounter, Item::FuncActive, OnPress_Interval, FuncDraw
)

static void OnPress_Interval(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_5( cBillingTime,                                                                                                                                //--- ���������� - ����� ����� ---
    "����� �����",
    "����� ������� ���������� ���������."
    ,
    "1 ��",     "������������ ��������� 1 ������������.",
    "10 ��",    "������������ ��������� 10 �����������.",
    "100 ��",   "������������ ��������� 100 �����������.",
    "1000 ��",  "������������ ��������� 1000 �����������.",
    "10000 ��", "������������ ��������� 10000 �����������.",
    FREQ_BILLING_TIME, pFrequencyCounter, Item::FuncActive, OnPress_BillingTime, FuncDraw
)

static void OnPress_BillingTime(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cResist,                                                                                                                              //--- ���������� - ������������� ����� ---
    "������������� �����",
    "���������� �������������� ����� �����������"
    ,
    "1 ���", "������������� ����� 1 ���",
    "50 ��", "������������� ����� 50 ��",
    FLAG_1, BIT_FREQ_RESIST, pFrequencyCounter, Item::FuncActive, OnPress_Resist, FuncDraw
)

static void OnPress_Resist(bool)
{
    Generator::LoadRegister(Register::FreqMeter_Resist, (uint)FREQ_RESIST);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cCouple,                                                                                                                                             //--- ���������� - ���� ---
    "����",
    "����������/��������� ���������� ������������"
    ,
    "�����","���������� ������������ ��������� �� ���� �����������",
    "����", "���������� ������������ �� ��������� �� ���� �����������",
    FLAG_1, BIT_FREQ_COUPLE, pFrequencyCounter, Item::FuncActive, OnPress_Couple, FuncDraw
)

static void OnPress_Couple(bool)
{
    Generator::LoadRegister(Register::FreqMeter_Couple, (uint)FREQ_COUPLE);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cFiltr,                                                                                                                                               //--- ���������� - ��� ---
    "���",
    "��������/��������� ������ ������ ������ �� ����� �����������"
    ,
    DISABLED_RU, "��� �� ����� ����������� ��������",
    ENABLED_RU,  "��� �� ����� ����������� ���������",
    FLAG_1, BIT_FREQ_FILTR, pFrequencyCounter, Item::FuncActive, OnPress_Filtr, FuncDraw
)

static void OnPress_Filtr(bool)
{
    Generator::LoadRegister(Register::FreqMeter_Filtr, (uint)FREQ_FILTR);
}

DEF_CHOICE_5(cAvePeriod,                                                                                                                                //--- ���������� - ����� �������� ---
    "����� ��������",
    "����� ����� ����������� �������� � ������ ��������� �������"
    ,
    "1",     "��������� ����������� �� ������ �������",
    "10",    "��������� ����������� �� ������ ��������",
    "100",   "��������� ����������� �� ��� ��������",
    "1000",  "��������� ����������� �� ������ ��������",
    "10000", "��������� ����������� �� ������ ������� ��������",
    FREQ_AVE_PERIOD, pFrequencyCounter, Item::FuncActive, OnPress_AvePeriod, FuncDraw
)

static void OnPress_AvePeriod(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_5(cTimeStamps,                                                                                                                                //--- ���������� - ����� ������� ---
    "����� �������",
    ""
    ,
    "1 ���",    "", 
    "10 ���",   "", 
    "100 ���",  "", 
    "1 ���",    "", 
    "10 ���",   "", 
    FREQ_TIME_STAMPS, pFrequencyCounter, Item::FuncActive, OnPress_TimeStamps, FuncDraw
)

static void OnPress_TimeStamps(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cTest,                                                                                                                                               //--- ���������� - ���� ---
    "����",
    "���������/���������� ��������� ������"
    ,
    DISABLED_RU, "",
    ENABLED_RU,  "",
    FLAG_1, BIT_FREQ_TEST, pFrequencyCounter, Item::FuncActive, OnPress_Test, FuncDraw
)

static void OnPress_Test(bool)
{
    PageFrequencyCounter::WriteRegisterRG9();
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_FreqLevel()
{
    FrequencyMeter::LoadLevel();
}

DEF_GOVERNOR( gLevel,                                                                                                                                          //--- ���������� - ������� ---
    "�������",
    "���������� ������ �������������",
    FREQ_LEVEL, -100, 100, pFrequencyCounter, Item::FuncActive, OnChange_FreqLevel, EmptyFuncVV, 0
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_Hysteresis()
{
    FrequencyMeter::LoadHysteresis();
}

DEF_GOVERNOR( gHysteresis,                                                                                                                                  //--- ���������� - ���������� ---
    "����������",
    "����� ���������� ��� ���������� ������� ����� �� �������� ���������",
    FREQ_HYSTERESIS, 0, 100, pFrequencyCounter, Item::FuncActive, OnChange_Hysteresis, EmptyFuncVV, 0
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_8( pFrequencyCounter,  // -V641 // -V1027                                                                                                                       //--- ���������� ---
    "����������",
    "���������� ��������� �����������."
    ,
    &cMeasure,       ///< ���������� - ���������
    &gLevel,         ///< ���������� - �������
    0,
    0,
    &cResist,        ///< ���������� - �������������
    &cCouple,        ///< ���������� - ����
    &cFiltr,         ///< ���������� - ���
    &cTest,          ///< ���������� - ����
    Page::FrequencyCounter, Menu::mainPage, Item::FuncActive, FuncPress, FuncOnKey, Page::FuncDraw
)


static void Tune_Page()
{
    PageBase *page = (PageBase *)&pFrequencyCounter;

    if (FREQ_METER_MEASURE_IS_FREQ)
    {
        page->items[2] = (Item *)&cBillingTime; // -V641
        page->items[3] = 0;
    }
    else if (FREQ_METER_MEASURE_IS_PERIOD)
    {
        page->items[2] = (Item *)&cTimeStamps;  // -V641
        page->items[3] = (Item *)&cAvePeriod;   // -V641
    }
    else
    {
        page->items[2] = 0;
        page->items[3] = 0;
    }
}

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4310)       // cast truncates constant value
#endif

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageFrequencyCounter::WriteRegisterRG9()
{
    uint data = 0;

    //----------- ����� ������ ------------------
    if(FREQ_METER_MEASURE_IS_PERIOD)
    {
        data |= 1;
    }

    //----------- ����� ����������� �������� ----

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
    data |= maskInterval[FREQ_INTERVAL];

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

    Generator::LoadRegister(Register::FPGA_RG9_FreqMeter, data);
    FrequencyMeter::SetInactive();
}

#ifdef WIN32
#pragma warning(pop)
#endif
