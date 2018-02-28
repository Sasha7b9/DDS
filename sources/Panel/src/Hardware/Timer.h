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


class Timer
{
friend class CPU;

private:
    
    static void Init();

public:
    /// ��������� ������� timer ������� � ����� ������������
    static void Set(TypeTimer2 type, pFuncVV func, uint dTms);

    static void SetAndStartOnce(TypeTimer2 type, pFuncVV func, uint dTms);

    static void SetAndEnable(TypeTimer2 type, pFuncVV func, uint dTms);

    static void StartOnce(TypeTimer2 type);

    static void Enable(TypeTimer2 type);

    static void Disable(TypeTimer2 type);

    static bool IsRun(TypeTimer2 type);

    static void PauseOnTime(uint timeMS);

    static void PauseOnTicks(uint numTicks);
    /// ������������� ��������� ����� ������������. ����� ������ Timer_LogPoint �������� ��������� ��������� �� ��� �����
    static void StartLogging();

    static uint LogPointUS(char *name);

    static uint LogPointMS(char *name);

};

/** @}  @}
 */
