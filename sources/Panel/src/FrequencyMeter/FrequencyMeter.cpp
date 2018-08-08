#include "FrequencyMeter.h"
#include "Display/Text.h"
#include "Display/Painter.h"
#include "Settings/Settings.h"
#include "Utils/StringUtils.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint FrequencyMeter::frequency = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FrequencyMeter::Draw()
{
    if (!FREQ_ENABLED)
    {
        return;
    }

    Painter::SetColor(Color::FILL);

    char buffer[20];

    if(FREQ_MEASURE_IS_FREQ)
    {
        Text::DrawFormatText(8, SCREEN_HEIGHT - 16, "F = %s ���", UInt2StringThisPoint(frequency, buffer, 6, (int)FREQ_BILLING_TIME));
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
    frequency = value;
}
