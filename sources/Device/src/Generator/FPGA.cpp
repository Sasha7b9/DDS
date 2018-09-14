#include "FPGA.h"
#include "defines.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Utils/Math.h"
#include "Generator/Generator.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_VALUE ((1 << 14) - 1)
#define MIN_VALUE (0)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FPGA::ModeWork              FPGA::modeWork[Chan::Number] = { FPGA::ModeWork::None, FPGA::ModeWork::None };;
uint8                       FPGA::dataDDS[Chan::Number][FPGA_NUM_POINTS * 2];
float                       FPGA::amplitude[Chan::Number] = {10.0f, 10.0f};
float                       FPGA::offset[Chan::Number] = {5.0f, 5.0f};
FPGA::ClockFrequency        FPGA::clock = FPGA::ClockFrequency::_100MHz;
uint64                      FPGA::registers[FPGA::RG::Number] = {0};
FPGA::SourceManipulation    FPGA::sourceManipulation[Chan::Number] = {FPGA::SourceManipulation::None, FPGA::SourceManipulation::None};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FPGA::Init()
{
    // ����������� ������ ��� ������ � �������� ����

    CPU::WritePin(GeneratorWritePin::FPGA_WR_RG, false);
    CPU::WritePin(GeneratorWritePin::FPGA_CLK_RG, false);
    CPU::WritePin(GeneratorWritePin::FPGA_DT_RG, false);
    CPU::WritePin(GeneratorWritePin::FPGA_A0_RG, false);
    CPU::WritePin(GeneratorWritePin::FPGA_A1_RG, false);
    CPU::WritePin(GeneratorWritePin::FPGA_A2_RG, false);
    CPU::WritePin(GeneratorWritePin::FPGA_A3_RG, false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetWaveForm(Chan ch, Form form)
{
    struct StructFunc
    {
        typedef void(*pFuncFpgaVU8)(Chan);
        pFuncFpgaVU8 func;
        StructFunc(pFuncFpgaVU8 f) : func(f) {};
    };
    
    static const StructFunc func[Form::Number] =
    {
        EmptyFunc,
        SetRampPlusMode,
        SetRampMinusMode,
        SetMeanderMode,
        SetImpulseMode,
        SetPackedImpulseMode
    };
    
    func[form.value].func(ch);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetMeanderMode(Chan ch)
{
    modeWork[ch] = ModeWork::Meander;
    WriteControlRegister();

    // �������� ������������ ������ ������� � ��������
    uint64 data = (16383 << 14) + 8191;

    RG regs[Chan::Number] = {RG::_3_RectA, RG::_4_RectB};

    WriteRegister(regs[ch], data);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetPackedImpulseMode(Chan)
{
    SetImpulseMode(Chan::A);
    SetImpulseMode(Chan::B);
    
    modeWork[Chan::A] = ModeWork::PackedImpulse;
    WriteControlRegister();

    PacketImpulse::SetNumberImpules(2);

    PacketImpulse::SetPeriodPacket(1e-3f);
    
    PacketImpulse::SetDurationImpulse(1e-6f);
    PacketImpulse::SetPeriodImpulse(1e-5f);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetImpulseMode(Chan ch)
{
    modeWork[ch] = ModeWork::Impulse;
    WriteControlRegister();

    uint64 data = (16383 << 14) + 8191;

    RG regs[Chan::Number] = {RG::_3_RectA, RG::_4_RectB};

    WriteRegister(regs[ch], data);

    // ��������� �������� �� ��������� ��� ������� � ������������.
    /// \todo �� ������ ������

    /*
    if(ch == Chan::A)
    {
        WriteRegister(RG::_3_RectA, (8191 << 14) + 16383);
        WriteRegister(RG::_5_PeriodImpulseA, (uint64)1e7);
        WriteRegister(RG::_6_DurationImpulseA, (uint64)1e6);
    }
    else
    {
        WriteRegister(RG::_4_RectB, (8191 << 14) + 16383);
        WriteRegister(RG::_7_PeriodImpulseB, (uint64)(1e-3f / 10e-9f));
        WriteRegister(RG::_8_DurationImpulseB, (uint64)(1e-4f / 10e-9f));
    }
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetFrequency(Chan ch, float frequency)
{
    WriteControlRegister();
    
    if(modeWork[ch] == ModeWork::Meander)
    {
        AD9952::SetFrequency(ch, frequency);
    }
    else if (modeWork[ch] == ModeWork::DDS)
    {
        uint64 N = (uint64)(frequency * 11e3f);
        WriteRegister(RG::_1_Freq, N);
    }
    else if(modeWork[ch] == ModeWork::Impulse || modeWork[ch] == ModeWork::Impulse2)
    {
        if (ch == Chan::B && ModeWork::Impulse2)
        {
            modeWork[ch] = ModeWork::Impulse;
            WriteControlRegister();
        }
        uint N = (uint)(1e8f / frequency + 0.5f);
        WriteRegister((uint8)(ch == Chan::A ? RG::_5_PeriodImpulseA : RG::_7_PeriodImpulseB), N);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetSourceManipulation(Chan ch, SourceManipulation source)
{
    modeWork[ch] = (source == SourceManipulation::None) ? ModeWork::None : ModeWork::Manipulation;

    sourceManipulation[ch] = source;

    WriteControlRegister();

    SetDurationImpulse(ch, 5e-6f);

    SetPeriodImpulse(ch, 10e-6f);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetDurationImpulse(Chan ch, float duration)
{
    uint64 value = (uint64)(duration / 10e-9f);
    RG reg = ch.IsA() ? RG::_6_DurationImpulseA : RG::_8_DurationImpulseB;
    WriteRegister(reg, value);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::PacketImpulse::SetPeriodPacket(float period)
{
    uint64 n = (uint64)(period / 10e-9f);
    WriteRegister(RG::_5_PeriodImpulseA, n - 2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::PacketImpulse::SetDurationImpulse(float duration)
{
    uint64 n = (uint64)(duration / 10e-9f);
    WriteRegister(RG::_8_DurationImpulseB, n - 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::PacketImpulse::SetNumberImpules(uint n)
{
    if(n < 2)
    {
        n = 2;
    }
    WriteRegister(RG::_6_DurationImpulseA, n - 2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::PacketImpulse::SetPeriodImpulse(float period)
{
    uint64 n = (uint64)(period / 10e-9f);
    WriteRegister(RG::_7_PeriodImpulseB, n - 2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetPeriodImpulse(Chan ch, float period)
{
    uint64 value = (uint64)(period / 10e-9f);
    RG reg = ch.IsA() ? RG::_5_PeriodImpulseA : RG::_7_PeriodImpulseB;
    WriteRegister(reg, value);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::WriteControlRegister()
{
    uint16 data = 0;

    SetBit(data, 0);                               // � ������� ���� 0 ���������� ������ ��� ������ ������ � ������

    switch(modeWork[Chan::A])
    {
        case ModeWork::Meander:     
            SetBit(data, 8);
        case ModeWork::Rectangle:
        case ModeWork::Impulse:
            SetBit(data, 1);
            break;
        case ModeWork::PackedImpulse:
            SetBit(data, 1);
            SetBit(data, 10);
            break;
    }

    switch(modeWork[Chan::B])
    {
        case ModeWork::Meander:   
            SetBit(data, 9);
        case ModeWork::Rectangle:
        case ModeWork::Impulse:
            SetBit(data, 2);
            break;
    }

    if(sourceManipulation[Chan::A] != SourceManipulation::None)
    {
        SetBit(data, 8);
    }

    if(sourceManipulation[Chan::B] != SourceManipulation::None)
    {
        SetBit(data, 9);
    }

    switch(sourceManipulation[Chan::A])
    {
        case SourceManipulation::ImpulseA: SetBit(data, 5);                  break;
        case SourceManipulation::ImpulseB: SetBit(data, 6);                  break;
        case SourceManipulation::None:     SetBit(data, 5); SetBit(data, 6); break;
    }

    switch(sourceManipulation[Chan::B])
    {
        case SourceManipulation::ImpulseA: SetBit(data, 3);                  break;
        case SourceManipulation::ImpulseB: SetBit(data, 4);                  break;
        case SourceManipulation::None:     SetBit(data, 3); SetBit(data, 4); break;
    }

    if(FPGA::clock == FPGA::ClockFrequency::_1MHz)
    {
        SetBit(data, 7);
    }


    WriteRegister(RG::_0_Control, data);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::EmptyFunc(Chan)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetRampPlusMode(Chan ch)
{
    modeWork[ch] = ModeWork::DDS;

    float step = 2.0f / FPGA_NUM_POINTS;

    float *data = (float *)malloc(FPGA_NUM_POINTS * 4);

    for (int i = 0; i < FPGA_NUM_POINTS; i++)
    {
        data[i] = -1.0f + step * i;
    }

    TransformDataToCode(data, dataDDS[ch]);

    free(data);

    SendData();

    WriteControlRegister();

    WriteRegister(RG::_1_Freq, (uint64)(200e3 * 11e3));
    WriteRegister(RG::_2_Amplitude, 0xfffff);
    WriteRegister(RG::_10_Offset, 0);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetRampMinusMode(Chan ch)
{
    modeWork[ch] = ModeWork::DDS;

    float step = 2.0f / FPGA_NUM_POINTS;

    float *d = (float *)malloc(FPGA_NUM_POINTS * 4);

    for (int i = 0; i < FPGA_NUM_POINTS; i++)
    {
        d[i] = 1.0f - step * i;
    }

    TransformDataToCode(d, dataDDS[ch]);

    free(d);

    SendData();

    WriteControlRegister();

    WriteRegister(RG::_1_Freq, (uint64)(200e3 * 11e3));
    WriteRegister(RG::_2_Amplitude, 0xfffff);
    WriteRegister(RG::_10_Offset, 0);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SendData()
{
    WriteRegister(RG::_0_Control, 0);
    
    uint8 *pointer = &dataDDS[0][0];

    for(int i = 0; i < FPGA_NUM_POINTS * 4; i++)
    {
        WriteByte(*pointer++);
        CPU::WritePin(GeneratorWritePin::FPGA_WR_DATA, true);
        for(int x = 0; x < 10; x++) { }
        CPU::WritePin(GeneratorWritePin::FPGA_WR_DATA, false);
    }

    WriteRegister(RG::_0_Control, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::WriteByte(uint8 byte)
{
    static const GeneratorWritePin pins[8] = 
    {
        GeneratorWritePin::D0,
        GeneratorWritePin::D1,
        GeneratorWritePin::D2,
        GeneratorWritePin::D3,
        GeneratorWritePin::D4,
        GeneratorWritePin::D5,
        GeneratorWritePin::D6,
        GeneratorWritePin::D7
    };

    for(int i = 0; i < 8; i++)
    {
        CPU::WritePin(pins[i], GetBit(byte, i) == 1);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::WriteRegister(uint8 reg, uint64 value)
{
    int numBits[Register::Number] =
    {
        16, // RG0_Control,
        40, // RG1_Freq,
        20, // RG2_Amplitude,
        28, // RG3_RectA,
        28, // RG4_RectB,
        32, // RG5_PeriodImpulseA,
        32, // RG6_DurationImpulseA,
        32, // RG7_PeriodImpulseB,
        32, // RG8_DurationImpulseB,
        13, // RG9_FreqMeter
        28  // RG10_Offset
    };

    registers[reg] = value;

    WriteAddress(reg);

    for (int bit = numBits[reg] - 1; bit >= 0; bit--)
    {
        CPU::WritePin(GeneratorWritePin::FPGA_DT_RG, GetBit(value, bit) == 1);  // ������������� ��� ���������� ��������������� ���
        CPU::WritePin(GeneratorWritePin::FPGA_CLK_RG, true);                    // � ���������� ��� � ����
        CPU::WritePin(GeneratorWritePin::FPGA_CLK_RG, false);
    }

    CPU::WritePin(GeneratorWritePin::FPGA_WR_RG, true);                         // ������ ������������ ������ �� ����������� �������� � FPGA
    CPU::WritePin(GeneratorWritePin::FPGA_WR_RG, false);
    Timer::PauseOnTime(10);                              // ��� 10 �����������, ���� ������ ����������� � FPGA
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::WriteAddress(uint8 reg)
{
    static const GeneratorWritePin pins[] = 
    {
        GeneratorWritePin::FPGA_A0_RG, 
        GeneratorWritePin::FPGA_A1_RG, 
        GeneratorWritePin::FPGA_A2_RG, 
        GeneratorWritePin::FPGA_A3_RG
    };

    for (int i = 0; i < 4; i++)
    {
        CPU::WritePin(pins[i], GetBit(reg, i) == 1);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint8 FPGA::RegisterForDuration(Chan ch)
{
    return ch == Chan::A ? (uint8)RG::_6_DurationImpulseA : (uint8)RG::_8_DurationImpulseB;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::TransformDataToCode(float d[FPGA_NUM_POINTS], uint8 code[FPGA_NUM_POINTS * 2])
{
    int max = 0x1fff;

    for(int i = 0; i < FPGA_NUM_POINTS; i++)
    {
        uint16 c = (uint16)(fabs(d[i]) * max);

        if(Sign(d[i]) == -1)
        {
            SetBit(c, 13);
        }

        code[i] = (uint8)c;
        code[i + FPGA_NUM_POINTS] = (uint8)(c >> 8);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint FPGA::OffsetToCode(float off)
{
    uint max = 0x1fff;

    int code = ~((int)(off / 5.0f * max)) + 1;

    return (uint)(code & 0x3fff);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetAmplitude(Chan ch, float ampl)
{
    amplitude[ch] = ampl;

    uint nA = (uint)(amplitude[Chan::A] * 1023 / 10);
    uint nB = (uint)(amplitude[Chan::B] * 1023 / 10);

    WriteRegister(RG::_2_Amplitude, nA + (nB << 10));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetOffset(Chan ch, float off)
{
    offset[ch] = off;

    uint nA = OffsetToCode(offset[Chan::A]);
    uint nB = OffsetToCode(offset[Chan::B]);
    
    WriteRegister(RG::_10_Offset, nA + (nB << 14));
}
