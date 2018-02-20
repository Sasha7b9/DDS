#include "defines.h"
#include "Hardware.h"
#include "Timer.h"
#include "Display/Display.h"
#include "Generator/Generator.h"
#include "Hardware/CPU.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Hardware_Init(void)
{
    CPU::Config();
   
    Display::Init();

    Timer_Init();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef USE_FULL_ASSERT

/**
* @brief Reports the name of the source file and the source line number
* where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */

}

#endif      // #ifdef USE_FULL_ASSERT

