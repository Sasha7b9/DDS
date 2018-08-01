#include "defines.h"
#include "Log.h"
#include "Interface.h"
#include "Generator/Generator.h"
#include "Generator/Multiplexor.h"
#include "Generator/FPGA.h"
#include "Hardware/CPU.h"
#include "Hardware/FreqMeter.h"
#include "Command.h"
#include "structs.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static SPI_HandleTypeDef hSPI1 =                                   // ��� ����� � �������
{
    SPI1,
    {
        SPI_MODE_SLAVE,                 // Init.Mode
        SPI_DIRECTION_2LINES,           // Init.Direction
        SPI_DATASIZE_8BIT,              // Init.DataSize
        SPI_POLARITY_HIGH,              // Init.CLKPolarity
        SPI_PHASE_2EDGE,                // Init.CLKPhase
        SPI_NSS_SOFT,                   // Init.NSS
        SPI_BAUDRATEPRESCALER_2,        // Init.BaudRatePrescaler
        SPI_FIRSTBIT_MSB,               // Init.FirstBit
        SPI_TIMODE_DISABLED,            // Init.TIMode
        SPI_CRCCALCULATION_DISABLED,    // Init.CRCCalculation
        7                               // InitCRCPolynomial
    },
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, HAL_UNLOCKED, HAL_SPI_STATE_RESET, 0
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint8 buffer[LENGTH_SPI_BUFFER];     ///< ����� ��� ����������� ������


                                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interface::Init()
{
    GPIO_InitTypeDef isGPIOA =
    {   //  SCK         MI           MO
        GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
        GPIO_MODE_AF_PP,
        GPIO_NOPULL,
        GPIO_SPEED_HIGH,
        GPIO_AF5_SPI1
    };
    HAL_GPIO_Init(GPIOA, &isGPIOA);

    HAL_SPI_Init(&hSPI1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::ProcessingCommand()
{
    HAL_StatusTypeDef res = HAL_SPI_Receive(&hSPI1, buffer, LENGTH_SPI_BUFFER, 10);
    
    if (res == HAL_OK)
    {
        if(buffer[0] != 0 || buffer[1] != 0 || buffer[2] != 0)
        {
            buffer[0] = buffer[0];
        }
        
        CPU::SetBusy();

        static uint8 prevBuffer[LENGTH_SPI_BUFFER] = {0};
        bool first = true;

        do
        {
            if (first)
            {
                first = false;
            }
            else
            {
                HAL_SPI_DeInit(&hSPI1);
                HAL_SPI_Init(&hSPI1);
            }
            memcpy(prevBuffer, buffer, LENGTH_SPI_BUFFER);
            res = HAL_SPI_TransmitReceive(&hSPI1, prevBuffer, buffer, LENGTH_SPI_BUFFER, 5);
        } while(memcmp(buffer, prevBuffer, LENGTH_SPI_BUFFER) != 0     // ���� �� �������� ��� �������� ������
                && res != HAL_TIMEOUT);             // ��� �� ������� ����� �������� ������, ��� ��������������� � ���, ��� ���������� �� �������
                                                    // ������, �.�. ��������� �������� ������ ����������

        ProcessCommand();
        CPU::SetReady();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::ProcessCommand()
{
    typedef void(*pFuncInterfaceVV)();

    static const pFuncInterfaceVV commands[NUM_COMMAND_WRITE] =
    {
        CommandEmpty,        /// WRITE_SERVICE_COMMAND
        CommandEnable,       /// ENABLE_CHANNEL
        CommandFormWave,     /// SET_FORM_WAVE
        CommandParameter,    /// SET_FREQUENCY
        CommandParameter,    /// SET_AMPLITUDE
        CommandParameter,    /// SET_OFFSET
        CommandParameter,    /// SET_DURATION
        CommandParameter,    /// SET_DUTYRATIO
        CommandParameter,    /// SET_PHASE
        CommandReset,        /// RUN_RESET
        CommandModeDebug,    /// MODE_DEBUG
        CommandParameter,    /// SET_DELAY
        CommandWriteRegister /// WRITE_REGISTER
    };
  
    if (buffer[0] < NUM_COMMAND_WRITE)
    {       
        pFuncInterfaceVV f = commands[buffer[0]];
        f();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::CommandEnable()
{
    LOG_WRITE("T���");

    Channel ch = (Channel)buffer[1];
    bool enable = buffer[2] == 1;
    
    __IO uint8 b1 = buffer[1];
    __IO uint8 b2 = buffer[2];

    if((b1 != 0 && b1 != 1) || (b2 != 0 && b2 != 1))
    {
        b1 = b1;
    }
    
    Generator::EnableChannel(ch, enable);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::CommandFormWave()
{
    Channel ch = (Channel)buffer[1];
    Type_WaveForm form = (Type_WaveForm)buffer[2];
    Generator::SetFormWave(ch, form);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::CommandWriteRegister()
{
    Name_Register reg = (Name_Register)buffer[1];

    BitSet32 set;
    for (int i = 0; i < 4; i++)
    {
        set.byte[i] = buffer[i + 2];
    }

    uint value = set.word;

    switch (reg)
    {
    case Multiplexor1:
    case Multiplexor2:
        Multiplexor::WriteRegister(reg, value);
        break;

    case OffsetA:
        AD5697::SetOffset(A, (float)value);
        break;

    case OffsetB:
        AD5697::SetOffset(B, (float)value);
        break;

    case FreqMeterLevel:
        AD5697::SetFreqLevel((float)value);
        break;

    case FreqMeterHYS:
        AD5697::SetFreqHysteresys((float)value);
        break;

    case FPGA_RG0_Control:
        FPGA::WriteRegister(FPGA::RG0_Control, value);
        break;

    case FPGA_RG1_Freq:
        FPGA::WriteRegister(FPGA::RG1_Freq, value);
        break;

    case FPGA_RG2_Mul:
        FPGA::WriteRegister(FPGA::RG2_Mul, value);
        break;

    case FPGA_RG3_RectA:
        FPGA::WriteRegister(FPGA::RG3_RectA, value);
        break;

    case FPGA_RG4_RectB:
        FPGA::WriteRegister(FPGA::RG4_RectB, value);
        break;

    case FPGA_RG5_PeriodImpulseA:
        FPGA::WriteRegister(FPGA::RG5_PeriodImpulseA, value);
        break;

    case FPGA_RG6_DurationImpulseA:
        FPGA::WriteRegister(FPGA::RG6_DurationImpulseA, value);
        break;

    case FPGA_RG7_PeriodImpulseB:
        FPGA::WriteRegister(FPGA::RG7_PeriodImpulseB, value);
        break;

    case FPGA_RG8_DurationImpulseB:
        FPGA::WriteRegister(FPGA::RG8_DurationImpulseB, value);
        break;

    case FPGA_RG9_FreqMeter:
        FPGA::WriteRegister(FPGA::RG9_FreqMeter, value);
        break;

    case Multiplexor3:
        Multiplexor::WriteRegister(reg, value);
        break;

    case FreqMeter_Resist:
        FreqMeter::SetResist((FreqResist)value);
        break;

    case FreqMeter_Couple:
        FreqMeter::SetCouple((FreqCouple)value);
        break;

    case FreqMeter_Filtr:
        FreqMeter::SetFiltr((FreqFiltr)value);
        break;

    case NumRegisters:
    default:
        break;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::CommandParameter()
{
    Channel ch = (Channel)buffer[1];
    CommandWrite command = (CommandWrite)buffer[0];
    float value = 0.0f;
    memcpy(&value, &buffer[2], 4);
    Generator::SetParameter(ch, command, value);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::CommandReset()
{
#ifndef MSVC

#define MAIN_PROGRAM_START_ADDRESS  (uint)0x8000000
    typedef void(*pFunction)();
    __disable_irq();
    pFunction JumpToApplication = (pFunction)(*(__IO uint *)(MAIN_PROGRAM_START_ADDRESS + 4));
    __enable_irq();
    JumpToApplication();

#endif
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::CommandModeDebug()
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Interface::CommandEmpty()
{
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
static void SlaveSynchro()
{
    uint8 txByte = SPI_SLAVE_SYNBYTE;
    uint8 rxByte = 0x00;

    do
    {
        HAL_SPI_TransmitReceive(&hSPI1, &txByte, &rxByte, 1, HAL_MAX_DELAY);
    } while(rxByte != SPI_MASTER_SYNBYTE);
}
*/
