#pragma once
#include "defines.h"
#include "Command.h"
#include "GeneratorSettingsTypes.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FPGA_NUM_POINTS (1024 * 8)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FPGA
{
friend class Interface;
friend class Handlers;

public:
    static void Init();

    static void SetWaveForm(Chan::E ch, Form form);

    static void SetFrequency(Chan::E ch, ParamValue frequency);

    static void SetAmplitude(Chan::E ch, ParamValue amplitude);

    static void SetOffset(Chan::E ch, ParamValue offset);

    static void SetDurationImpulse(Chan::E ch, ParamValue duration);

    static void SetPeriodImpulse(Chan::E ch, ParamValue period);

    static void SetPolarity(Chan::E ch, uint8 polarity);

    static void SetStartMode(Chan::E ch, StartMode mode);
    /// ������ ����������� ������. ���������� true � ������ ������ (���� ����������� ��������������� ���������)
    static bool Start();

    class PacketImpulse
    {
    public:
        /// ������������� ����� ��������� � �����
        static void SetNumberImpules(uint n);
        /// ������������� ������ ���������� �����
        static void SetPeriodPacket(ParamValue period);

        static ParamValue periodImpulse;

        static ParamValue durationImpulse;
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
            PackedImpulse,  ///< ������ ���������
            Sine,
            Number
        } value;
        explicit ModeWork(E v) : value(v) {};
    };

    struct ClockFrequency
    {
        enum E
        {
            _100MHz,
            _1MHz
        } value;
        explicit ClockFrequency(E v) : value(v) {};
    };

    static ClockFrequency::E clock;

    static ModeWork::E CurrentMode(Chan::E ch) { return modeWork[ch]; }

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
            _3_ManipulationOSK2,    ///< ����� 0, ���� ����� ������ 1 ������ ���������������� �������� OSK2 ("�����" �� AD9952 ������� ������)
            _4_ManipulationFPGA1,   ///< ����� 0, ���� ����� ������ 1 ������ ���������������� �������������� ��������� ������ 1
            _5_ManipulationOSK1,    ///< ����� 0, ���� ����� ������ 2 ������ ���������������� �������� OSK1 ("�����" �� AD9952 ������� ������)
            _6_ManipulationFPGA2,   ///< ����� 0, ���� ����� ������ 2 ������ ���������������� �������������� ��������� ������ 2
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

    class Multiplexor
    {
        friend class Interface;
    public:

        /// �������������� �������������
        static void Init();
        /// �������������� ������������� � ������������ � ������ ���������������� ������� �� ������ ������
        static void SetMode(Chan::E ch, Form form);

        static Form GetMode(Chan ch);

    private:
        static void SetPin(uint16 pin);
        static void ResetPin(uint16 pin);

        static void WriteRegister(Register reg, uint value);

        static Form mode[Chan::Number];
    };

    static void SetModeSine(Chan::E ch);
    /// ���������� ����� ������������� ������� �� ������ ch
    static void SetModeDDS(Chan::E ch);
    /// ���������� ��������� �� ����� ������������� �������
    static uint8 *DataDDS(Chan::E ch);

    static void SetModeMeander(Chan::E ch);

    static void SetModeImpulse(Chan::E ch);

    static void SetModePackedImpulse(Chan::E ch);

    static void EmptyFunc(Chan ch);

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
    /// ���������� ����, ��������������� ������������� � ������������ ��������
    static void WriteMaxAmplitude(Chan::E ch);

    static uint8 RegisterForDuration(Chan ch);
    /// ����������� �������� � ������ ���, ��������� ��� ������ � �������
    static uint OffsetToCode(float offset);
    /// ���������� ����, ��������������� ������ �������
    static uint16 SetBitsStartMode(uint16 data);
    /// ����� �������
    static StartMode startMode[Chan::Number];
    /// ����� ������ ����
    static ModeWork::E modeWork[Chan::Number];
    /// \brief ����� �������� ��������, ��������������� ��������������� ��� ������� � ����. ������� ���� ������� 8 ���, � ����� ������� 6 ���
    /// ������ ������ ���� �������� � ������ ���� - 0 � ������� ������� ���������� ������������� �����, � 1 - �������������
    static uint8 dataDDS[Chan::Number][FPGA_NUM_POINTS * 2];

    static float amplitude[Chan::Number];

    static float offset[Chan::Number];
    /// ����� �������� ���������� � �������� ��������
    static uint64 registers[RG::Number];
};
