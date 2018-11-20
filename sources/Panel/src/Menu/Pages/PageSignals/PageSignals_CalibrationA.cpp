#include "stdafx.h"
#ifndef WIN32
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/PageSignals.h"
#include "Settings/Settings.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageCalibrationA;
Page *PageSignals::PageCalibration::PageA::pointer = (Page *)&pageCalibrationA;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnChange_NegativeAD9952()
{

}

static void OnPress_NegativeAD9952(bool)
{

}

DEF_GOVERNOR( gNegativeAD9952,                                                                                                       //--- ��������� �������� - ���������� A - AD9952 -5� ---
    "AD9952 -5�", "AD9952 -5V",
    "��������� ������ -5� AD9952",
    "Level setting -5V AD9952",
    CAL_AD9952_OFFSET_NEG, -128, 128, pageCalibrationA, FuncActive, OnChange_NegativeAD9952, EmptyFuncVV, OnPress_NegativeAD9952
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_PositiveAD9952()
{

}

static void OnPress_PositiveAD9952(bool)
{

}

DEF_GOVERNOR( gPositiveAD9952,                                                                                                       //--- ��������� �������� - ���������� A - AD9952 +5� ---
    "AD9952 +5�", "AD9952 +5V",
    "��������� ������ +5� AD9952",
    "Level settings +5V AD9952",
    CAL_AD9952_OFFSET_POS, -128, 128, pageCalibrationA, FuncActive, OnChange_PositiveAD9952, EmptyFuncVV, OnPress_PositiveAD9952
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_ZeroAD9952()
{

}

static void OnPress_ZeroAD9925(bool)
{

}

DEF_GOVERNOR( gZeroAD9952,                                                                                                            //--- ��������� �������� - ���������� A - AD9952 0� ---
    "AD9952 0�", "AD9952 0V",
    "��������� ������ +5� AD9952",
    "Level settings +5V AD9952",
    CAL_AD9952_OFFSET_ZERO, -128, 128, pageCalibrationA, FuncActive, OnChange_ZeroAD9952, EmptyFuncVV, OnPress_ZeroAD9925
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_AmplitudeAD9952()
{

}

static void OnPress_AmplitudeAD9952(bool)
{

}

DEF_GOVERNOR( gAmplitudeAD9952,                                                                                                   //--- ��������� �������� - ���������� A - AD9952 ������ ---
    "AD9952 ������", "AD9952 Amplitude",
    "��������� ������� AD9952",
    "Amplitude settings AD9952",
    CAL_AD9952_AMPLITUDE, -128, 128, pageCalibrationA, FuncActive, OnChange_AmplitudeAD9952, EmptyFuncVV, OnPress_AmplitudeAD9952
)



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_4( pageCalibrationA,                                                                                                                     //--- ��������� �������� - ���������� A ---
    "���������� A", "CALIBRATION A",
    "", "",
    &gPositiveAD9952,       ///< ��������� �������� - ���������� A - AD9952 +5�
    &gZeroAD9952,           ///< ��������� �������� - ���������� A - AD9952 0�
    &gNegativeAD9952,       ///< ��������� �������� - ���������� A - AD9952 -5�
    &gAmplitudeAD9952,      ///< ��������� �������� - ���������� A - AD9952 ������
    Page::Settings_CalibrationA, PageSignals::pointer, FuncActive, FuncPress, FuncOnKey, FuncDrawPage
)
