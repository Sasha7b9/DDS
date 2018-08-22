#pragma once
#include "defines.h"

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4514)
#endif


/** @addtogroup Panel
 *  @{
 *  @addtogroup Interface
 *  @{
 */

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef COMMON_ENUM
#define COMMON_ENUM     \
    uint8 value; operator uint8() const { return value; }; operator uint8() { return value; }; bool Is(uint8 v) const { return v == value; }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    ��������� �������

1.  WRITE_SERVICE_COMMAND

    0                1        2
2.  SET_FORM_CHANNEL NUM_CHAN FormChannel

    0                     1        2                3...6
3.  SET_PARAMETER_CHANNEL NUM_CHAN ParameterChannel value

    0              1             2...5
12. WRITE_REGISTER NAME_REGISTER VALUE
*/

/// ��������� ������� ��� �������� � �������� ���������
struct CommandPanel
{
    enum ECommandPanel
    {
        COMMAND_NONE = 0,
        ENABLE_CHANNEL = 1,    ///< ��������/��������� �����
        SET_FORM_WAVE = 2,    ///< ���������� ����� �������
        SET_FREQUENCY = 3,    ///< ���������� �������
        SET_AMPLITUDE = 4,    ///< ���������� ���������
        SET_OFFSET = 5,    ///< ���������� ��������
        SET_DURATION = 6,
        SET_DUTYRATIO = 7,
        SET_PHASE = 8,
        RUN_RESET = 9,    ///< ����� ���������
        MODE_DEBUG = 10,   ///< ��������� ����������� ������ - ����� ���� ����������� ������� � FPGA
        SET_DELAY = 11,   ///< ��������
        WRITE_REGISTER = 12,   ///< ������� �������� � �������
        READ_DATA = 13,   ///< ������ ������ �� ����������
        SET_DEPTH_MODULATION = 14,
        SET_POLARITY = 15,
        SET_DURATION_RISE = 16,
        SET_DURATION_FALL = 17,
        SET_DURATION_STADY = 18,
        SET_DUTY_FACTOR = 19,
        Number
    };
    ECommandPanel value;
    CommandPanel(ECommandPanel v) : value(v){};
    operator uint8() const { return (uint8)value; };
};

/// ��������� �������, ����������� �� ��������� ����������
struct CommandGenerator
{
    enum
    {
        //   0            1...5
        COM_FREQ_MEASURE = 1,   ///< FREQ_MEASURE �������                                                           /* ��������� ��������� ����������� */
        NUM_COMMAND_READ
    };
};

struct WaveParameter
{
    enum
    {
        Frequency,          ///< �������
        Period,             ///< ������
        Amplitude,          ///< ���������
        Offset,             ///< ��������
        Duration,           ///< ������������
        DutyRatio,          ///< ����������
        Phase,              ///< ����� ����
        Delay,              ///< ��������
        DepthModulation,    ///< ������� ����������� ���������
        Polarity,           ///< ����������
        DurationRise,       ///< ������������ ����������
        DurationFall,       ///< ������������ �����
        DurationStady,      ///< ������������ ������������� ��������
        DutyFactor,         ///< ����������� ����������
        Number
    };
    uint8 type;
    WaveParameter(uint8 t = 0) : type(t)
    {
    };
    WaveParameter(int t) : type((uint8)t)
    {
    };
    bool Is(WaveParameter param) const
    {
        return type == param.type;
    }
    float MinValue();
    float MaxValue();
    pString Name();
    operator uint8() const
    {
        return type;
    }
};

struct WaveForm
{
    enum
    {
        Sine,           ///< �����
        Cosine,         ///< �������
        Meander,        ///< ������
        RampPlus,       ///< ����+
        RampMinus,      ///< ����-
        Triangle,       ///< �����������
        Trapeze,        ///< ��������
        Impulse,        ///< �������
        ExpPlus,        ///< ����������+
        ExpMinus,       ///< ����������-
        Noise,          ///< ���
        Free,           ///< ������������
        Number
    };
    uint8 type;
    pString Name() const;
    bool Is(WaveForm form) const
    {
        return type == form.type;
    }
    WaveForm(uint8 num = 0) : type(num)
    {
    }
    operator uint8() const
    {
        return type;
    }
};

struct Register
{
    enum
    {
        Multiplexor1,
        Multiplexor2,
        OffsetA,
        OffsetB,
        FreqMeterLevel,
        FreqMeterHYS,
        FPGA_RG0_Control,           ///< ����������� �������
        FPGA_RG1_Freq,              ///< ������� ���� �������
        FPGA_RG2_Mul,               ///< ������� ���� ����������
        FPGA_RG3_RectA,             ///< ������� ���� ������� ������������� ����� ������ �
        FPGA_RG4_RectB,             ///< ������� ���� ������� ������������� ����� ������ B
        FPGA_RG5_PeriodImpulseA,    ///< ������� ���� ������� ������������� ��������� ������ �
        FPGA_RG6_DurationImpulseA,  ///< ������� ���� ������������ ������������ ��������� ������ �
        FPGA_RG7_PeriodImpulseB,    ///< ������� ���� ������� ������������� ��������� ������ B
        FPGA_RG8_DurationImpulseB,  ///< ������� ���� ������������ ������������ ��������� ������ B
        FPGA_RG9_FreqMeter,         ///< ������� ���������� �����������
        FPGA_RG10_Offset,           ///< ������� ��������
        Multiplexor3,
        FreqMeter_Resist,
        FreqMeter_Couple,
        FreqMeter_Filtr,
        Number
    };
    Register(uint8 n = Multiplexor1) : name(n)
    {
    };
    uint8 name;
    pString Name() const;
    bool Is(uint8 n) const
    {
        return n == this->name;
    }
    operator uint8() const
    {
        return name;
    }
};


#define LENGTH_SPI_BUFFER   10

#define SPI_SLAVE_SYNBYTE   0x53

#define SPI_MASTER_SYNBYTE  0xAC

#define NAME_FORM(form, lang) namesWaveForm[form][lang]
#define FORM_RU(form) NAME_FORM(form, Language::RU)
#define FORM_EN(form) NAME_FORM(form, Language::EN)
extern const char * namesWaveForm[WaveForm::Number][2];


//const char *Command_Name(CommandPanel command);


/** @}  @} */

#ifdef WIN32
#pragma warning(pop)
#endif
