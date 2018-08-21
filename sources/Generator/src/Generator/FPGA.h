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

    static void SetWaveForm(WaveForm form);

    static void SetFrequency(Chan ch, float frequency);

    static void SetDuration(Chan ch, float duration);

    static void SetDelay(float delay);

private:
    enum ModeWorkFPGA
    {
        ModeNone,
        ModeDDS,
        ModeImpulse,    ///< �����, � ������� ������c� ����� ����� ������ �������
        ModeImpulse2    ///< �����, � ������� �������� ����� ���������� �������. ��� ���� ����� ������������ �������� ������� ������ ���. �������
    };

    struct RG
    {
        enum
        {
            _0_Control,
            _1_Freq,
            _2_Mul,
            _3_RectA,
            _4_RectB,
            _5_PeriodImpulseA,
            _6_DurationImpulseA,
            _7_PeriodImpulseB,
            _8_DurationImpulseB,
            _9_FreqMeter,
            _10_Offset,
            Number
            /*
            Reg_Control,
            Reg_PeriodA,
            Reg_DurationA,
            Reg_PeriodB,
            Reg_DurationBandDelay,
            Reg_DurationB,
            Reg_Frequency
            */
        };
        uint8 value;
        RG(uint8 v) : value(v) { };
        operator uint8() const { return value; };
    };

    static void CreateSine();

    static void CreateCosine();

    static void CreateMeander();

    static void CreateRampPlus();

    static void CreateRampMinus();

    static void CreateTriangle();

    static void CreateTrapeze();

    //static void GenerateSaw();
    /// ���������� ���������� ����� ������
    static void CreateImpulse();

    static void CreateExponentePlus();

    static void CreateExponenteMinus();

    static void CreateNoise();

    static void CreateFree();

    /// ������� ������������ ����� � ����
    static void SendData();
    /// �������� �������� � �������
    static void WriteRegister(uint8 reg, uint value);
    /// ���������� �� A0_RG...A3_RG �����, ������������� ��������
    static void WriteAddress(uint8 reg);

    static void WriteControlRegister();

    static uint8 RegisterForDuration(Chan ch);

    static ModeWorkFPGA modeWork;

    static uint16 dataA[FPGA_NUM_POINTS];   ///< ����� ������� ��� ������� � ����
    static uint16 dataB[FPGA_NUM_POINTS];
};
