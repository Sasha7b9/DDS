#pragma once
#include "defines.h"



// ������ ������������ ��� �����������, ���� ����� � HardFault_Handler() ����������� ��� ����������
//#define DEBUG_POINT Debug::line = __LINE__; Debug::file = __FILE__;



namespace Debug
{
    void StartProfiling();
    void PointProfiling(char *name);

    void ClearTimeCounter();
    void StartIncreaseCounter();
    void StopIncreaseCounter();
    uint GetTimeCounterUS();

    extern int line;
    extern char *file;
};
