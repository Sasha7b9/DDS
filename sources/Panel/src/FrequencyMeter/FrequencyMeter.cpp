#include "FrequencyMeter.h"
#include "Display/Text.h"
#include "Display/Painter.h"
#include "Settings/Settings.h"
#include "Utils/StringUtils.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint FrequencyMeter::frequency = 0;
bool FrequencyMeter::inactive = true;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FrequencyMeter::Draw()
{
    if (!FREQ_ENABLED)
    {
        return;
    }

    Painter::SetColor(inactive ? Color::BLUE_50 : Color::FILL);

    char buffer[20];

    if(FREQ_MEASURE_IS_FREQ)
    {
        Text::DrawFormatText(8, SCREEN_HEIGHT - 16, "F = %s ���", UInt2StringThisPoint(frequency, buffer, 8, (int)FREQ_BILLING_TIME));
    }
    else
    {
        static const struct StrOut
        {
            int forFract;
            const char * const suffix;
        } strs[5][5] =
        {
            {{0, "��"}, {1, "��"}, {2, "��"}, {0, "���"}, {1, "���"}},
            {{1, "��"}, {2, "��"}, {3, "��"}, {1, "���"}, {2, "���"}},
            {{2, "��"}, {3, "��"}, {4, "��"}, {2, "���"}, {3, "���"}},
            {{3, "��"}, {4, "��"}, {5, "��"}, {3, "���"}, {4, "���"}},
            {{4, "��"}, {5, "��"}, {6, "��"}, {4, "���"}, {5, "���"}}
        };

        StrOut str = strs[FREQ_AVE_PERIOD][FREQ_TIME_STAMPS];

        Text::DrawFormatText(8, SCREEN_HEIGHT - 16, "T = %s %s", UInt2StringThisPoint(frequency, buffer, 9, str.forFract), str.suffix);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyMeter::SetMeasure(uint value)
{
    if(value == MAX_UINT)
    {
        return;
    }
    frequency = value;
    inactive = false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FrequencyMeter::SetInactive()
{
    inactive = true;
}
