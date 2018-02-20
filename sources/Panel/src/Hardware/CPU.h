#pragma once
#include "common/stm32/429/stm429.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
class _LTDC_
{
public:
    static void SetColors(uint clut[], uint numColors);
};
*/



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPU : public STM429
{
public:

    static void Config();

    /// ��������� �������� ��� ����������
    static void SetCallbackKeyboard(void (*func)());

    static void InitKeyboardInputs(uint16 sl[], char portSL[], int numSL, uint16 rl[], char portRL[], int numRL);

    //------------------------------------------------------------------------------------------------------------------------------------------------
    class _LTDC_
    {
    public:

        static void SetColors(uint clut[], uint numColors);

        static void SetFrontBuffer(uint frontBuffer);
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------
    class _SPI4_
    {
    public:
        /// ��������� ������ ������
        static void Transmit(uint8 *buffer, uint16 size, uint timeOut);
        /// ��������� ������ ������ � ������������� ������ ������� �������
        static void TransmitReceive(uint8 *trans, uint8 *receiv, uint16 size, uint timeOut);
        /// ���������� true, ���� ��������� ����� - ��������� �� ����� ���������� �������
        static bool IsBusy();
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
