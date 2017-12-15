#include "AD9952.h"
#include "Common.h"
#include "defines.h"
#include "GeneratroSettings.h"
#include <math.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static SPI_HandleTypeDef hSPI3 =
{
    SPI3,
    {
        SPI_MODE_MASTER,
        SPI_DIRECTION_1LINE,
        SPI_DATASIZE_8BIT,
        SPI_POLARITY_LOW,
        SPI_PHASE_1EDGE,
        SPI_NSS_SOFT,
        SPI_BAUDRATEPRESCALER_2,
        SPI_FIRSTBIT_MSB,
        SPI_TIMODE_DISABLE,
        SPI_CRCCALCULATION_DISABLE,
        10
    }
};


typedef enum
{
    AD9952_CFR1,
    AD9952_CFR2,
    AD9952_ASF,
    AD9952_ARR,
    AD9952_FTW0,
    AD9952_POW
} RegAD9952;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void WriteRegister(Channel ch, RegAD9952 reg);
static void WriteCFR1(Channel ch);
static void WriteCFR2(Channel ch);
static void WriteASF(Channel ch);
static void WriteFTW0(Channel ch);
static void WriteToHardware(Channel ch, RegAD9952 reg, uint value);
static GeneratorPin ChipSelect(Channel ch);
static void Reset();


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AD9952::Init(void)
{
    __HAL_RCC_SPI3_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef isGPIO = 
    {   //   SCK          MI           MO
        GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12,
        GPIO_MODE_AF_PP,
        GPIO_NOPULL,
        GPIO_SPEED_FREQ_MEDIUM,
        GPIO_AF6_SPI3
    };

    HAL_GPIO_Init(GPIOC, &isGPIO);

    HAL_SPI_Init(&hSPI3);

    Reset();

    WriteCFR1(A);
    WriteCFR1(B);

    WriteCFR2(A);
    WriteCFR2(B);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AD9952::SetFrequency(Channel ch, float frequency)
{
    setDDS.ad9952[ch].frequency = frequency;
    WriteRegister(ch, AD9952_FTW0);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void AD9952::SetAmplitude(Channel ch, float amplitude)
{
    setDDS.ad9952[ch].amplitude = amplitude;
    WriteRegister(ch, AD9952_ASF);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteRegister(Channel ch, RegAD9952 reg)
{
    static const pFuncVCh func[] = {WriteCFR1, WriteCFR2, WriteASF, 0, WriteFTW0, 0};

    pFuncVCh f = func[reg];

    if (f)
    {
        f(ch);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteCFR1(Channel ch)
{
    uint value = 0;
    if(ch == B)
    {
        SetBit(value, 1);
        SetBit(value, 23);
    }
    SetBit(value, 9);       // ���������������� �����
    SetBit(value, 13);
    SetBit(value, 25);      // OSK enable - ���������� ����������
    WriteToHardware(ch, AD9952_CFR1, value);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteCFR2(Channel ch)
{
    uint value = 0;
    SetBit(value, 3);
    WriteToHardware(ch, AD9952_CFR2, value);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteASF(Channel ch)
{
    uint value = ((uint)((setDDS.ad9952[ch].amplitude / 5.0f) * ((1 << 7) - 1))) << 7;

    WriteToHardware(ch, AD9952_ASF, value);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteFTW0(Channel ch)
{
    float FTWf = (setDDS.ad9952[ch].frequency / 1e8f) * powf(2, 32);

    WriteToHardware(ch, AD9952_FTW0, (uint)(FTWf + 0.5f));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteToHardware(Channel ch, RegAD9952 reg, uint value)
{
    static const int numBytes[] =               // ����� ���� ������ ��� ��������
    { //CFR1 CFR2 ASF ARR FTW0 POW
         4,   3,   2,  1,  4,   2
    };

    uint8 buffer[5];
    buffer[0] = (uint8)reg;
    int pointer = 1;                    // � ��� ����� ������ ����� ���������� ������ ��������� ����

    int curByte = numBytes[reg] - 1;    // ����� ����� ���������� ����� value �� �������� � ��������
    while (curByte >= 0)
    {
        buffer[pointer++] = (uint8)(value >> (curByte * 8));
        --curByte;
    }
    
    WritePin(ChipSelect(ch), false);

    HAL_SPI_Transmit(&hSPI3, buffer, numBytes[reg] + 1, 1);
    
    WritePin(AD9952_IO_UPD, true);
    volatile int i = 0;
    for (; i < 1000; ++i)
    {
    };
    WritePin(AD9952_IO_UPD, false);

    WritePin(ChipSelect(ch), true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static GeneratorPin ChipSelect(Channel ch)
{
    return (ch == A) ? AD9952_SPI3_CSA : AD9952_SPI3_CSB;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Reset(void)
{
    WritePin(AD9952_RES_DDS, false);
    WritePin(AD9952_RES_DDS, true);
    WritePin(AD9952_RES_DDS, false);

    WritePin(AD9952_SPI3_CSA, true);
    WritePin(AD9952_SPI3_CSB, true);
    WritePin(AD9952_IO_UPD, false);
    WritePin(AD9952_IOSYNA, false);
    WritePin(AD9952_IOSYNB, false);

    WritePin(AD9952_RES_DDS, false);
    WritePin(AD9952_RES_DDS, true);
    WritePin(AD9952_RES_DDS, false);
}
