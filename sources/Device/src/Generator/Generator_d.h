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

    static void SetOffset(Chan::E ch, DoubleValue offset);

    static void SetFrequency(Chan::E ch, DoubleValue frequency);

    static void SetAmplitude(Chan::E ch, DoubleValue amplitude);

    static void SetDuration(Chan::E ch, DoubleValue duration);

    static void SetDutyRatio(Chan::E ch, DoubleValue dutyRatio);

    static void SetPhase(Chan::E ch, DoubleValue phase);

    static void SetDelay(Chan::E ch, DoubleValue duration);

    static void SetManipulationDuration(Chan::E ch, DoubleValue duration);

    static void SetManipulationPeriod(Chan::E ch, DoubleValue period);

    static void SetPacketPeriod(Chan::E ch, DoubleValue duration);

    static void SetPacketNumber(Chan::E ch, DoubleValue number);

    static void SetPeriod(Chan::E ch, DoubleValue period);
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
    } value;

    explicit Attenuation(Attenuation::E v) : value(v) { }
    float Units() const;
    pString Name() const;
};


class Amplifier
{
public:
    
    static void Init();
    
    // ��������� ��������� � ������������ � �������� �����������
    static void Tune(Chan::E ch);
    
    // ���������� ����������� �������� � ����� ����� ������, ������� ���������� � ���������. ��������� ��� �������� 10 ���, �� ������ 10 �� ����� ��������� �� 3.16
    static double GetAmplification(Chan::E ch);
    
    // ������������� ������������
    static void Block()   { isBlocked = true; };
    
    // �������������� ������������
    static void Unblock() { isBlocked = false; };
    
    // ���������� true, ���� �� ������ ������ ������� ���������
    static bool IsEnabled(Chan::E ch) { return isEnabled[ch]; }

private:
    
    // ��������/��������� ���������� ��������� ���������
    static void Enable(Chan::E ch, bool enable);

    static void SetAttenuation(Chan::E ch, Attenuation::E attenuation);

    static Attenuation::E attenuation[Chan::Count];
    
    // ������������� � true �������� ��������, ��� ��������� ������������ - ������� �������� � Tune() ���������� �� �����
    static bool isBlocked;
    
    // true, ���� ��������� ��������������� ������ �������
    static bool isEnabled[Chan::Count];
};


struct SettingsGenerator
{
    friend class DGenerator;
public:
    // ���������� ������������� �� ������ ���������. ��������� ������������ ��� ����� ����������
    static double Amplitude(Chan::E ch) { return amplitude[ch].ToDouble();  }
    // ���������� ������������� �� ������ ��������
    static double Offset(Chan::E ch)    { return offset[ch].ToDouble();     }
    // ���������� ������������� ������� �� ������
    static double Frequency(Chan::E ch) { return frequency[ch].ToDouble();  }
    // ���������� true, ���� �� ������ ch ����������� �������������� ����� �������
    static bool FormIsSine(Chan::E ch) { return waveIsSine[ch]; }
private:
    // true, ���� �� ������ ����������� ����� ������� "���������"
    static bool waveIsSine[Chan::Count];
    // ������� ������������� ��������� �� ������
    static DoubleValue amplitude[Chan::Count];
    // ������� ������������� �������� �� ������
    static DoubleValue offset[Chan::Count];
    // ������� ������� �� ������
    static DoubleValue frequency[Chan::Count];
};
