#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Hardware
{
public:

    void Init();
    /// ���������� �� PA2 ������� ����, ��� ��������� �����
    void SetBusy();
    /// ���������� �� PA2 ������� ����, ��� ��������� ��������
    void SetReady();

private:

    void GPIOS_Init();

    void SystemClock_Config();
};


extern Hardware hardware;
