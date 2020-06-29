#include "defines.h"
#include "Generator/Calibrator.h"
#include "Generator/Generator_d.h"
#include "Settings/CalibrationSettings.h"


bool Calibrator::inModeCalibration = false;
uint8 Calibrator::range[Chan::Count] = { 255, 255 };
uint8 Calibrator::signal[Chan::Count] = { 0 , 0 };


void Calibrator::SetFormWave(Chan::E ch, uint8 sig)
{
    DGenerator::SetFormWave(ch, (sig == 0) ? TypeForm::Sine : TypeForm::Meander);

    DGenerator::SetFrequency(ch, Value(1e3F));
}


void Calibrator::SetOffset(Chan::E ch, uint8 param)
{
    static const float offset[4] =
    {
        0.0F,
        range[ch] < 3 ? 2.5F : 5.0F,
        0.0F,
        range[ch] < 3 ? -2.5F : -5.0F
    };

    AD5697::EnabledCalibrateMode(true);

    DGenerator::SetOffset(ch, Value(offset[param]));

    AD5697::EnabledCalibrateMode(false);
}


void Calibrator::SetK(uint8 channel, uint8 _signal, uint8 _range, uint8 param, int16 k)
{
    inModeCalibration = true;

    range[channel] = _range;

    signal[channel] = _signal;

    *setCal.GetK(channel, _signal, range[channel], param) = k;

    Chan::E ch = static_cast<Chan::E>(channel);

    SetFormWave(ch, _signal);

    if (param != 0)
    {
        Amplifier::TuneAndLock(ch, _range > 2, Attenuation::_0Db);
    }

    SetAmplitude(ch, param != 0);       // ��� ���������� �������� ����� ���������� ������� ������� �� ������, �� ���������� �� �������

    SetOffset(ch, param);

    if (param != 0)
    {
        Amplifier::Unlock();
    }

    inModeCalibration = false;
}


void Calibrator::SetAmplitude(Chan::E ch, bool zeroAmplitude)
{
    if (zeroAmplitude)
    {
        DGenerator::SetAmplitude(ch, Value("0"));
    }
    else
    {
        static const float amplitude[6] =
        {
            100e-3F,
            300e-3F,
            1.0F,
            3.0F,
            10.0F
        };

        DGenerator::SetAmplitude(ch, Value(amplitude[range[ch]]));
    }
}


uint8 Calibrator::CalculateRange(Chan::E ch)
{
    if(inModeCalibration)
    {
        return range[ch];
    }

    double amplitude = SettingsGenerator::Amplitude(ch);

    if(amplitude > Attenuation(Attenuation::_10Db).Units())
    {
        return 4;
    }
    else if(amplitude > 1.0F)
    {
        return 3;
    }
    else if(amplitude > Attenuation(Attenuation::_10Db).Units() / 10)
    {
        return 2;
    }
    else if(amplitude > 0.1F)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


float Calibrator::GetAmplitudeK(Chan::E ch)
{
    uint8 r = CalculateRange(ch);

    int16 k = *setCal.GetK(static_cast<uint8>(ch), SettingsGenerator::FormIsSine(ch) ? 0U : 1U, r, 0U);

    return 1.0F + k / 1e3F;
}


float Calibrator::GetOffsetK_Zero(Chan::E ch)
{
    uint8 r = CalculateRange(ch);

    return 2048.0F + *setCal.GetK(static_cast<uint8>(ch), SettingsGenerator::FormIsSine(ch) ? 0U : 1U, r, 2U);
}


double Calibrator::GetOffsetK_Negative(Chan::E ch)
{
    uint8 r = CalculateRange(ch);

    return 4095.0 - *setCal.GetK(static_cast<uint8>(ch), SettingsGenerator::FormIsSine(ch) ? 0U : 1U, r, 3U);
}


double Calibrator::GetOffsetK_Positive(Chan::E ch)
{
    uint8 r = CalculateRange(ch);

    return 0.0 - *setCal.GetK(static_cast<uint8>(ch), SettingsGenerator::FormIsSine(ch) ? 0U : 1U, r, 1U);
}


float Calibrator::GetFreqMeterK_Trig()
{
    return 0.0F;
}
