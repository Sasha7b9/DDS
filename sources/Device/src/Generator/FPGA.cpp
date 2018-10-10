#include "FPGA.h"
#include "defines.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Utils/Math.h"
#include "Generator/Generator.h"
#include "Utils/Console.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_VALUE ((1 << 14) - 1)
#define MIN_VALUE (0)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FPGA::ModeWork          FPGA::modeWork[Chan::Number] = { FPGA::ModeWork::None, FPGA::ModeWork::None };;
uint8                   FPGA::dataDDS[Chan::Number][FPGA_NUM_POINTS * 2];
float                   FPGA::amplitude[Chan::Number] = {10.0f, 10.0f};
float                   FPGA::offset[Chan::Number] = {5.0f, 5.0f};
FPGA::ClockFrequency    FPGA::clock = FPGA::ClockFrequency::_100MHz;
uint64                  FPGA::registers[FPGA::RG::Number] = {0};
StartMode               FPGA::startMode[Chan::Number] = {StartMode::Auto, StartMode::Auto};
float                   FPGA::PacketImpulse::periodImpulse = 0.0f;
float                   FPGA::PacketImpulse::durationImpulse = 0.0f;


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

    Multiplexor::Init();
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
        SetSineMode,            ///< ����� ���������� ����� ����������� �����������
        EmptyFunc,
        EmptyFunc,
        SetMeanderMode,
        SetImpulseMode,
        SetPackedImpulseMode
    };
    
    func[form.value].func(ch);
    
    Multiplexor::SetMode(ch, form);

    WriteControlRegister();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::EmptyFunc(Chan)
{
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
void FPGA::SetSineMode(Chan ch)
{
    modeWork[ch] = ModeWork::Sine;

    WriteControlRegister();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetPackedImpulseMode(Chan)
{
    modeWork[Chan::A] = ModeWork::PackedImpulse;
    WriteControlRegister();

    uint64 data = (16383 << 14) + 8191;

    WriteRegister(RG::_3_RectA, data);

    SetPolarity(Chan::A, 0);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetPolarity(Chan ch, uint8 polarity)
{
    uint64 data = (8191 << 14) + 16383;     // ������������� ����������

    if(polarity == 1)
    {
        data = (16383 << 14) + 8191;        // ������������� ����������
    }

    static const RG regs[Chan::Number] = {RG::_3_RectA, RG::_4_RectB};

    WriteRegister(regs[ch], data);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetImpulseMode(Chan ch)
{
    modeWork[ch] = ModeWork::Impulse;
    WriteControlRegister();

    SetPolarity(ch, 0);         // ������������� ������������� ����������
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
void FPGA::SetDurationImpulse(Chan ch, float duration)
{
    PacketImpulse::durationImpulse = duration;
    uint64 value = (uint64)(duration / 10e-9f);
    RG reg = ch.IsA() ? RG::_6_DurationImpulseA : RG::_8_DurationImpulseB;
    if(ch.IsA() && modeWork[Chan::A].Is(ModeWork::PackedImpulse))
    {
        reg = RG::_8_DurationImpulseB;
    }
    WriteRegister(reg, value);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::PacketImpulse::SetPeriodPacket(float period)
{
    uint64 n = (uint64)(period / 10e-9f);
    WriteRegister(RG::_5_PeriodImpulseA, n - 2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::PacketImpulse::SetNumberImpules(uint value)
{
    uint64 n = (uint64)(((value - 1) * periodImpulse + durationImpulse) / 10e-9f);

    WriteRegister(RG::_6_DurationImpulseA, n);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetPeriodImpulse(Chan ch, float period)
{
    // ��� ��������� � ���������� ���������� ������� ������ ������� �����. ������� ��������� �������� ������� ���������, ����� ������������ ���
    // � �������� ������ ��� �������������
    PacketImpulse::periodImpulse = period;
    uint64 value = (uint64)(period / 10e-9f);
    RG reg = ch.IsA() ? RG::_5_PeriodImpulseA : RG::_7_PeriodImpulseB;
    if(ch.IsA() && modeWork[Chan::A].Is(ModeWork::PackedImpulse))
    {
        reg = RG::_7_PeriodImpulseB;
    }
    WriteRegister(reg, value);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetStartMode(Chan ch, StartMode mode)
{
    startMode[ch] = mode;
    WriteControlRegister();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::WriteControlRegister()
{
    uint16 data = BINARY_U16(00000000, 01111000);       // ���� 3, 4, 5, 6 ������������� � ��������� ���������. �� �������� ��������� - �������

    SetBit(data, RG0::_0_WriteData);                    // � ������� ���� 0 ���������� ������ ��� ������ ������ � ������

    if(modeWork[Chan::A].Is(ModeWork::Sine) && AD9952::Manipulation::IsEnabled(Chan::A))
    {
        switch(AD9952::Manipulation::GetType(Chan::A))
        {
            case AD9952::Manipulation::Type::OSK:
                ClearBit(data, RG0::_3_ManipulationOSK2);
                break;
            case AD9952::Manipulation::Type::FPGA:
                ClearBit(data, RG0::_4_ManipulationFPGA1);
                break;
        }
    }

    if (modeWork[Chan::B].Is(ModeWork::Sine) && AD9952::Manipulation::IsEnabled(Chan::B))
    {
        switch (AD9952::Manipulation::GetType(Chan::B))
        {
            case AD9952::Manipulation::Type::OSK:
                ClearBit(data, RG0::_5_ManipulationOSK1);
                break;
            case AD9952::Manipulation::Type::FPGA:
                ClearBit(data, RG0::_6_ManipulationFPGA2);
                break;
        }
    }

    switch(modeWork[Chan::A])
    {
        case ModeWork::Meander:     
            SetBit(data, RG0::_8_MeanderA);
        case ModeWork::Rectangle:
        case ModeWork::Impulse:
        case ModeWork::PackedImpulse:
            SetBit(data, RG0::_1_ImpulseA);
            break;
    }

    switch(modeWork[Chan::B])
    {
        case ModeWork::Meander:   
            SetBit(data, RG0::_9_MeanderB);
        case ModeWork::Rectangle:
        case ModeWork::Impulse:
            SetBit(data, RG0::_2_ImpulseB);
            break;
    }

    if(FPGA::clock == FPGA::ClockFrequency::_1MHz)
    {
        SetBit(data, RG0::_7_Freq_MHz);
    }

    if(modeWork[Chan::A] == ModeWork::PackedImpulse)
    {
        SetBit(data, RG0::_12_HandStartPacket);
    }

    data = SetBitsStartMode(data);

    WriteRegister(RG::_0_Control, data);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint16 FPGA::SetBitsStartMode(uint16 data)
{
    ModeWork mode = modeWork[Chan::A];
    StartMode start = startMode[Chan::A];

    if(mode.Is(ModeWork::Impulse) || mode.Is(ModeWork::PackedImpulse))
    {
        if(start.Is(StartMode::Single))
        {
            SetBit(data, RG0::_10_HandStartA);
        }
    }

    if(mode.Is(ModeWork::DDS))
    {
        if(start.Is(StartMode::ComparatorA))
        {
            SetBit(data, RG0::_13_StartMode0);
        }
        else if(start.Is(StartMode::ShaperB))
        {
            SetBit(data, RG0::_14_StartMode1);
        }
        else if(start.Is(StartMode::Single))
        {
            SetBit(data, RG0::_13_StartMode0);
            SetBit(data, RG0::_14_StartMode1);
        }
    }

    mode = modeWork[Chan::B];
    start = startMode[Chan::B];

    if(mode.Is(ModeWork::Impulse) || mode.Is(ModeWork::PackedImpulse))
    {
        if(start.Is(StartMode::Single))
        {
            SetBit(data, RG0::_11_HandStartB);
        }
    }

    if (mode.Is(ModeWork::DDS))
    {
        if (start.Is(StartMode::ComparatorA))
        {
            SetBit(data, RG0::_13_StartMode0);
        }
        else if (start.Is(StartMode::ShaperB))
        {
            SetBit(data, RG0::_14_StartMode1);
        }
        else if (start.Is(StartMode::Single))
        {
            SetBit(data, RG0::_13_StartMode0);
            SetBit(data, RG0::_14_StartMode1);
        }
    }

    return data;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool FPGA::Start()
{
    if(startMode[Chan::A] != StartMode::Auto || startMode[Chan::B] != StartMode::Auto)
    {
        WriteRegister(RG::_11_Start, 2);
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FPGA::SetModeDDS(Chan ch)
{
    modeWork[ch] = ModeWork::DDS;
    Multiplexor::SetMode(ch, Form::Meander);
    SendData();
    WriteControlRegister();
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
    static const struct StructBits
    {
        int value;
        StructBits(int v) : value(v) {};
    }
    numBits[RG::Number] =
    {
        16, // _0_Control,
        40, // _1_Freq,
        20, // _2_Amplitude,
        28, // _3_RectA,
        28, // _4_RectB,
        32, // _5_PeriodImpulseA,
        32, // _6_DurationImpulseA,
        32, // _7_PeriodImpulseB,
        32, // _8_DurationImpulseB,
        13, // _9_FreqMeter
        28, // _10_Offset
        2   // _11_Start
    };

    registers[reg] = value;

    WriteAddress(reg);

    for(int i = 0; i < 2; i++)
    {
        for (int bit = numBits[reg].value - 1; bit >= 0; bit--)
        {
            CPU::WritePin(GeneratorWritePin::FPGA_DT_RG, GetBit(value, bit) == 1);  // ������������� ��� ���������� ��������������� ���
            CPU::WritePin(GeneratorWritePin::FPGA_CLK_RG, true);                    // � ���������� ��� � ����
            CPU::WritePin(GeneratorWritePin::FPGA_CLK_RG, false);
        }
    }

    CPU::WritePin(GeneratorWritePin::FPGA_WR_RG, true);                         // ������ ������������ ������ �� ����������� �������� � FPGA
    CPU::WritePin(GeneratorWritePin::FPGA_WR_RG, false);
    Timer::PauseOnTime(10);                                                     // ��� 10 �����������, ���� ������ ����������� � FPGA
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint8 *FPGA::DataDDS(Chan ch)
{
    return &dataDDS[ch][0];
}
