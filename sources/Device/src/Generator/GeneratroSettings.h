#pragma once
#include "defines.h"


struct SettingsAD9952
{
    float       frequency;                      ///< �������
};


struct SettingsGenerator
{
    SettingsAD9952 ad9952[2];
};

extern SettingsGenerator setDDS;
