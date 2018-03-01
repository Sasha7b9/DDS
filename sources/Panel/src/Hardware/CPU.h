#pragma once
#include "Hardware/Controls.h"
#include "Hardware/stm32/429/stm429.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TIME_TICKS CPU::TIM_::TimeTicks()
#define TIME_US    CPU::TIM_::TimeUS()
#define TIME_MS    CPU::TIM_::TimeMS()


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPU : public STM429
{
public:

    static void Init();

    static void OnIRQHandlerTIM3();

    //------------------------------------------------------------------------------------------------------------------------------------------------
    class Keyboard
    {
    public:

        static void Init();
        /// ��������� �������� ��� ����������
        static void SetCallback(void(*func)());

        static void InitInputs(uint16 sl[], char portSL[], int numSL, uint16 rl[], char portRL[], int numRL);
        /// ���������� true, ���� ����� ����
        static bool BufferIsEmpty();
        /// ���������� ��������� ����� ����������, ���� ������� �������
        static StructControl GetNextControl();

    private:

        static void Update();
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------
    class LTDC_
    {
    public:

        static void SetColors(uint clut[], uint numColors);

        static void SetBuffers(uint frontBuffer, uint backBuffer);

        static void ToggleBuffers();
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------
    class SPI4_
    {
    public:
        /// ��������� ������ ������
        static void Transmit(uint8 *buffer, uint16 size, uint timeOut);
        /// ��������� ������ ������ � ������������� ������ ������� �������
        static void TransmitReceive(uint8 *trans, uint8 *receiv, uint16 size, uint timeOut);
        /// ���������� true, ���� ��������� ����� - ��������� �� ����� ���������� �������
        static bool IsBusy();
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------
    class TIM_
    {
    public:
        /// ��������� ������� ��� ��������� ����� ����������� �������
        static void StartMultiMeasurement();
        /// \brief ���������� �����, ��������� � ������� ���������� ������ StartMultiMeasurement(). �� ����� (1 << 32)
        static uint TimeTicks();

        static uint TimeUS();

        static uint TimeMS();
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------
    class TIM3_
    {
    public:
        /// ������� ������, ������� ����������� � timeStop ��
        static void Start(uint timeStopMS);

        static void Stop();
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------
    class GPIO_
    {
    public:
        static void WritePin(char port, uint16 maskPin, bool state);

        static bool ReadPin(char port, uint16 maskPin);
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------
    class FLASH_
    {
    public:
        static void SaveSettings();
        static void LoadSettings();
    };

private:
    /// ������������� SPI ��� ����� � �������� �����������
    static void InitSPI4();

    static void InitTIM2();

    static void InitTIM5();

    static void InitHardware();
    /// ������������� �������
    static void InitLTDC();
    /// ������������� ���� ��� ����� � ����
    static void InitFSMC();

    static void EnablePeriphery();
};
