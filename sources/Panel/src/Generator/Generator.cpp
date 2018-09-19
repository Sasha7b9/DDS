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

#include <math.h>
#include <string.h>
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Generator::enabledCh[Chan::Number] = {true, true};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Generator::EnableChannel(Chan ch, bool enable)
{
    enabledCh[ch] = enable;
    uint8 buffer[3] = {CommandPanel::EnableChannel, (uint8)ch, (uint8)(enable ? 1 : 0)};
    SendToInterface(buffer, 3);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Generator::ChannelEnabled(Chan ch)
{
    return enabledCh[ch];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::LoadRegister(Register reg, uint64 value)
{
    INIT_BIT_SET_64(bitSet, value);

    uint8 buffer[10] = {CommandPanel::WRITE_REGISTER, (uint8)reg,   bitSet.byte0, bitSet.byte1, bitSet.byte2, bitSet.byte3,
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
    uint8 buffer[2] = {CommandPanel::MODE_DEBUG, (uint8)(enable ? 1 : 0)};
    SendToInterface(buffer, 2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::Reset()
{
    uint8 command = CommandPanel::RUN_RESET;
    SendToInterface(&command, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetFormWave(Chan ch, Form form)
{
    uint8 buffer[3] = {CommandPanel::SetFormWave, (uint8)ch, (uint8)form.value};
    SendToInterface(buffer, 3);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::Update()
{
    static uint timePrev = 0;

    if(TIME_MS - timePrev > 100)
    {
        uint8 trans[LENGTH_SPI_BUFFER] = {0};

        SendToInterface(trans, LENGTH_SPI_BUFFER);

        timePrev = TIME_MS;
    }}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::ExecuteCommand(uint8 *buffer, int)
{
    if(buffer[0] == CommandGenerator::COM_FREQ_MEASURE)
    {
        BitSet32 data;
        for(int i = 0; i < 4; i++)
        {
            data.byte[i] = buffer[i + 1];
        }
        FrequencyMeter::SetMeasure(data.word);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetParameter(Chan ch, Parameter param, float value)
{
    static const CommandPanel commands[Parameter::Number] =
    {
        CommandPanel::SetFrequency,
        CommandPanel::None,
        CommandPanel::SetAmplitude,
        CommandPanel::SetOffset,
        CommandPanel::SetDuration,
        CommandPanel::SetDutyRatio,
        CommandPanel::SetPhase,
        CommandPanel::SET_DELAY,
        CommandPanel::SET_DEPTH_MODULATION,
        CommandPanel::SET_POLARITY,
        CommandPanel::SET_DURATION_RISE,
        CommandPanel::SET_DURATION_FALL,
        CommandPanel::SET_DURATION_STADY,
        CommandPanel::SET_DUTY_FACTOR,
        CommandPanel::SetRampForSine,
        CommandPanel::SetRampSineDuration,
        CommandPanel::SetRampSineAmplitude,
        CommandPanel::SetPacketPeriod,
        CommandPanel::SetPacketNumber,
        CommandPanel::None
    };

    uint8 buffer[6] = {(uint8)commands[param.value], (uint8)ch};

    if(param.Is(Parameter::Offset))
    {
        value -= 5.0f;
    }

    memcpy(&buffer[2], &value, 4);
    SendToInterface(buffer, 6);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SendToInterface(uint8 *data, int size)
{
    /*
        �������� ��������.
        �������� ��������� � ������.
        � ������, ���� � ���������� ��� ������ ��� ��������, �� ���������� �������� ����������.
        � ������ ������� ���������� ��� �������� �� ������� �.
    */
 
    static uint8 trans[LENGTH_SPI_BUFFER];          // ��� ������ ��� ������������ ������
    static uint8 recv[LENGTH_SPI_BUFFER];         // ��� ������, ���� ����������� ������ ������

    memcpy(trans, data, (uint)size);

#ifndef OPEN
    CPU::SPI4_::TransmitReceive(trans, recv, LENGTH_SPI_BUFFER, 100);
#endif
    
    if(recv[0] == CommandGenerator::COM_FREQ_MEASURE)
    {
        BitSet32 bs;
        for(int i = 0; i < 4; i++)
        {
            bs.byte[i] = recv[i + 1];
        }
        FrequencyMeter::SetMeasure(bs.word);
    }
    else if(recv[0] == CommandGenerator::COM_LOG)
    {
        char buf[10];
        for(int i = 0; i < 9; i++)
        {
            buf[i] = (char)recv[i + 1];
        }
        buf[9] = '\0';
        Console::AddString(buf);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::TuneChannel(Chan ch)
{
    EnableChannel(ch, CHANNEL_ENABLED(ch));

    FORM(ch)->TuneGenerator(ch);
}
