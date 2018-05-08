#pragma once
#include "defines.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Hardware
 *  @{
 *  @defgroup Timer
 *  @brief ������ �������
 *  @{
 */

 /// @brief ���������� �����, ��������� � ������� ���������� ������ ������� Timer_StartMultiMeasurement(). �� ����� (1 << 32)
 /// � ����� ������� 120.000.000 ����� ��� �8-53 � 90.000.000 ����� ��� �8-54.
 /// ������������ ������� �������, ������� ����� ��������� � � ������� - 35 ���.
#define TIME_TICKS (TIM2->CNT)
#define TIME_US    (TIM2->CNT / 90)
#define TIME_MS    HAL_GetTick()

enum TypeTimer
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
    kTemp,
    NumTimers
};


class Timer
{
public:

    static void Init();

    static void DeInit();
    /// ��������� ������� timer ������� � ����� ������������
    static void Set(TypeTimer type, pFuncVV func, uint dTms);

    static void SetAndStartOnce(TypeTimer type, pFuncVV func, uint dTms);

    static void SetAndEnable(TypeTimer type, pFuncVV func, uint dTms);

    static void StartOnce(TypeTimer type);

    static void Enable(TypeTimer type);

    static void Disable(TypeTimer type);

    static bool IsRun(TypeTimer type);

    static void PauseOnTime(uint timeMS);

    static void PauseOnTicks(uint numTicks);
    /// ��������� ������� ��� ��������� ����� �������� �������
    static void StartMultiMeasurement();
    /// ������������� ��������� ����� ������������. ����� ������ Timer_LogPoint �������� ��������� ��������� �� ��� �����
    static void StartLogging();

    static uint LogPointUS(char *name);

    static uint LogPointMS(char *name);
};


/** @}  @}
 */
