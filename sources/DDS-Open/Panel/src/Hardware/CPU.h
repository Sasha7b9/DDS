#pragma once
#include "Hardware/Controls.h"
#include "Hardware/stm746.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RTC_GET_PACKED_TIME() {}
#define RTC_SET_TIME_AND_DATA(d, m, y, h, min, s)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPU : public STM746
{
public:

    static void Init();

    //----------------------------------------------------------------------------------------------------------------------------------- Keyboard ---
    class Keyboard
    {
    friend class CPU;

    private:

        static void Init();

        static void DrawButton(int x, int y, char *title);

    public:
        static void Draw();
        /// ��������� �������� ��� ����������
        static void SetCallback(void(*func)());
        /// ���������� true, ���� ����� ����
        static bool BufferIsEmpty();
        /// ���������� ��������� ����� ����������, ���� ������� �������
        static StructControl GetNextControl();

        //----------------------------------------------------------------------------------------------------------------------------------- TIM4 ---
        class TIM4_
        {
        public:
            /// ������� ������, ������� ����������� � timeStop ��
            static void Start(uint timeStopMS);

            static void Stop();

            static void ElapsedCallback(void *htim);
        };

    private:

        static void Update();
    };

    //-------------------------------------------------------------------------------------------------------------------------------------- GPIO ----
    class GPIO_
    {
    public:
        static void WritePin(char port, uint16 maskPin, bool state);

        static bool ReadPin(char port, uint16 maskPin);
    };

    //-------------------------------------------------------------------------------------------------------------------------------------- FLASH ---
    class FLASH_
    {
    public:
        static void SaveSettings();
        static void LoadSettings();
    };
    
    //---------------------------------------------------------------------------------------------------------------------------------------- FMC ---
    class FMC_
    {
    friend class CPU;
    private:
        static void Init();
    };
    
    //-------------------------------------------------------------------------------------------------------------------------------------- SDRAM ---
    class SDRAM_
    {
    friend class CPU;
    private:
        static void Init();
        static void InitializationSequence(uint count);
        static SDRAM_HandleTypeDef sdramHandle;
#define SDRAM_DEVICE_ADDR ((uint)0xD0000000)
    };

private:

    static void SystemClockConfig();
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif

    /// ���������� �� ������. Timer.cpp
    void TIM3_IRQHandler();
    /// ���������� �� ����� ����������. CPU_Keyboard.cpp
    void TIM4_IRQHandler();

    void NMI_Handler();
    void HardFault_Handler();
    void MemManage_Handler();
    void BusFault_Handler();
    void UsageFault_Handler();
    void SVC_Handler();
    void DebugMon_Handler();
    void PendSV_Handler();
    void SysTick_Handler();
    
#ifdef __cplusplus
}
#endif
