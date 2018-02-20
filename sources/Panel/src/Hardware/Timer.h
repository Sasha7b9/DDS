#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Hardware
 *  @{
 *  @defgroup Timer
 *  @brief ������ �������
 *  @{
 */

typedef enum
{
    kPressKey,                  ///< ����� �������������, ����� �������� ������� �������.
    kShowLevelRShiftA,          ///< ����� �������������, ����� ���������� ��������� ����� �������� ������ 1.
    kShowLevelRShiftB,          ///< ����� �������������, ����� ���������� ��������� ����� �������� ������ 2.
    kShowLevelTrigLev,          ///< ����� �������������, ����� ���������� ��������� ����� ������ �������������
    kENumSignalsInSec,           ///< ��� ��������� ���������� ���������� ������� � �������.
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
    NumTimers
} TypeTimer2;


void Timer_Init();
/// ��������� ������� timer ������� � ����� ������������
void Timer_Set(TypeTimer2 type, pFuncVV func, uint dTms);

void Timer_SetAndStartOnce(TypeTimer2 type, pFuncVV func, uint dTms);

void Timer_SetAndEnable(TypeTimer2 type, pFuncVV func, uint dTms);

void Timer_StartOnce(TypeTimer2 type);

void Timer_Enable(TypeTimer2 type);

void Timer_Disable(TypeTimer2 type);

bool Timer_IsRun(TypeTimer2 type);

void Timer_PauseOnTime(uint timeMS);

void Timer_PauseOnTicks(uint numTicks);
/// ������������� ��������� ����� ������������. ����� ������ Timer_LogPoint �������� ��������� ��������� �� ��� �����
void Timer_StartLogging();

uint Timer_LogPointUS(char *name);

uint Timer_LogPointMS(char *name);


/// @brief ���������� �����, ��������� � ������� ���������� ������ ������� Timer_StartMultiMeasurement(). �� ����� (1 << 32)
/// � ����� ������� 120.000.000 ����� ��� �8-53 � 90.000.000 ����� ��� �8-54.
/// ������������ ������� �������, ������� ����� ��������� � � ������� - 35 ���.
    
/** @}  @}
 */
