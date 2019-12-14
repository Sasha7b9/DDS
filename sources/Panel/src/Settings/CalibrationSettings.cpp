#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "structs.h"
#include "CalibrationSettings.h"
#include "Hardware/HAL/HAL.h"
#endif



static const CalibrationSettings defSet =
{
    0,              // ��� �������� �� ������ ��������� (-1), ����� ��������� ��� ���������� ������� �������� � EEPROM-������
    {4095, 4095},   // AD9952 -5�
    {2048, 2048},   // AD9952 0�
    {0,    0},      // AD9952 +5�
    {0,    0},      // AD9952 ������
    {0,    0},      // DDS MAX
    {0,    0},      // DDS MIN
    {2048, 2048},      // DDS OFFSET
    0               // FREQ TRIG LEV
};

CalibrationSettings setCal = defSet;


void CalibrationSettings::Load()
{
    *this = defSet;                     // ������� ��������� ���������� �� ��������� - ����� ���������� �������� ����
    HAL_EEPROM::LoadSettings(this);

    for (int ch = 0; ch < Chan::Count; ch++)
    {
        for (int k = 0; k < KoeffCal::Count; k++)
        {
            Message::Calibrate(static_cast<uint8>(ch), static_cast<uint8>(k)).Transmit();
        }
    }
}


void CalibrationSettings::Save()
{
    HAL_EEPROM::SaveSettings(this);
}


CalibrationSettings &CalibrationSettings::operator =(const CalibrationSettings &rhs)
{
    std::memcpy(this, rhs.unused, sizeof(*this));

    return *this;
}
