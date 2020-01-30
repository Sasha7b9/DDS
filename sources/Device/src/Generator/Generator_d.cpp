#include "defines.h"
#include "log.h"
#include "Generator/Generator_d.h"
#include "FreqMeter/FreqMeter_d.h"
#include <cmath>


bool SettingsGenerator::waveIsSine[Chan::Count] = { true, true };
float SettingsGenerator::amplitude[Chan::Count] = { 10.0F, 10.0F };
float SettingsGenerator::frequency[Chan::Count] = { 1e3F, 1e3F };
float SettingsGenerator::offset[Chan::Count] = { 0.0F, 0.0F };
Attenuation::E Amplifier::attenuation[Chan::Count] = { Attenuation::_0Db, Attenuation::_0Db };
bool Amplifier::isBlocked = false;


struct Filtr
{
    static void Init()
    {
        HAL_PIO::Init(HPort::_E, HPin::_12, HMode::Output_PP, HPull::No); //-V525
        HAL_PIO::Init(HPort::_E, HPin::_13, HMode::Output_PP, HPull::No);
        HAL_PIO::Init(HPort::_E, HPin::_14, HMode::Output_PP, HPull::No);

        HAL_PIO::Init(HPort::_F, HPin::_4, HMode::Output_PP, HPull::No);
    }

    static void Tune(Chan::E ch, TypeForm::E form)
    {
        if (form == TypeForm::Sine)
        {
            SetType(ch, Type::Chebyshev);
        }
        else if(form == TypeForm::Impulse || form == TypeForm::PacketImpuls || form == TypeForm::Meander)
        {
            SetType(ch, Type::None);
        }
        else
        {
            SetType(ch, Type::Bessel);
        }
    }

private:

    struct Type
    {
        enum E
        {
            None,
            Chebyshev,
            Bessel,
            Count
        };
    };

    static void SetType(Chan::E ch, Type::E type)
    {
        /*  +-----------+---------+---------+
            |           | ����� � | ����� B |
            +-----------+----+----+----+----+
            |           |PE12|PE14|PE13|PF4 |
            |  ������   | p1 | p3 | p2 | p8 |
            +-----------+----+----+----+----+
            | �����     | X    1  | X    1  |
            +-----------+---------+---------+
            | �������   |         |         |
            | �����     | 0    0  | 0    0  |
            | ������    |         |         |
            +-----------+---------+---------+
            | ��������� | 1    0  | 1    0  |
            +-----------+---------+---------+
        */

        static const HPort::E gpio0[Chan::Count] = { HPort::_E, HPort::_E };
        static const HPort::E gpio1[Chan::Count] = { HPort::_E, HPort::_F };

        static const uint16 pin0[Chan::Count] = { HPin::_12, HPin::_13 };
        static const uint16 pin1[Chan::Count] = { HPin::_14, HPin::_4 };
        
        //                                                   ���         �������      �������
        static const HState::E state0[Type::Count] = { HState::Reset, HState::Set, HState::Set   };
        static const HState::E state1[Type::Count] = { HState::Reset, HState::Set, HState::Reset };

        HAL_PIO::Write(gpio0[ch], pin0[ch], state0[type]);
        HAL_PIO::Write(gpio1[ch], pin1[ch], state1[type]);
    }
};


void DGenerator::Init()
{
    EnableChannel(Chan::A, false);
    EnableChannel(Chan::B, false);
    AD9952::Init();
    AD5697::Init();
    FPGA::Init();
    DFreqMeter::Init();
    Amplifier::Init();
    Filtr::Init();
}


void DGenerator::EnableChannel(Chan::E ch, bool enable)
{
    if(!FPGA::Start())
    {
        StructPIN pins[Chan::Count] = { {WR_OUT_A}, {WR_OUT_B} };

        HAL_PIO::Write(pins[ch].port, pins[ch].pin, enable);
    }
}



void DGenerator::SetFormWave(Chan::E ch, TypeForm::E form)
{
    Filtr::Tune(ch, form);

    if(ch < Chan::Count && form < TypeForm::Count)
    {
        SettingsGenerator::waveIsSine[ch] = (form == TypeForm::Sine);

        FPGA::SetWaveForm(ch, form);
    }
}


void DGenerator::SetFrequency(Chan::E ch, FloatValue freq)
{
    SettingsGenerator::frequency[ch] = freq.ToFloat();

    if (SettingsGenerator::waveIsSine[ch])
    {
        AD9952::SetFrequency(ch);
    }
    else
    {
        FPGA::SetFrequency(ch);
    }
}


void DGenerator::SetManipulationPeriod(Chan::E ch, FloatValue period)
{
    FPGA::SetPolarity(ch, 0);
    FPGA::SetPeriodImpulse(ch, period);
}


void DGenerator::SetManipulationDuration(Chan::E ch, FloatValue duration)
{
    FPGA::SetPolarity(ch, 0);
    FPGA::SetDurationImpulse(ch, duration);
}


