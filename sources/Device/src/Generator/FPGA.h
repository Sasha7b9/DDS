#pragma once
#include "Generator/Generator_d.h"
#include "Command.h"
#include "GeneratorSettingsTypes.h"




namespace FPGA
{
    static const uint NUM_POINTS = 1024 * 8;

    void Init();

    void SetWaveForm(Chan::E ch, Form::E form);

    void SetFrequency(Chan::E ch, ParamValue frequency);

    void SetAmplitude(Chan::E ch, ParamValue amplitude);

    void SetOffset(Chan::E ch, ParamValue offset);

    void SetDurationImpulse(Chan::E ch, ParamValue duration);

    void SetPeriodImpulse(Chan::E ch, ParamValue period);

    void SetPolarity(Chan::E ch, uint8 polarity);

    void SetStartMode(Chan::E ch, StartMode mode);
    /// ������ ����������� ������. ���������� true � ������ ������ (���� ����������� ��������������� ���������)
    bool Start();

    namespace PacketImpulse
    {
        /// ������������� ����� ��������� � �����
        void SetNumberImpules(uint n);
        /// ������������� ������ ���������� �����
        void SetPeriodPacket(ParamValue period);

        extern ParamValue periodImpulse;

        extern ParamValue durationImpulse;
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
            Count
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
            Count
        } value;
        explicit RG(E v) : value(v) { };
    };

    void SetClockAD992(ClockFrequency::E clock);

    extern ClockFrequency::E clock;
    /// ����� ������ ����
    extern ModeWork::E modeWork[Chan::Count];

    inline ModeWork::E CurrentMode(Chan::E ch) { return modeWork[ch]; }
    /// ���������� ��������� �� ����� �������, ������������ �� ������
    uint8 *DataFlash(Chan::E ch);
    /// ��������� ������ �������, ������������ � ������
    void SaveExtSignal(Chan::E ch, uint8 *data);
    /// ���������� ��������� �� ����� ������������� ������� (���������� �����������)
    uint8 *DataDDS(Chan::E ch);
    /// �������� �������� � �������
    void WriteRegister(RG::E reg, uint64 value);
};
