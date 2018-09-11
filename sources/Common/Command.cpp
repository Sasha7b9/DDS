#include "Command.h"
#include "defines.h"
#include "Log.h"
#include "Settings/Settings.h"
#include <stdio.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct StructName
{
    pString nameRU;
    pString nameEN;
    StructName(pString nRU, pString nEN) : nameRU(nRU), nameEN(nEN) {};
}
nameParameter[Wave::Parameter::Number] =
{
    StructName("�������",        "FREQUENCY"),
    StructName("������",         "PERIOD"),
    StructName("������",         "AMPLITUDE"),
    StructName("��������",       "OFFSET"),
    StructName("����.",          "DURATION"),
    StructName("����������",     "DUTY RATIO"),
    StructName("����",           "PHASE"),
    StructName("��������",       "DELAY"),
    StructName("�����. ���.",    "MOD. INDEX"),
    StructName("����������",     "POLARITY"),
    StructName("��. ����������", "BUILD-UP TIME"),
    StructName("��. �����",      "RELEASING TIME"),
    StructName("��. ����",       "PEAK TIME"),
    StructName("�����. ������.", "DUTY FACTOR"),
    StructName("���������",      "Modulation")
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pString Wave::Form::Name(Language lang) const
{
    struct StrName
    {
        pString nameRu;
        pString nameEn;
        StrName(pString nRu, pString nEn) : nameRu(nRu), nameEn(nEn) { };
        pString Name(Language lang) { return lang == Language::RU ? nameRu : nameEn; }
    };

    static StrName names[Wave::Form::Number] =
    {
        StrName("�����",    "SINE"),
        StrName("����+",    "RAMP+"),
        StrName("����-",    "RAMP-"),
        StrName("������",   "MEANDER"),
        StrName("�������",  "IMPULSE")
    };

    return names[value].Name(lang);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString Register::Name() const
{
    struct StrName
    {
        pString name;
        StrName(pString n) : name(n) {};
    };

    static const StrName names[Register::Number] =
    {
        "������������� 1",
        "������������� 2",
        "5697 �������� 1",
        "5697 �������� 2",
        "5697 ���� �������",
        "5697 ���� ����������",
        "RG0 ����������",
        "RG1 �������",
        "RG2 ����������",
        "RG3 ������� �",
        "RG4 ������� B",
        "RG5 ������ ��������� �",
        "RG6 ����. ��������� �",
        "RG7 ������ ��������� B",
        "RG8 ����. ��������� B",
        "RG9 �����. �����������",
        "RG10 ��������",
        "������������� 3",
        "���������� - �������������",
        "���������� - �����",
        "���������� - ������"
    };

    return names[value].name;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const struct StructMinMax
{
    float min;
    float max;
    StructMinMax(float _min, float _max) : min(_min), max(_max) {};
}
minMax[Wave::Parameter::Number] =
{
    StructMinMax(1.0f,    50e6f),       // Frequency
    StructMinMax(2e-08f,  1.0f),        // Period
    StructMinMax(0.000f,  65535.0f),    // Amplitude
    StructMinMax(0.0f,    4095.0f),     // Offset
    StructMinMax(2e-08f,  10.0f),       // Duration
    StructMinMax(0.001f,  1.0f),        // DutyRatio
    StructMinMax(-180.0f, 180.0f),      // Phase
    StructMinMax(2e-08f,  10e08f),      // Delay
    StructMinMax(1e-3f,   10e6f),       // DepthModulation
    StructMinMax(-1,      1),           // Polarity
    StructMinMax(1e-6f,   1e6f),        // DurationRise
    StructMinMax(1e-6f,   1e6f),        // DurationFall
    StructMinMax(1e-6f,   1e6f),        // DurationStady
    StructMinMax(1e-6f,   1e6f),        // DutyFactor
    StructMinMax(-1.0f,   -1.0f)        // Modulation [-1.0f;1.0f] ��������, ��� ���� �������� ����� ��������� ���������� - ����� ��� ���������
                                        // �������� ��������� ����������
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Wave::Parameter::IsPage() const
{
    return MinValue() == -1.0f && MaxValue() == -1.0f;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float Wave::Parameter::MinValue() const
{
    return minMax[value].min;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float Wave::Parameter::MaxValue() const
{
    return minMax[value].max;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString Wave::Parameter::Name() const
{
    return LANG_RU ? (char *)nameParameter[value].nameRU : (char *)nameParameter[value].nameEN;
}
