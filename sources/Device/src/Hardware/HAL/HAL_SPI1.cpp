#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include <stm32f4xx_hal.h>


static SPI_HandleTypeDef handle =                                   // ��� ����� � �������
{
    SPI1, //-V2571
    {
        SPI_MODE_SLAVE,                 // Init.Mode
        SPI_DIRECTION_2LINES,           // Init.Direction
        SPI_DATASIZE_8BIT,              // Init.DataSize
        SPI_POLARITY_HIGH,              // Init.CLKPolarity
        SPI_PHASE_2EDGE,                // Init.CLKPhase
        SPI_NSS_SOFT,                   // Init.NSS
        SPI_BAUDRATEPRESCALER_32,      // Init.BaudRatePrescaler
        SPI_FIRSTBIT_MSB,               // Init.FirstBit
        SPI_TIMODE_DISABLED,            // Init.TIMode
        SPI_CRCCALCULATION_DISABLED,    // Init.CRCCalculation
        7                               // InitCRCPolynomial
    },
    0, 0, 0, 0, 0, 0,
    0,
    0,
    0, 0, HAL_UNLOCKED, HAL_SPI_STATE_RESET, 0
};



void HAL_SPI1::Init()
{
    GPIO_InitTypeDef isGPIOA =
    {   //  SCK         MI           MO
        GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
        GPIO_MODE_AF_PP,
        GPIO_PULLUP,
        GPIO_SPEED_HIGH,
        GPIO_AF5_SPI1
    };
    HAL_GPIO_Init(GPIOA, &isGPIOA); //-V2571

    HAL_SPI_Init(&handle);
}


bool HAL_SPI1::Receive(void *buffer, int size, int timeout)
{
    return HAL_SPI_Receive(&handle, static_cast<uint8 *>(buffer), static_cast<uint16>(size), static_cast<uint>(timeout)) == HAL_OK; //-V2571
}


bool HAL_SPI1::Transmit(void *buffer, int size, int timeout)
{
    return HAL_SPI_Transmit(&handle, static_cast<uint8 *>(buffer), static_cast<uint16>(size), static_cast<uint>(timeout)) == HAL_OK; //-V2571
}


bool HAL_SPI1::Transmit(int value, int timeout)
{
    return Transmit(&value, 4, timeout);
}
