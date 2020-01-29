#pragma once
#include "AD9952.h"
#include "AD5697.h"
#include "FPGA.h"
#include "common/Command.h"


class DGenerator
{
public:
    static const int DDS_NUM_POINTS = 8 * 1024;

    static void Init();

    static void EnableChannel(Chan::E ch, bool enable);

    static void SetFormWave(Chan::E ch, TypeForm::E form);

    static void SetOffset(Chan::E ch, FloatValue offset);

    static void SetFrequency(Chan::E ch, FloatValue frequency);

    static void SetAmplitude(Chan::E ch, FloatValue amplitude);

    static void SetDuration(Chan::E ch, FloatValue duration);

    static void SetDutyRatio(Chan::E ch, FloatValue dutyRatio);

    static void SetPhase(Chan::E ch, FloatValue phase);

    static void SetDelay(Chan::E ch, FloatValue duration);

    static void SetManipulationDuration(Chan::E ch, FloatValue duration);

    static void SetManipulationPeriod(Chan::E ch, FloatValue period);

    static void SetPacketPeriod(Chan::E ch, FloatValue duration);

    static void SetPacketNumber(Chan::E ch, FloatValue number);

    static void SetPeriod(Chan::E ch, FloatValue period);
};


struct Attenuation
{
    enum E
    {
        _0Db,
        _10Db,
        _20Db,
        _30Db,
        Count
    }value;

    Attenuation(E v) : value(v) { };

    float Multiplier() const;
};


class Amplifier
{
public:
    static void Init();
    /// ��������� ��������� � ������������ � �������� �����������
    static void Tune(Chan::E ch);
    /// ���������� ������������� ����������� ���������� �� ������
    static Attenuation GetAttenuation(Chan::E ch);

private:
    /// ��������/��������� ���������� ��������� ���������
    static void Enable(Chan::E ch, bool enable);

    static void SetAttenuation(Chan::E ch, Attenuation::E attenuation);

    static Attenuation::E attenuation[Chan::Count];
};


struct SetGenerator
{
    friend class DGenerator;
public:
    /// ���������� ������������� �� ������ ���������. ��������� ������������ ��� ����� ����������
    static float Amplitude(Chan::E ch)
    {
        return amplitude[ch];
    }
    /// ���������� ������������� �� ������ ��������
    static float Offset(Chan::E ch)
    {
        return offset[ch];
    }
    /// ���������� ������������� ������� �� ������
    static float Frequency(Chan::E ch)
    {
        return frequency[ch];
    }
    /// ���������� true, ���� �� ������ ch ����������� �������������� ����� �������
    static bool FormIsSine(Chan::E ch)
    {
        return waveIsSine[ch];
    }
private:
    /// true, ���� �� ������ ����������� ����� ������� "���������"
    static bool waveIsSine[Chan::Count];
    /// ������� ������������� ��������� �� ������
    static float amplitude[Chan::Count];
    /// ������� ������������� �������� �� ������
    static float offset[Chan::Count];
    /// ������� ������� �� ������
    static float frequency[Chan::Count];
};
