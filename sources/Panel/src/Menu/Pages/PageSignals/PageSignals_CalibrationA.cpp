#include "stdafx.h"
#ifndef WIN32
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/PageSignals.h"
#include "Settings/CalibrationSettings.h"
#endif


/// ����������� �������� �������������� ������������
#define MIN -128
/// ������������ �������� �������������� ������������
#define MAX 127


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageCalibrationA;
Page *PageSignals::PageCalibration::PageA::pointer = (Page *)&pageCalibrationA;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_OffsetAD9952(bool enter, KoeffCal::E koeff)
{
    PageSignals::PageCalibration::OnPress_OffsetAD9952(Chan::A, enter, koeff);
}

static void OnChange_OffsetAD9952(KoeffCal::E koeff)
{
    PageSignals::PageCalibration::WriteKoeffCal(Chan::A, koeff);
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_NegativeAD9952()
{
    OnChange_OffsetAD9952(KoeffCal::AD9952_NEG);
}

static void OnPress_NegativeAD9952(bool enter)
{
    OnPress_OffsetAD9952(enter, KoeffCal::AD9952_NEG);
}

DEF_GOVERNOR(gNegativeAD9952,                                                                                                       //--- ��������� �������� - ���������� A - AD9952 -5� ---
    "AD9952 -5�", "AD9952 -5V",
    "��������� ������ -5� AD9952",
    "Level setting -5V AD9952",
    CAL_AD9952_OFFSET_NEG(Chan::A), 3000, 4095, pageCalibrationA, FuncActive, OnChange_NegativeAD9952, EmptyFuncVV, OnPress_NegativeAD9952
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_PositiveAD9952()
{
    OnChange_OffsetAD9952(KoeffCal::AD9952_POS);
}

static void OnPress_PositiveAD9952(bool enter)
{
    OnPress_OffsetAD9952(enter, KoeffCal::AD9952_POS);
}

DEF_GOVERNOR( gPositiveAD9952,                                                                                                       //--- ��������� �������� - ���������� A - AD9952 +5� ---
    "AD9952 +5�", "AD9952 +5V",
    "��������� ������ +5� AD9952",
    "Level settings +5V AD9952",
    CAL_AD9952_OFFSET_POS(Chan::A), 0, 1000, pageCalibrationA, FuncActive, OnChange_PositiveAD9952, EmptyFuncVV, OnPress_PositiveAD9952
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_ZeroAD9952()
{
    OnChange_OffsetAD9952(KoeffCal::AD9952_ZERO);
}

static void OnPress_ZeroAD9952(bool enter)
{
    OnPress_OffsetAD9952(enter, KoeffCal::AD9952_ZERO);
}

DEF_GOVERNOR( gZeroAD9952,                                                                                                            //--- ��������� �������� - ���������� A - AD9952 0� ---
    "AD9952 0�", "AD9952 0V",
    "��������� ������ +5� AD9952",
    "Level settings +5V AD9952",
    CAL_AD9952_OFFSET_ZERO(Chan::A), 1000, 3000, pageCalibrationA, FuncActive, OnChange_ZeroAD9952, EmptyFuncVV, OnPress_ZeroAD9952
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChange_AmplitudeAD9952()
{

}

static void OnPress_AmplitudeAD9952(bool enter)
{
    if (enter)
    {
        PageSignals::PageCalibration::PrepareForAmplitudeAD9952(Chan::A);
    }
}

DEF_GOVERNOR( gAmplitudeAD9952,                                                                                                   //--- ��������� �������� - ���������� A - AD9952 ������ ---
    "AD9952 ������", "AD9952 Amplitude",
    "��������� ������� AD9952",
    "Amplitude settings AD9952",
    CAL_AD9952_AMPLITUDE(Chan::A), MIN, MAX, pageCalibrationA, FuncActive, OnChange_AmplitudeAD9952, EmptyFuncVV, OnPress_AmplitudeAD9952
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
