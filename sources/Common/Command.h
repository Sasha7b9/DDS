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

1.    WRITE_SERVICE_COMMAND

           0             1         2
2.    SET_FORM_CHANNEL NUM_CHAN FormChannel

            0                  1           2          3...6
3.    SET_PARAMETER_CHANNEL NUM_CHAN ParameterChannel value
*/

/// ��������� ������� ��� �������� � �������� ���������
enum CommandWrite
{
    WRITE_SERVICE_COMMAND   = 0,    ///< ���������. ��� ���������� � ���������� ���������� ��� ��������.
    ENABLE_CHANNEL          = 1,    ///< ��������/��������� �����
    SET_FORM_WAVE           = 2,    ///< ���������� ����� �������
    SET_FREQUENCY           = 3,    ///< ���������� �������
    SET_AMPLITUDE           = 4,    ///< ���������� ���������
    SET_OFFSET              = 5,    ///< ���������� ��������
    SET_DURATION            = 6,
    SET_DUTYRATIO           = 7,
    SET_PHASE               = 8,
    RUN_RESET               = 9,   ///< ����� ���������
    MODE_DEBUG              = 10,   ///< ��������� ����������� ������ - ����� ���� ����������� ������� � FPGA
    SET_DELAY               = 11,   ///< ��������
    NUM_COMMAND_WRITE,
    COMMAND_NONE
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
    const char * Name() const;
    uint8 ToValue() const;
};


/// ��������� �������, ����������� �� ��������� ����������
enum CommandRead
{
    READ_SERVICE_COMMAND,   ///< ��������� �������. ������������ ��� ����, ����� ����� ���� �������� ������ ��������� ����������
    READ_POINTS             ///< ��������� ����� ������������� �������
};

#define LENGTH_SPI_BUFFER   10

#define SPI_SLAVE_SYNBYTE   0x53

#define SPI_MASTER_SYNBYTE  0xAC

#define NAME_FORM(form, lang) namesWaveForm[form][lang]
#define FORM_RU(form) NAME_FORM(form, RU)
#define FORM_EN(form) NAME_FORM(form, EN)
extern const char * namesWaveForm[NumForms][2];


//const char *Command_Name(CommandWrite command);


/** @}  @} */
