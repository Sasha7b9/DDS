#pragma once
#include "Command.h"
#include "CommonTypes.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CAL_AD9952_OFFSET_NEG(ch)   set.cal_AD9952_Offset_Negative[ch]
#define CAL_AD9952_OFFSET_POS(ch)   set.cal_AD9952_Offset_Positive[ch]
#define CAL_AD9952_OFFSET_ZERO(ch)  set.cal_AD9952_Offset_Zero[ch]
#define CAL_AD9952_AMPLITUDE(ch)    set.cal_AD9952_Amplitude[ch]
#define CAL_DDS_MAX(ch)             set.cal_DDS_MAX[ch]
#define CAL_DDS_MIN(ch)             set.cal_DDS_MIN[ch]


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CalibrationSettings
{
    const   uint marker;                                ///< �� ����� �������� ��������� �������� ����������, ��� ��� ����
    int16   cal_AD9952_Offset_Negative[Chan::Number];   ///< ������������� ����������� AD9952 �� -5�
    int16   cal_AD9952_Offset_Zero[Chan::Number];       ///< ������������� ����������� AD9952 �� 0�
    int16   cal_AD9952_Offset_Positive[Chan::Number];   ///< ������������� ����������� AD9952 �� +5�
    int16   cal_AD9952_Amplitude[Chan::Number];         ///< ������������� ����������� AD9952 �������
    int16   cal_DDS_MAX[Chan::Number];
    int16   cal_DDS_MIN[Chan::Number];
};


extern CalibrationSettings set;
