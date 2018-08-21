#pragma once
#include "CommonTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������������������ �������� ������ - �� �������� � ��������  ��� �� �������� � ��������
struct TransmissionSequence
{
    enum
    {
        MSB_2_LSB,          ///< �� �������� ���� � ��������
        LSB_2_MSB           ///< �� �������� ���� � ��������
    };
    uint8 value;
    TransmissionSequence(uint8 v) : value(v)
    {
    };
};

struct TypeWave
{
    enum
    {
        Sin,
        Cos
    };
    uint8 value;
    TypeWave(uint8 v) : value(v)
    {
    };
};
