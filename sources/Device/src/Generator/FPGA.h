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

    static void SetWaveForm(Chan ch, Form form);

    static void SetFrequency(Chan ch, float frequency);

    static void SetAmplitude(Chan ch, float amplitude);

    static void SetOffset(Chan ch, float offset);

    static void SetDurationImpulse(Chan ch, float duration);

    static void SetPeriodImpulse(Chan ch, float period);

    static void SetPolarity(Chan ch, uint8 polarity);

    static void SetStartMode(Chan ch, StartMode mode);
    /// ������ ����������� ������. ���������� true � ������ ������ (���� ����������� ��������������� ���������)
    static bool Start();

    class PacketImpulse
    {
    public:
        /// ������������� ����� ��������� � �����
        static void SetNumberImpules(uint n);
        /// ������������� ������ ���������� �����
        static void SetPeriodPacket(float period);

        static float periodImpulse;

        static float durationImpulse;
    };

    struct ModeWork
    {
        enum E
        {
            None,
            DDS,
            Impulse,        ///< �����, � ������� ������c� ����� ����� ������ �������
            Impulse2,       ///< �����, � ������� �������� ����� ���������� �������. ��� ���� ����� ������������ �������� ������� ������ ���. �������
            Rectangle,
            Meander,
            Manipulation,   ///< ����� ����������� �����������
            PackedImpulse,  ///< ������ ���������
            Number
        } value;
        ModeWork(E v) : value(v) {};
        operator uint8() const { return(uint8)value; };
        bool Is(ModeWork mode) { return mode.value == value; };
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
            _11_Start,
            _12_Multiplexor,    ///< ���������� ���������������� ��� ���������� ������� �����������
            Number
        } value;
        RG(E v) : value(v) { };
        operator uint8() const { return (uint8)value; };
    };

    struct RG0
    {
        enum E
        {
            _0_WriteData,           ///< � ���� ��� ���������� 0, ����� ��������� ������ ������� � ����
            _1_ImpulseA,            ///< 1, ���� � ������ � ���� ��������� ��������/�������������
            _2_ImpulseB,            ///< 1, ���� � ������ B ���� ��������� ��������/�������������
            _3_ManipulationNoOSK1,  ///< ����� 1, ���� ����������� ������ � ��������� ��� �� �������� OSK1 (�����)
            _4_ManipulationNoFPGA1, ///< ����� 1, ���� ����������� ������ � ��������� ��� �� �������� ������������� ���������
            _5_ManipulationNoOSK2,  ///< ����� 1, ���� ����������� ������ � ��������� ��� �� �������� OSK2 (�����)
            _6_ManipulationNoFPGA2, ///< ����� 1, ���� ����������� ������ � ��������� ��� �� �������� ������������� ���������
            _7_Freq_MHz,            ///< 1, ���� �������� ������� 1���
            _8_MeanderA,            ///< 1, ���� ������ �� ������ A
            _9_MeanderB,            ///< 1, ���� ������ �� ������ B
            _10_HandStartA,         ///< ���� ��� ���������� � 1, �� ������ ����� �������
            _11_HandStartB,
            _12_HandStartPacket,    ///< 1, ���� ������� �������� ����� ���������
            _13_StartMode0,         ///< ������� ��� ���������� ������� �������
            _14_StartMode1          ///< ������� ��� ���������� ������� �������
        };
    };

    static void SetManipulationMode(Chan ch);

    static void SetRampPlusMode(Chan ch);

    static void SetRampMinusMode(Chan ch);

    static void SetMeanderMode(Chan ch);

    static void SetImpulseMode(Chan ch);

    static void SetPackedImpulseMode(Chan ch);

    static void CreateEnable();
    /// ������� ������������ ����� � ����
    static void SendData();
    /// �������� ���� � ����
    static void WriteByte(uint8 byte);
    /// �������� �������� � �������
    static void WriteRegister(uint8 reg, uint64 value);
    /// ���������� �� A0_RG...A3_RG �����, ������������� ��������
    static void WriteAddress(uint8 reg);
    /// ������ ������������ ��������
    static void WriteControlRegister();
    /// ����������� ������, ���������� � ������������� �������� [-1.0f;1.0f] � ������, ���������� � ������ ����, ��������� ��� �������� � ����
    static void TransformDataToCode(float data[FPGA_NUM_POINTS], uint8 code[FPGA_NUM_POINTS * 2]);

    static uint8 RegisterForDuration(Chan ch);
    /// ����������� �������� � ������ ���, ��������� ��� ������ � �������
    static uint OffsetToCode(float offset);
    /// ���������� ����, ��������������� ������ �������
    static uint16 SetBitsStartMode(uint16 data);
    /// ����� �������
    static StartMode startMode[Chan::Number];
    /// ����� ������ ����
    static ModeWork modeWork[Chan::Number];
    /// \brief ����� �������� ��������, ��������������� ��������������� ��� ������� � ����. ������� ���� ������� 8 ���, � ����� ������� 6 ���
    /// ������ ������ ���� �������� � ������ ���� - 0 � ������� ������� ���������� ������������� �����, � 1 - �������������
    static uint8 dataDDS[Chan::Number][FPGA_NUM_POINTS * 2];

    static float amplitude[Chan::Number];

    static float offset[Chan::Number];
    /// ����� �������� ���������� � �������� ��������
    static uint64 registers[RG::Number];
};
