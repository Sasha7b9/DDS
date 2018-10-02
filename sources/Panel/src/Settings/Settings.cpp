#include "defines.h"
#include "Generator/Signals.h"
#include "Settings.h"
#include "Display/Colors.h"
#include "Display/Display.h"
#include "Display/Painter.h"
#include "Generator/Generator.h"
#include "Hardware/CPU.h"
#include "Menu/Menu.h"


#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4310)
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Settings defSet =
{
    sizeof(Settings),
    {
    },
    {
        MAKE_COLOR(0x00, 0x00, 0x00),   // BLACK
        MAKE_COLOR(0xff, 0xff, 0xff),   // WHITE
        MAKE_COLOR(25,   25,   25),     // GRAY_10
        MAKE_COLOR(0x40, 0x40, 0x40),   // GRAY_25
        MAKE_COLOR(0x80, 0x80, 0x80),   // GRAY_50
        MAKE_COLOR(0xc0, 0xc0, 0xc0),   // GRAY_75
        MAKE_COLOR(0x00, 0x00, 0xff),   // BLUE
        MAKE_COLOR(0x00, 0x00, 25),     // BLUE_10
        MAKE_COLOR(0x00, 0x00, 0x40),   // BLUE_25
        MAKE_COLOR(0x00, 0x00, 0x80),   // BLUE_50
        MAKE_COLOR(0x00, 0x00, 0xc0),   // BLUE_75
        MAKE_COLOR(0x00, 0xff, 0x00),   // GREEN
        MAKE_COLOR(0x00, 13,   0x00),   // GREEN_5
        MAKE_COLOR(0x00, 25,   0x00),   // GREEN_10
        MAKE_COLOR(0x00, 0x40, 0x00),   // GREEN_25
        MAKE_COLOR(0x00, 0x80, 0x00),   // GREEN_50
        MAKE_COLOR(0x00, 0xc0, 0x00),   // GREEN_75
        MAKE_COLOR(0xff, 0x00, 0x00),   // RED
        MAKE_COLOR(0x40, 0x00, 0x00),   // RED_25
        MAKE_COLOR(0x80, 0x00, 0x00),   // RED_50
        MAKE_COLOR(0xc0, 0x00, 0x00)    // RED_75
    },
    { 
        ParameterValue::Frequency,           // sig_parameter[NumForms]
        ParameterValue::Frequency,
        ParameterValue::Frequency,
        ParameterValue::Frequency,
        ParameterValue::Frequency
    },
    (Page *)Menu::mainPage,                 // menu_page
    {0},                                    // menu_posActItem[]
    {0},                                    // menu_currentSubPage[]
    FrequencyMeter::BillingTime::_1ms,      // freq_billingTime
    FrequencyMeter::AvePeriod::_1,          // freq_avePeriod
    FreqTimeStamps::_10MHz,                 // freq_timeStamps
    {false, false},                         // sineManipulation

    BINARY_U32(00000000, 00000000, 00010110, 01011100), // flag1
//                           ||||  ||||||||  ||||||||------ 0  BIT_PARITY         Parity_Off
//                           ||||  ||||||||  |||||||------- 1  BIT_FREQ_INTERVAL  Interval_1
//                           ||||  ||||||||  ||||||-------- 2  BIT_CONSOLE      
//                           ||||  ||||||||  |||||--------- 3  BIT_BACK_BLACK   
//                           ||||  ||||||||  ||||---------- 4  BIT_TUNE_FULL    
//                           ||||  ||||||||  |||----------- 5  BIT_DBG_MODE     
//                           ||||  ||||||||  ||------------ 6  BIT_FREQ_ENABLED 
//                           ||||  ||||||||  |------------- 7  BIT_STATISTICS   
//                           ||||  ||||||||
//                           ||||  ||||||||---------------- 8  BIT_LANGUAGE       RU
//                           ||||  |||||||----------------- 9  BIT_CHAN_A   
//                           ||||  ||||||------------------ 10 BIT_CHAN_B   
//                           ||||  |||||------------------- 11 BIT_CHANNEL        A
//                           ||||  ||||-------------------- 12 BIT_SIZE_BYTE      8bit
//                           ||||  |||--------------------- 13 BIT_STOP_BIT       StopBit_1
//                           ||||  ||---------------------- 14 BIT_FREQ_RESIST
//                           ||||  |----------------------- 15 BIT_FREQ_COUPLE
//                           ||||
//                           ||||-------------------------- 16 BIT_FREQ_FILTR
//                           |||--------------------------- 17 BIT_FREQ_MEASURE
//                           ||---------------------------- 18 BIT_FREQ_TEST
//                           |----------------------------- 19 BIT_BIG_SYMBOLS
};


#ifdef WIN32
#pragma warning(pop)
#endif

Settings set = defSet;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Settings::Save()
{
    CPU::FLASH_::SaveSettings();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Settings::Load(bool _default)
{
    set = defSet;

    if(_default)
    {
        set = defSet;
    }
    else
    {
        CPU::FLASH_::LoadSettings();
    }

    Generator::TuneChannel(Chan::A);
    Generator::TuneChannel(Chan::B);
    
    Painter::LoadPalette();
}
