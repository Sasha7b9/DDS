#pragma once
#include "defines.h"


class FrequencyMeter
{
public:
    static void Draw();
    /// ���������� ��������� �������� �������
    static void SetMeasure(uint value);
    /// ���� ����� �������� ��� ����, ����� �������, ��� ��������� ���������� ���������.
    static void SetInactive();

private:

    static uint frequency;

    static bool inactive;
};
