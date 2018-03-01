#pragma once
#include "Hardware/stm32/407/stm407.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    AD9952_SPI3_CSA,
    AD9952_SPI3_CSB,
    AD9952_IO_UPD,
    AD9952_IOSYNA,
    AD9952_IOSYNB,
    AD9952_RES_DDS,
    Pin_P1_AmplifierA,
    Pin_P2_AmplifierB,
    Pin_P3_OutA,
    Pin_P4_OutB,
    AD5697_LDACA,
    AD5697_LDACB,
    AD5697_D_RSA,
    AD5697_D_RSB,
    FPGA_WR_RG,
    FPGA_CLK_RG,
    FPGA_DT_RG,
    FPGA_A0_RG,
    FPGA_A1_RG,
    FPGA_A2_RG,
    FPGA_A3_RG,
    NumPins
} GeneratorPin;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CPU : public STM407
{
public:
    static void Init();
    /// ���������� �� PA2 ������� ����, ��� ��������� �����
    static void SetBusy();
    /// ���������� �� PA2 ������� ����, ��� ��������� ��������
    static void SetReady();
    
    static  void WritePin(GeneratorPin pin, bool set);

private:

    static void EnablePeriphery();

    static void InitGPIOS();
    /// ��������� ������������� ����������� �������
    static void InitPins();

};