void DGenerator::SetPeriod(Chan::E ch, FloatValue period)
{
    FPGA::SetPeriodImpulse(ch, period);
}


void DGenerator::SetAmplitude(Chan::E ch, FloatValue ampl)
{
    SettingsGenerator::amplitude[ch] = ampl.ToFloat();

    Amplifier::Tune(ch);

    if (SettingsGenerator::waveIsSine[ch])
    {
        AD9952::SetAmplitude(ch);
    }
    else
    {
        FPGA::SetAmplitude();
    }
}


void DGenerator::SetOffset(Chan::E ch, FloatValue off)
{
    SettingsGenerator::offset[ch] = off.ToFloat();

    Amplifier::Tune(ch);

    AD5697::SetOffset(ch);
}


void DGenerator::SetPhase(Chan::E ch, FloatValue phase)
{
    AD9952::SetPhase(ch, phase);
}


void DGenerator::SetPacketNumber(Chan::E, FloatValue number)
{
    FPGA::PacketImpulse::SetNumberImpules(static_cast<uint>(number.ToFloat() + 0.5F));
}


void DGenerator::SetPacketPeriod(Chan::E, FloatValue period)
{
    FPGA::PacketImpulse::SetPeriodPacket(period);
}


void DGenerator::SetDutyRatio(Chan::E, FloatValue)
{

}


void DGenerator::SetDuration(Chan::E ch, FloatValue value)
{
    FPGA::SetDurationImpulse(ch, value);
}


void DGenerator::SetDelay(Chan::E, FloatValue)
{
}


void Amplifier::SetAttenuation(Chan::E ch, Attenuation::E att)
{
    static const HPort::E gpio0[Chan::Count] = { HPort::_E, HPort::_F };
    static const HPort::E gpio1[Chan::Count] = { HPort::_B, HPort::_C };

    static const uint16 pin0[Chan::Count] = { HPin::_15, HPin::_5 };
    static const uint16 pin1[Chan::Count] = { HPin::_5,  HPin::_13 };

    static const HState::E state0[Attenuation::Count] =
    {
        HState::Reset,
        HState::Set,
        HState::Reset,
        HState::Set
    };

    static const HState::E state1[Attenuation::Count] =
    {
        HState::Reset,
        HState::Reset,
        HState::Set,
        HState::Set
    };

    HAL_PIO::Write(gpio0[ch], pin0[ch], state0[att]);
    HAL_PIO::Write(gpio1[ch], pin1[ch], state1[att]);

    attenuation[ch] = att;
}


void Amplifier::Init()
{
    HAL_PIO::Init(HPort::_E, HPin::_15, HMode::Output_PP, HPull::No); //-V525

    HAL_PIO::Init(HPort::_B, HPin::_10, HMode::Output_PP, HPull::No);

    HAL_PIO::Init(HPort::_F, HPin::_0, HMode::Output_PP, HPull::No);
    HAL_PIO::Init(HPort::_F, HPin::_5, HMode::Output_PP, HPull::No);

    HAL_PIO::Init(HPort::_C, HPin::_13, HMode::Output_PP, HPull::No);
    HAL_PIO::Init(HPort::_C, HPin::_14, HMode::Output_PP, HPull::No);
}


void Amplifier::Tune(Chan::E ch)
{
    if(isBlocked)
    {
        return;
    }

    float amplitude = SettingsGenerator::Amplitude(ch);

    if(amplitude > 3.16F)              // 1 ��������
    {
        SetAttenuation(ch, Attenuation::_0Db);
    }
    else if(amplitude > 1.0F)          // 2 ��������
    {
        SetAttenuation(ch, Attenuation::_10Db);
    }
    else if(amplitude > 0.316F)        // 3,4 ���������
    {
        if(SettingsGenerator::Offset(ch) > 2.5F)
        {
            SetAttenuation(ch, Attenuation::_20Db);
        }
        else
        {
            SetAttenuation(ch, Attenuation::_0Db);
        }
    }
    else if(amplitude > 0.100F)        // 5 ��������
    {
        SetAttenuation(ch, Attenuation::_10Db);
    }
    else if(amplitude > 0.0316F)        // 6 ��������
    {
        SetAttenuation(ch, Attenuation::_20Db);
    }
    else                                // 7 ��������
    {
        SetAttenuation(ch, Attenuation::_30Db);
    }

    Enable(ch, attenuation[ch] < Attenuation::_20Db);
}


void Amplifier::Enable(Chan::E ch, bool enable)
{
    static const HPort::E gpio[Chan::Count] = { HPort::_F, HPort::_C };
    static const uint16   pin[Chan::Count] =  { HPin::_0,  HPin::_14 };

    HAL_PIO::Write(gpio[ch], pin[ch], enable);
}


float Amplifier::GetAttenuation(Chan::E ch)
{
    static const float att[Attenuation::Count] =
    {
        std::powf(10, 0.05F * 0),
        std::powf(10, 0.05F * 10),
        std::powf(10, 0.05F * 20),
        std::powf(10, 0.05F * 30)
    };

    return att[attenuation[ch]];
}
