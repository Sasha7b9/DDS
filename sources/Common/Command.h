#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "CommonTypes.h"


#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4514 4623)
#endif

#include "Wave.h"


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

    0                1        2...3       4...9
20  CREATE_HAND_WAVE NUM_CHAN START_POINT points

    0              1        2
22  SetRampForSine NUM_CHAN 0/1

    0                      1        2...5
23  SetDurationRampForSine NUM_CHAN value
*/

/// ��������� ������� ��� �������� � �������� ���������
struct CommandPanel
{
    enum E
    {
        None,
        EnableChannel,              ///< ��������/��������� �����
        SetFormWave,                ///< ���������� ����� �������
        SetFrequency,               ///< ���������� �������
        SetAmplitude,               ///< ���������� ���������
        SetOffset,                  ///< ���������� ��������
        SetDuration,
        SetDutyRatio,
        SetPhase,
        RunReset,                   ///< ����� ���������
        ModeDebug,                  ///< ��������� ����������� ������ - ����� ���� ����������� ������� � FPGA
        SetDelay,                   ///< ��������
        WriteRegister,              ///< ������� �������� � �������
        SetDurationRise,
        SetDurationFall,
        SetDurationStady,
        SetDutyFactor,
        SetManipulation,            ///< ���������� ����� �����������
        SetManipulationDuration,    ///< ���������� ������������ ������� � ������ �����������
        SetManipulationPeriod,      ///< ���������� ������ ���������� ��������� � ������ �����������
        SetPacketPeriod,
        SetPacketNumber,
        // 0            1        2
        // SetStartMode NUM_CHAN value
        SetStartMode,               ///< ���������� ����� ������� �� ������
        SetPeriod,                  ///< ���������� ������
        // 0           1        2
        // SetPolarity NUM_CHAN polarity
        SetPolarity,
        // 0                   1        2
        // SetModeManipulation NUM_CHAN mode
        SetModeManipulation,
        // 0
        // RequestData
        RequestData,                ///< ������ ������
        Number
    } value;
    CommandPanel(E v) : value(v) {};
    CommandPanel(uint8 v) : value((E)v) {};
    operator uint8() const { return (uint8)value; };
    pString Name() const;
    pString Trace(uint8 *buffer) const;
private:
    pString Value(uint8 *buffer) const;
};

/// ��������� �������, ����������� �� ��������� ����������
struct CommandGenerator
{
    enum E
    {
        //                      0           1...5
        FreqMeasure = 1,   ///< FreqMeasure �������                                                        /* ��������� ��������� ����������� */
        Log = 2,
        Number
    } value;
};

struct Register
{
    enum E
    {
        Multiplexor1,
        Multiplexor2,
        OffsetA,
        OffsetB,
        FreqMeterLevel,
        FreqMeterHYS,
        FPGA_RG0_Control,           ///< ����������� �������
        FPGA_RG1_Freq,              ///< ������� ���� �������
        FPGA_RG2_Amplitude,         ///< ������� ���� ����������
        FPGA_RG3_RectA,             ///< ������� ���� ������� ������������� ����� ������ �
        FPGA_RG4_RectB,             ///< ������� ���� ������� ������������� ����� ������ B
        FPGA_RG5_PeriodImpulseA,    ///< ������� ���� ������� ������������� ��������� ������ �
        FPGA_RG6_DurationImpulseA,  ///< ������� ���� ������������ ������������ ��������� ������ �
        FPGA_RG7_PeriodImpulseB,    ///< ������� ���� ������� ������������� ��������� ������ B
        FPGA_RG8_DurationImpulseB,  ///< ������� ���� ������������ ������������ ��������� ������ B
        FPGA_RG9_FreqMeter,         ///< ������� ���������� �����������
        FPGA_RG10_Offset,           ///< ������� ��������
        FreqMeter_Resist,
        FreqMeter_Couple,
        FreqMeter_Filtr,
        Number
    } value;
    Register(E v) : value(v) {};
    operator uint8() const { return (uint8)value; };
    pString Name() const;
};


#define LENGTH_SPI_BUFFER   30

#define SPI_SLAVE_SYNBYTE   0x53

#define SPI_MASTER_SYNBYTE  0xAC

#define NAME_FORM(form, lang)  Form(form).Name(lang)
#define FORM_RU(form) NAME_FORM(form, Language::RU)
#define FORM_EN(form) NAME_FORM(form, Language::EN)


/** @}  @} */

#ifdef WIN32
#pragma warning(pop)
#endif
