#include "defines.h"
#include "Keyboard/Keyboard.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern TIM_HandleTypeDef timHandle;

#ifdef __cplusplus
extern "C" {
#endif

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void LTDC_IRQHandler(void)
    {
        //HAL_LTDC_IRQHandler(&LtdcHandle);
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void TIM3_IRQHandler(void)
    {
        HAL_TIM_IRQHandler(&timHandle);
    }

    void SysTick_Handler(void)
    {
        HAL_IncTick();
        HAL_SYSTICK_IRQHandler();
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void NMI_Handler(void)
    {
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void HardFault_Handler(void)
    {
        /* Go to infinite loop when Hard Fault exception occurs */
        while (1)
        {
        }
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void MemManage_Handler(void)
    {
        /* Go to infinite loop when Memory Manage exception occurs */
        while (1)
        {
        }
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void BusFault_Handler(void)
    {
        /* Go to infinite loop when Bus Fault exception occurs */
        while (1)
        {
        }
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void UsageFault_Handler(void)
    {
        /* Go to infinite loop when Usage Fault exception occurs */
        while (1)
        {
        }
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void SVC_Handler(void)
    {
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void DebugMon_Handler(void)
    {
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void PendSV_Handler(void)
    {
    }

#ifdef __cplusplus
}
#endif
