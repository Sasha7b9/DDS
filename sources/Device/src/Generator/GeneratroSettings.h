#pragma once
#include "defines.h"


struct SettingsAD9952
{
    bool        bidirectionalMode;              ///< D9 ���� true, �� �������� � ��������������� ������
    float       frequency;                      ///< �������
    float       phase;
};


struct SettingsGenerator
{
    SettingsAD9952 ad9952[2];
};

extern SettingsGenerator setDDS;
