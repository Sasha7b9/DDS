#pragma once
#include "common/Common.h"
#include "common/CommonTypes.h"


struct Calibrator
{
    // ������������� ����������� ����������, ������������ ������������ ������������ ��� ����� ������������ ���������
    static void SetK(uint8 channel, uint8 signal, uint8 range, uint8 param, int16 k);
    /// ���������� ����������� ���������� ���������
    static float GetAmplitudeK(Chan::E ch, TypeForm::E form, float amplitude);

private:
    static uint8 CalculateRange(float amplitude);
    /// ������������� ����� ������� ��� �������������� ����� �������
    static void SetFormWave(Chan::E ch, uint8 signal);
    /// ���������� ��������� ��� ��������� ���������
    static void SetAmplitude(Chan::E ch, uint8 range);
    /// ���������� �������� ��� ��������� ���������
    static void SetOffset(Chan::E ch, uint8 param);
};
