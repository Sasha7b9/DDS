#pragma once
#include "defines.h"


 /// @brief ���������� �����, ��������� � ������� ���������� ������ ������� Timer_StartMultiMeasurement(). �� ����� (1 << 32)
 /// � ����� ������� 120.000.000 ����� ��� �8-53 � 90.000.000 ����� ��� �8-54.
 /// ������������ ������� �������, ������� ����� ��������� � � ������� - 35 ���.
#define TIME_TICKS (TIM2->CNT)
#define TIME_US    (TIM2->CNT / 90)
#define TIME_MS    HAL_GetTick()

struct Timer
{
    struct Type
    {
        enum E 
        {
            kPressKey,                  ///< ����� �������������, ����� �������� ������� �������.
            kShowLevelRShiftA,          ///< ����� �������������, ����� ���������� ��������� ����� �������� ������ 1.
            kShowLevelRShiftB,          ///< ����� �������������, ����� ���������� ��������� ����� �������� ������ 2.
            kShowLevelTrigLev,          ///< ����� �������������, ����� ���������� ��������� ����� ������ �������������
            kENumSignalsInSec,          ///< ��� ��������� ���������� ���������� ������� � �������.
            kFlashDisplay,              ///< ������ ��� ��������� �������� ������ �����-������ �������.
            kShowMessages,              ///< ������ ��� ��������� ����� ������ �������������� � ��������������� ���������.
            kMenuAutoHide,              ///< ������ ��� ������� ������� ��������� ����.
            kRShiftMarkersAutoHide,     ///< ������ ��� ������� ������� ��������� �������������� ������� �����.
            kUSB,                       ///< ���������������, ��� ����� ����.
            kStopSound,                 ///< ��������� ����
            kTemporaryPauseFPGA,        ///< ��������� ����� ��� �������� ������� �� ������ ����� �������� �����
            kStrNaviAutoHide,           ///< ������� ������ ��������� ����
            kTimerStartP2P,             ///< ������ ��� ������� ���������� ����� ����������� ������
            kTimerDisplay,              ///< ������ �� ������ ��������� ������
            USB,
            kTemp,
            Count
        } value;
        Type(E v) : value(v) {};
        operator uint8() const { return static_cast<uint8>(value); };
    };

    static void Init();

    /// ��������� ������� timer ������� � ����� ������������
    static void Set(Type type, pFuncVV func, uint dTms);

    static void SetAndStartOnce(Type type, pFuncVV func, uint dTms);

    static void SetAndEnable(Type type, pFuncVV func, uint dTms);

    static void StartOnce(Type type);

    static void Enable(Type type);

    static void Disable(Type type);

    static bool IsRun(Type type);

    static void PauseOnTime(uint timeMS);

    static void PauseOnTicks(uint numTicks);
    /// ��������� ������� ��� ��������� ����� �������� �������
    static void StartMultiMeasurement();
    /// ������������� ��������� ����� ������������. ����� ������ Timer_LogPoint �������� ��������� ��������� �� ��� �����
    static void StartLogging();

    static uint LogPointUS(char *name);

    static uint LogPointMS(char *name);
};
