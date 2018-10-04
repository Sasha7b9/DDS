#pragma once
#include "defines.h"
#include "Hardware/CPU.h"
#include "GeneratorSettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AD9952
{
public:

    static void Init();

    static void SetFrequency(Chan ch, float frequency);

    static void SetAmplitude(Chan ch, float amplitude);

    static void SetPhase(Chan ch, float phase);

    /// �����������
    class Manipulation
    {
    friend class AD9952;
    public:
        enum Type
        {
            OSK,    ///< ����������� ���������� �� ����������� ��������
            FPGA    ///< ����������� �������������� ����������
        };
        /// ����������/�������� ������������� ��������� �������� "����"
        static void SetEnabled(Chan ch, bool enable);
        static bool IsEnabled(Chan ch) { return enabled[ch]; };
        static void SetType(Chan ch, Type type);
        static Type GetType(Chan ch) { return type[ch]; };
    private:
        /// True ��������, ��� ����������� ��������
        static bool enabled[Chan::Number];
        static Type type[Chan::Number];
    };

private:
    struct Register
    {
        enum E
        {
            CFR1,
            CFR2,
            ASF,
            ARR,
            FTW0,
            POW
        } value;
        Register(E v) : value(v) { };
        operator uint8() const { return (uint8)value;  };
    };

    static void WriteToHardware(Chan ch, Register reg, uint value);
    static GeneratorWritePin ChipSelect(Chan ch);
    static void Reset();
    static void WriteRegister(Chan ch, Register reg);
    static void WriteCFR1(Chan ch);
    static void WriteCFR2(Chan ch);
    static void WriteARR(Chan ch);
    static void WriteASF(Chan ch);
    static void WriteFTW0(Chan ch);
    static void WritePOW(Chan ch);
};
