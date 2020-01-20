#pragma once
#include "common/CommonTypes.h"



/// ������������������ �������� ������ - �� �������� � ��������  ��� �� �������� � ��������
struct TransmissionSequence
{
    enum E
    {
        MSB_2_LSB,          ///< �� �������� ���� � ��������
        LSB_2_MSB           ///< �� �������� ���� � ��������
    } value;
    TransmissionSequence(E v) : value(v) {};
};

struct TypeWave
{
    enum E
    {
        Sin,
        Cos
    } value;
    TypeWave(E v) : value(v) {};
};
