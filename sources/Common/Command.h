#pragma once
#include "defines.h"


/** @addtogroup Panel
 *  @{
 *  @addtogroup Interface
 *  @{
 */


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
enum CommandPanel
{

    ENABLE_CHANNEL          = 1,    ///< ��������/��������� �����
    SET_FORM_WAVE           = 2,    ///< ���������� ����� �������
    SET_FREQUENCY           = 3,    ///< ���������� �������
    SET_AMPLITUDE           = 4,    ///< ���������� ���������
    SET_OFFSET              = 5,    ///< ���������� ��������
    SET_DURATION            = 6,
    SET_DUTYRATIO           = 7,
    SET_PHASE               = 8,
    RUN_RESET               = 9,    ///< ����� ���������
    MODE_DEBUG              = 10,   ///< ��������� ����������� ������ - ����� ���� ����������� ������� � FPGA
    SET_DELAY               = 11,   ///< ��������
    WRITE_REGISTER          = 12,   ///< ������� �������� � �������
    READ_DATA               = 13,   ///< ������ ������ �� ����������
    NUM_COMMAND_WRITE,
    COMMAND_NONE
};

/// ��������� �������, ����������� �� ��������� ����������
enum CommandGenerator
{
                        //   0            1...5
    FREQ_MEASURE = 1,   ///< FREQ_MEASURE �������                                                                /* ��������� ��������� ����������� */
    NUM_COMMAND_READ
};

enum Type_WaveParameter
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
    NumParameters
};

enum Type_WaveForm
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
    NumForms
};

struct WaveForm
{
    Type_WaveForm type;
    WaveForm(uint8 num = 0);
    pString Name() const;
    uint8 ToValue() const;
};

enum Name_Register
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
    Multiplexor3,
    FreqMeter_Resist,
    FreqMeter_Couple,
    FreqMeter_Filtr,
    NumRegisters
};

struct Register
{
    Register(Name_Register n = Multiplexor1);
    Register(uint8 n = 0);
    Name_Register name;
    pString Name() const;
};


#define LENGTH_SPI_BUFFER   10

#define SPI_SLAVE_SYNBYTE   0x53

#define SPI_MASTER_SYNBYTE  0xAC

#define NAME_FORM(form, lang) namesWaveForm[form][lang]
#define FORM_RU(form) NAME_FORM(form, RU)
#define FORM_EN(form) NAME_FORM(form, EN)
extern const char * namesWaveForm[NumForms][2];


//const char *Command_Name(CommandPanel command);


/** @}  @} */
