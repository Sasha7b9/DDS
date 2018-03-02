#pragma clang diagnostic ignored "-Wpadded"
#ifdef STM32F207xx
#include <stm32f2xx.h>
#else
#include <stm32f4xx.h>
#endif
#pragma clang diagnostic warning "-Wpadded"
#include "stm32.h"
#include "Hardware/CPU.h"


#ifdef __cplusplus
extern "C" {
#endif

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    __attribute((noreturn)) void HardFault_Handler(void)
    {
        while (1)
        {
        }
    }
    
    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void NMI_Handler(void)
    {
    
    }
    
    //----------------------------------------------------------------------------------------------------------------------------------------------------
    __attribute((noreturn)) void MemManage_Handler(void)
    {
        while (1)
        {
        }
    }
    
    //----------------------------------------------------------------------------------------------------------------------------------------------------
    __attribute((noreturn)) void BusFault_Handler(void)
    {
        while (1)
        {
        }
    }
    
    //----------------------------------------------------------------------------------------------------------------------------------------------------
    __attribute((noreturn)) void UsageFault_Handler(void)
    {
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
    
    //----------------------------------------------------------------------------------------------------------------------------------------------------
    void SysTick_Handler(void)
    {
        HAL_IncTick();
        HAL_SYSTICK_IRQHandler();
    }

#ifdef __cplusplus
}
#endif
