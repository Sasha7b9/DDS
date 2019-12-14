#pragma once
#include "Hardware/Controls.h"


#define PRIORITY_SOUND_DMA1_STREAM5 5, 0


#define RTC_GET_PACKED_TIME() {}
#define RTC_SET_TIME_AND_DATA(d, m, y, h, min, s)


class CPU
{
public:

    static void Init();

    static void Update();

    static float GetFPS();

    //----------------------------------------------------------------------------------------------------------------------------------- Keyboard ---
    class Keyboard
    {
    friend class CPU;

    private:

        static void Init();

    public:
        static void InitInputs(const uint16 *sl, const char *portSL, int numSL, const uint16 *rl, const char *portRL, int numRL);
        /// ���������� true, ���� ����� ����
        static bool BufferIsEmpty();
        /// ���������� ��������� ����� ����������, ���� ������� �������
        static KeyEvent GetNextControl();
        /// �������-��������. ��� ���������, �� ������� ��� ���������� ���������� � ����� � �������� �� ������
        static void Draw();

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

private:
    /// ����� ������ ������ ��� (����� ������ ���������� 1-���������� ������� �������)
    static uint timeStartMeasFPS;
    /// ������� ������� ��������� � ������ ���������� 1-���������� ������� �������
    static int numFrames;

    static float fps;
};



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
