#pragma once
#include "Command.h"
#include "CommonTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum BillingTime
{
    BillingTime_1ms,
    BillingTime_10ms,
    BillingTime_100ms,
    BillingTime_1000ms,
    BillingTime_10000ms
};

enum Language
{
    RU,
    EN
};

enum SizeByte
{
    Size_7bit,
    Size_8bit
};

enum StopBit
{
    StopBit_1,
    StopBit_2
};

enum Parity
{
    Parity_Off,
    Parity_On
};

/// 
enum FreqInterval
{
    FreqInterval_1,
    FreqInterval_10
};

/// �������� ������� ��� ������
enum FreqMeasure
{
    FreqMeasure_Freq,
    FreqMeasure_Period
};

/// ����� ����������� ������ � ������ ��������� ������� �������
enum FreqAvePeriod
{
    FreqAvePeriod_1,
    FreqAvePeriod_10,
    FreqAvePeriod_100,
    FreqAvePeriod_1000,
    FreqAvePeriod_10000
};

/// ����� �������
enum FreqTimeStamps
{
    FreqTimeStamps_1kHz,
    FreqTimeStamps_10kHz,
    FreqTimeStamps_100kHz,
    FreqTimeStamps_1MHz,
    FreqTimeStamps_10MHz
};

float MinValue(Type_WaveParameter param);
float MaxValue(Type_WaveParameter param);
