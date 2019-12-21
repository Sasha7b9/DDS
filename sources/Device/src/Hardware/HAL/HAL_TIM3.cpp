#include "Hardware/HAL/HAL.h"


static TIM_HandleTypeDef handler;


void HAL_TIM3::Init()
{
    __HAL_RCC_TIM3_CLK_ENABLE();

    handler.Instance = TIM3;
    handler.Init.Prescaler = 54000 - 1;
    handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    handler.Init.Period = 1;
    handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_Base_Init(&handler);

    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    HAL_NVIC_SetPriority(TIM3_IRQn, 1, 1);
}


void HAL_TIM3::StartIT(uint period)
{
    handler.Init.Period = period;
    HAL_TIM_Base_Init(&handler);
    HAL_TIM_Base_Start_IT(&handler);
}


void HAL_TIM3::StopIT()
{
    HAL_TIM_Base_Stop_IT(&handler);
}
