#pragma once
#include "defines.h"


class FrequencyMeter
{
public:
    static void Draw();
    /// ���������� ��������� �������� �������
    static void SetMeasure(uint value);

private:

    static uint frequency;
};
