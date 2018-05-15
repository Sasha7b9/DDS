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

enum WaveParameter
{
    Frequency,      ///< �������
    Period,         ///< ������
    Amplitude,      ///< ���������
    Offset,         ///< ��������
    Duration,       ///< ������������
    DutyRatio,      ///< ����������
    Phase,          ///< ����
    Delay,          ///< ��������
    NumParameters
};

enum Type_WaveForm
{
    Form_Sine,
    Form_Saw,
    Form_Impulse,
    NumForms
};

struct WaveForm
{
    Type_WaveForm type;
    WaveForm(uint8 num = 0) : type((Type_WaveForm)num) {};
    const char * Name();
    uint8 ToValue();
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


const char *Command_Name(CommandWrite command);


/** @}  @} */
