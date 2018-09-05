#pragma once
#include "defines.h"
#include "Command.h"
#include "GeneratorSettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FPGA_NUM_POINTS (1024 * 8)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FPGA
{
friend class Interface;

public:
    static void Init();

    static void SetWaveForm(Chan ch, Wave::Form form);

    static void SetFrequency(Chan ch, float frequency);

    static void SetAmplitude(Chan ch, float amplitude);

    static void SetOffset(Chan ch, float offset);

    struct ModeWork
    {
        enum E
        {
            None,
            DDS,
            Impulse,    ///< �����, � ������� ������c� ����� ����� ������ �������
            Impulse2,  ///< �����, � ������� �������� ����� ���������� �������. ��� ���� ����� ������������ �������� ������� ������ ���. �������
            Rectangle,
            Meander,
            Number
        } value;
        ModeWork(E v) : value(v) {};
        operator uint8() const { return(uint8)value; };
    };

    static struct ClockFrequency
    {
        enum E
        {
            _100MHz,
            _1MHz
        } value;
        ClockFrequency(E v) : value(v) {};
        operator uint8() const { return (uint8)value; };
    } clock;

private:

    ///< �������� ����
    struct RG
    {
        enum E
        {
            _0_Control,
            _1_Freq,
            _2_Amplitude,
            _3_RectA,           /// \brief ������� ���� ������� ������������� ����� ������ �. ������������ ��� ��������� ���� �����. 1-� ��� ������-
                                /// ���� ������ �������� �������������� ������� - ��������. 2-� ��� ������������� ������� �������� ������� - ��� ��
                                /// ���������.
                                /// b0...b13 - ������ ��������, b14...b27 - ������� ��������
            _4_RectB,           ///< ������ _3_RectA ��� ������ B
            _5_PeriodImpulseA,
            _6_DurationImpulseA,
            _7_PeriodImpulseB,
            _8_DurationImpulseB,
            _9_FreqMeter,
            _10_Offset,
            Number
        } value;
        RG(E v) : value(v) { };
        operator uint8() const { return (uint8)value; };
    };

    static void EmptyFunc(Chan ch);

    static void SetRampPlusMode(Chan ch);

    static void SetRampMinusMode(Chan ch);

    static void SetMeanderMode(Chan ch);

    static void SetImpulseMode(Chan ch);

    static void CreateEnable();
    /// ������� ������������ ����� � ����
    static void SendData();
    /// �������� ���� � ����
    static void WriteByte(uint8 byte);
    /// �������� �������� � �������
    static void WriteRegister(uint8 reg, uint64 value);
    /// ���������� �� A0_RG...A3_RG �����, ������������� ��������
    static void WriteAddress(uint8 reg);

    static void WriteControlRegister();
    /// ����������� ������, ���������� � ������������� �������� [-1.0f;1.0f] � ������, ���������� � ������ ����, ��������� ��� �������� � ����
    static void TransformDataToCode(float data[FPGA_NUM_POINTS], uint8 code[FPGA_NUM_POINTS * 2]);

    static uint8 RegisterForDuration(Chan ch);
    /// ����������� �������� � ������ ���, ��������� ��� ������ � �������
    static uint OffsetToCode(float offset);

    static ModeWork modeWork[Chan::Number];
    /// \brief ����� �������� ��������, ��������������� ��������������� ��� ������� � ����. ������� ���� ������� 8 ���, � ����� ������� 6 ���
    /// ������ ������ ���� �������� � ������ ���� - 0 � ������� ������� ���������� ������������� �����, � 1 - �������������
    static uint8 dataDDS[Chan::Number][FPGA_NUM_POINTS * 2];

    static float amplitude[Chan::Number];

    static float offset[Chan::Number];
    /// ����� �������� ���������� � �������� ��������
    static uint64 registers[RG::Number];
};
