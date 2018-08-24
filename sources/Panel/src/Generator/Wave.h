#pragma once
#include "defines.h"
#include "Settings/Settings.h"


class Wave
{
public:
    pString Name(uint num, Language lang);
    /// ���������� ������� ����� ������� �� ������ ������
    //static WaveForm GetForm(Chan ch = (Chan::E)CURRENT_CHANNEL);
    /// ������������� ������ ������� �� ������ �����
    static void SetForm(Chan ch, WaveForm form);
};
