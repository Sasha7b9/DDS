#include "defines.h"
#include "Generator.h"
#include "Log.h"
#include "Menu/MenuItems.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "FrequencyMeter/FrequencyMeter.h"
#include "Settings/Settings.h"
#include "Display/Console.h"
#include "Signals.h"
#include "Command.h"
#include "structs.h"
#include "Signals.h"
#include "Display/Console.h"
#include "Utils/Math.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Generator::EnableChannel(Chan ch, bool enable)
{
    uint8 buffer[3] = {CommandPanel::EnableChannel, (uint8)ch, (uint8)(enable ? 1 : 0)};
    SendToInterface(buffer, 3);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::LoadStartMode(Chan ch, int mode)
{
    uint8 buffer[3] = {CommandPanel::SetStartMode, (uint8)ch, (uint8)mode};
    SendToInterface(buffer, 3);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::LoadRegister(Register reg, uint64 value)
{
    INIT_BIT_SET_64(bitSet, value);

    uint8 buffer[10] = {CommandPanel::WriteRegister, (uint8)reg,   bitSet.byte0, bitSet.byte1, bitSet.byte2, bitSet.byte3,
                                                                    bitSet.byte4, bitSet.byte5, bitSet.byte6, bitSet.byte7};
    SendToInterface(buffer, 10);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::EmptyCommand()
{
    uint8 buffer[10] = {CommandPanel::None};
    SendToInterface(buffer, 10);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetDebugMode(bool enable)
{
    uint8 buffer[2] = {CommandPanel::ModeDebug, (uint8)(enable ? 1 : 0)};
    SendToInterface(buffer, 2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::Reset()
{
    uint8 command = CommandPanel::RunReset;
    SendToInterface(&command, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetFormWave(Wave *w)
{
    Chan ch = w->GetChannel();
    uint8 form = (uint8)FORM(ch)->value;

    if(form == Form::Sine || form == Form::Impulse || form == Form::Meander || form == Form::PacketImpuls)
    {
        uint8 buffer[3] = {CommandPanel::SetFormWave, ch, form};
        SendToInterface(buffer, 3);
    }
    else
    {
        SetFormDDS(FORM(ch));
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetFormDDS(Form *form)
{
    Chan ch = form->GetWave()->GetChannel();

    switch (form->value)
    {
        uint8 buffer[FPGA_NUM_POINTS * 2];
        float data[FPGA_NUM_POINTS];

        case Form::RampPlus:
            {
                float step = 2.0f / FPGA_NUM_POINTS;

                for(int i = 0; i < FPGA_NUM_POINTS; i++)
                {
                    data[i] = 1.0f - step * i;
                }

                TransformDataToCode(data, buffer);

                LoadPointsToDDS(ch, buffer);
            }
            break;
        case Form::RampMinus:
            break;
        case Form::Meander:
        case Form::Sine:
        case Form::Impulse:
        case Form::PacketImpuls:
        case Form::Number:
            break;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::TransformDataToCode(float d[FPGA_NUM_POINTS], uint8 code[FPGA_NUM_POINTS * 2])
{
    int max = 0x1fff;

    for (int i = 0; i < FPGA_NUM_POINTS; i++)
    {
        uint16 c = (uint16)(fabs(d[i]) * max);

        if (Sign(d[i]) == -1)
        {
            SetBit(c, 13);
        }

        code[i] = (uint8)c;
        code[i + FPGA_NUM_POINTS] = (uint8)(c >> 8);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::LoadPointsToDDS(Chan ch, uint8 points[FPGA_NUM_POINTS * 2])
{
    /*
    uint8 data = {CommandPanel::LoadFormDDS, ch};

    SendToInterface(data, 2);

    SendToInterface(points, FPGA_NUM_POINTS * 2);
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::Update()
{
    static uint timePrev = 0;

    if(TIME_MS - timePrev > 100)
    {
        ProcessDataFPGA();

        timePrev = TIME_MS;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetParameter(ParameterChoice *param)
{
    static const struct StructCommand
    {
        CommandPanel command;
        StructCommand(CommandPanel::E c) : command(c) {};
    }
    commands[ParameterChoice::Number] =
    {
        CommandPanel::SetPolarity,
        CommandPanel::SetStartMode,
        CommandPanel::SetManipulationMode,
        CommandPanel::SetManipulation
    };

    if(param->value == ParameterChoice::ManipulationEnabled)
    {
        LOG_WRITE("modulation %d", (uint8)param->GetChoice());
    }

    uint8 buffer[3] = {(uint8)commands[param->value].command, (uint8)param->GetForm()->GetWave()->GetChannel(), (uint8)param->GetChoice()};

    SendToInterface(buffer, 3);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetParameter(ParameterValue *param)
{
    static const struct StructCommand
    {
        CommandPanel command;
        StructCommand(CommandPanel::E c) : command(c) {};
    }
    commands[ParameterValue::Number] =
    {
        CommandPanel::SetFrequency,
        CommandPanel::SetPeriod,
        CommandPanel::SetAmplitude,
        CommandPanel::SetOffset,
        CommandPanel::SetDuration,
        CommandPanel::SetDutyRatio,
        CommandPanel::SetPhase,
        CommandPanel::SetDelay,
        CommandPanel::SetDurationRise,
        CommandPanel::SetDurationFall,
        CommandPanel::SetDurationStady,
        CommandPanel::SetDutyFactor,
        CommandPanel::SetManipulationDuration,
        CommandPanel::SetManipulationPeriod,
        CommandPanel::SetPacketPeriod,
        CommandPanel::SetPacketNumber,
        CommandPanel::None
    };

    uint8 buffer[6] = {(uint8)commands[param->value].command, (uint8)param->GetForm()->GetWave()->GetChannel()};

    float value = param->GetValue();

    if(param->Is(ParameterValue::Offset))
    {
        value -= 5.0f;
    }

    memcpy(&buffer[2], &value, 4);
    SendToInterface(buffer, 6);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SendToInterface(uint8 *buffer, uint16 size)
{
    CPU::SPI4_::Transmit((uint8 *)&size, 2);

    uint8 *pointer = buffer;
    while(size > 0)
    {
        uint16 sizeChunk = (size > 1024u) ? 1024u : size; // ������ ����� ��� ��������

        size -= sizeChunk;

        CPU::SPI4_::Transmit(pointer, sizeChunk);

        pointer += sizeChunk;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::ProcessDataFPGA()
{
    uint8 command = CommandPanel::RequestData;

    SendToInterface(&command, 1);

    uint16 numBytes = 0;

    CPU::SPI4_::Receive((uint8 *)&numBytes, 2);

    if(numBytes)  // �������� �������� �������� ����� ����, ������� ��� �������� ��������������� �����������
    {
        ReceiveAndRun(numBytes);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::ReceiveAndRun(uint16 numBytes)
{
    uint8 *buffer = (uint8 *)malloc(numBytes);

    if (buffer)
    {
        CPU::SPI4_::Receive(buffer, numBytes);

        if (buffer[0] == CommandGenerator::FreqMeasure)
        {
            BitSet32 bs;
            for (int i = 0; i < 4; i++)
            {
                bs.byte[i] = buffer[i + 1];
            }
            FrequencyMeter::SetMeasure(bs.word);
        }
        else if (buffer[0] == CommandGenerator::Log)
        {
            char buf[LENGTH_SPI_BUFFER];
            for (int i = 0; i < LENGTH_SPI_BUFFER - 1; i++)
            {
                buf[i] = (char)buffer[i + 1];
            }
            buf[LENGTH_SPI_BUFFER - 1] = '\0';
            Console::AddString(buf);
        }
    }

    free(buffer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::TuneChannel(Chan ch)
{
    EnableChannel(ch, CHANNEL_ENABLED(ch));

    FORM(ch)->TuneGenerator(ch);
}
