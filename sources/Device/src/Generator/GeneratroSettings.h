#pragma once
#include "defines.h"
#include "GeneratorSettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SettingsAD9952
{
    TransmissionSequence transmissionSequence;  ///< D8 ����������� �������� ���
    bool        bidirectionalMode;              ///< D9 ���� true, �� �������� � ��������������� ������
    TypeWave    typeWave;                       ///< D12 ����� ������ ��� ��������
    
    float       frequency;                      ///< �������
    float       amplitude;
    float       offset;
};


struct SettingsGenerator
{
    SettingsAD9952 ad9952[2];
};

extern SettingsGenerator setDDS;
