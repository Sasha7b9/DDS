#include "Display/Text.h"
#include "Display/Painter.h"
#include "Settings/Settings.h"
#include "Utils/StringUtils.h"
#include "Utils/Math.h"
#include "Log.h"
#include <cstdio>


static uint valueFreq = 0;
static bool inactive = true;



void PFreqMeter::Draw()
{
    if (set.freq.measure == FreqMeasure::Disable)
    {
        return;
    }

    Text::SetUpperCase(false);

    if(inactive)
    {
        Color::BLUE_50.SetAsCurrent();
    }
    else
    {
        Color::FILL.SetAsCurrent();
    }

    char buffer[20];
    char text[50];

    if(set.freq.measure == FreqMeasure::Freq)
    {
        std::sprintf(text, (LANGUAGE ? "%skHz" : "%s���"), SU::UInt2StringThisPoint(valueFreq, buffer, 8, static_cast<int>(set.freq.billingTime)));
    }
    else
    {
        static const struct StrOut
        {
            int forFract;
            const char * suffix;
        }
        strs[5][5] =
        {
            {{0, "��"}, {1, "��"}, {2, "��"}, {0, "���"}, {1, "���"}},
            {{1, "��"}, {2, "��"}, {3, "��"}, {1, "���"}, {2, "���"}},
            {{2, "��"}, {3, "��"}, {4, "��"}, {2, "���"}, {3, "���"}},
            {{3, "��"}, {4, "��"}, {5, "��"}, {3, "���"}, {4, "���"}},
            {{4, "��"}, {5, "��"}, {6, "��"}, {4, "���"}, {5, "���"}}
        };

        StrOut str = strs[set.freq.avePeriod][set.freq.timeStamps];

        std::sprintf(text, "%s%s", SU::UInt2StringThisPoint(valueFreq, buffer, 9, str.forFract), str.suffix);
    }

    Text::DrawBigText(24, SIGNAL_HEIGHT + Page::Title::HEIGHT + 10, 3, text);

    Text::SetUpperCase(true);
}


void PFreqMeter::SetMeasure(uint value)
{
    if(value == MAX_UINT)
    {
        return;
    }
    valueFreq = value;
    inactive = false;
}


void PFreqMeter::SetInactive()
{
    inactive = true;
}


void PFreqMeter::LoadLevel()
{
    int max = 4 * 1024;

    float step = static_cast<float>(max) / 200.0F;

    int value = static_cast<int>(static_cast<float>(max / 2) + static_cast<float>(set.freq.level) * step);

    Math::Limitation(&value, 0, max - 1);

    PGenerator::LoadRegister(Register::FreqMeterLevel, static_cast<uint64>(value));
}


void PFreqMeter::LoadHysteresis()
{
    int max = 4 * 1024;

    float step = static_cast<float>(max) / 100.0F;

    int value = static_cast<int>(step * static_cast<float>(set.freq.hysteresis));

    Math::Limitation(&value, 0, max - 1);

    PGenerator::LoadRegister(Register::FreqMeterHYS, static_cast<uint64>(value));
}


void PFreqMeter::LoadSettings()
{
    LoadLevel();
    LoadHysteresis();
}
