#pragma once
#include "defines.h"
#include "GeneratorSettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    TransmissionSequence transmissionSequence;      ///< D8 ����������� �������� ���
    bool        bidirectionalMode;                  ///< D9 ���� true, �� �������� � ��������������� ������
    TypeWave    typeWave;                           ///< D12 ����� ������ ��� ��������

    float       frequency;                          ///< �������
    float       amplitude;
    float       offset;
} SettingsAD9952;


typedef struct
{
    SettingsAD9952 ad9952[2];
} SettingsGenerator;

extern SettingsGenerator setDDS;
