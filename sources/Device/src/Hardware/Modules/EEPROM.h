#pragma once
#include "Settings/CalibrationSettings.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EEPROM
{
public:

    static void SaveSettings(CalibrationSettings *settings);

    static void LoadSettings(CalibrationSettings *settings);

    static void SaveSignal(Chan::E ch, float *data);

    static float *GetSignal(Chan::E ch);
};
