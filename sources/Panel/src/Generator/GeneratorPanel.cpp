#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "GeneratorPanel.h"
#include "Log.h"
#include "Message.h"
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
#include "Utils/Debug.h"
#include <cmath>
#include <string.h>
#include <cstdlib>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int FPGA_NUM_POINTS = 8 * 1024;
/// ��������� ����� ������������� �������
static void LoadFormDDS(Form *form);
/// ����������� ������, ���������� � ������������� �������� [-1.0f;1.0f] � ������, ���������� � ������ ����, ��������� ��� �������� � ����
static void TransformDataToCode(float data[FPGA_NUM_POINTS], Message *message);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Generator::EnableChannel(Chan::E ch, bool enable)
{
    MessageEnableChannel((uint8)ch, (uint8)(enable ? 1U : 0U)).Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::LoadStartMode(Chan::E ch, int mode)
{
    Message(3, Command::SetStartMode, (uint8)ch, (uint8)mode).Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::LoadRegister(Register::E reg, uint64 value)
{
    Message(10, Command::WriteRegister, (uint8)reg, value).Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetDebugMode(bool enable)
{
    Message(2, Command::ModeDebug, (uint8)(enable ? 1u : 0u)).Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::Reset()
{
    Message(1, Command::RunReset).Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetFormWave(Wave *w)
{
    Chan::E ch = w->GetChannel();
    uint8 form = (uint8)FORM(ch)->value;

    if(FORM(ch)->IsDDS())
    {
        LoadFormDDS(FORM(ch));
    }

    Message(3, Command::SetFormWave, (uint8)ch, form).Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetFormWave(Chan::E ch, Form::E form)
{
    /// \todo �����, ��������, ������������ ��������� ����� ������� - ��� ����� ��� ��������� ������������ �����?

    Message(3, Command::SetFormWave, (uint8)ch, (uint8)form).Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void LoadFormDDS(Form *form)
{
    Chan::E ch = form->GetWave()->GetChannel();

    float data[FPGA_NUM_POINTS];

    Message message(FPGA_NUM_POINTS * 2 + 2, Command::LoadFormDDS, (uint8)ch);

    switch (form->value)
    {
        case Form::RampPlus:
            {
                float step = 2.0f / FPGA_NUM_POINTS;

                for(int i = 0; i < FPGA_NUM_POINTS; i++)
                {
                    data[i] = -1.0f + step * i;
                }

                TransformDataToCode(data, &message);
            }
            break;
        case Form::RampMinus:
            {
                float step = 2.0f / FPGA_NUM_POINTS;

                for (int i = 0; i < FPGA_NUM_POINTS; i++)
                {
                    data[i] = 1.0f - step * i;
                }

                TransformDataToCode(data, &message);
            }
            break;
        case Form::Triangle:
            {
                float step = 2.0f / (FPGA_NUM_POINTS / 2);

                for (int i = 0; i < FPGA_NUM_POINTS / 2; i++)
                {
                    data[i] = - 1.0f + step * i;
                }

                for(int i = FPGA_NUM_POINTS / 2; i < FPGA_NUM_POINTS; i++)
                {
                    data[i] = 1.0f - step * (i - FPGA_NUM_POINTS / 2);
                }

                TransformDataToCode(data, &message);
            }
            break;
        case Form::Meander:
        case Form::Sine:
        case Form::Impulse:
        case Form::PacketImpuls:
        case Form::DDS:
        case Form::Number:
            break;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TransformDataToCode(float d[FPGA_NUM_POINTS], Message *message)
{
    uint8 code[FPGA_NUM_POINTS * 2];

    int max = 0x1fff;

    for (int i = 0; i < FPGA_NUM_POINTS; i++)
    {
        uint16 c = (uint16)(std::fabs(d[i]) * max);

        if (Sign(d[i]) == -1)
        {
            SetBit(c, 13);
        }

        code[i] = (uint8)c;
        code[i + FPGA_NUM_POINTS] = (uint8)(c >> 8);
    }

    message->PutData(code, FPGA_NUM_POINTS * 2);

    message->Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetParameter(ParameterChoice *param)
{
    DEF_STRUCT(StructCommand, Command::E) commands[ParameterChoice::Number] =
    {
        Command::SetPolarity,
        Command::SetStartMode,
        Command::SetManipulationMode,
        Command::SetManipulation
    };

    Message message(3, (uint8)commands[param->value].val,
        (uint8)param->GetForm()->GetWave()->GetChannel(),
        (uint8)param->GetChoice());

    message.Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetOffset(Chan::E ch, float offset)
{
    /// \todo �������� - ������ ��������� �� ���� ����
    Message(10, Command::SetOffset, (uint8)ch, ParamValue(offset).ToUINT64()).Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetAmplitude(Chan::E ch, float amplitude)
{
    /// \todo �������� - ������ ��������� �� ���� ����
    Message(10, Command::SetAmplitude, (uint8)ch, ParamValue(amplitude).ToUINT64()).Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetFrequency(Chan::E ch, float frequency)
{
    /// \todo �������� - ������ ��������� �� ���� ����
    Message(10, Command::SetFrequency, (uint8)ch, ParamValue(frequency).ToUINT64()).Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::SetParameter(ParameterValue *param)
{
    DEF_STRUCT(StructCommand, Command::E) commands[ParameterValue::Number] =
    {
        Command::SetFrequency,
        Command::SetPeriod,                     // 
        Command::SetAmplitude,
        Command::SetOffset,
        Command::SetDuration,                   // 
        Command::SetDutyRatio,
        Command::SetPhase,
        Command::SetDelay,
        Command::SetDurationRise,
        Command::SetDurationFall,
        Command::SetDurationStady,
        Command::SetDutyFactor,
        Command::SetManipulationDuration,
        Command::SetManipulationPeriod,
        Command::SetPacketPeriod,
        Command::SetPacketNumber,
        Command::RequestData
    };

    ParamValue value = param->GetValueNano();

    if (param->Is(ParameterValue::Offset))
    {
        value.Add(-5.0f);
    }

    Chan::E ch = param->GetForm()->GetWave()->GetChannel();

    Command com = commands[param->value].val;

    Message(10, com, (uint8)ch, value.ToUINT64()).Transmit();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::TuneChannel(Chan::E ch)
{
    EnableChannel(ch, CHANNEL_ENABLED(ch));

    FORM(ch)->TuneGenerator(ch);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Generator::LoadSettings()
{
    Generator::TuneChannel(Chan::A);
    Generator::TuneChannel(Chan::B);
}
