#include "defines.h"
#include "common/Messages_pl.h"
#include "FDrive/FDrive_dl.h"
#include "Interface/Interface_dl.h"
#include "Hardware/CPU.h"
#include "Hardware/HAL/HAL.h"
#include "Updater_dl.h"
#include <stm32f4xx_hal.h>


typedef void(*pFunction)();

static void WithoutUpdate();

static void UpdateAuto();

static void UpdateManual();

static void JumpToMainApplication();


int main()
{
    CPU::Init();

    DLDrive::Init();

    pFuncVV funcs[] = { WithoutUpdate, UpdateAuto, UpdateManual };

    funcs[START_WITHOUT_UPDATE]();

    Message::StartMainApplication().Transmit(); // �������� ������� ������� ��������� ����������

    while(DInterface::GetOutbox().Size())       // � ���, ���� ��� ����������
    {
        DInterface::Update();
    }

    JumpToMainApplication();                    // � �������� ��� �� �������� ��������

    return 0;
}


static void WithoutUpdate()
{

}


static void UpdateAuto()
{

}


static void UpdateManual()
{
    uint start = HAL_TIM::TimeMS();

    while(HAL_TIM::TimeMS() - start < 10000)     // ��� �������
    {
        DInterface::Update();                   // ��������� �� ������ � ������� ����������
        DLDrive::Update();
        if(Updater::NeedUpgrade())              // ���� ���������
        {
            Updater::Upgrade();                 // ���������� ����������
            break;
        }
    }
}


static void JumpToMainApplication()
{
    __disable_irq();

    pFunction JumpToApplication;

    JumpToApplication = reinterpret_cast<pFunction>(*reinterpret_cast<__IO uint *>(Updater::MAIN_PROGRAM_START_ADDRESS + 4)); //-V566

    __set_MSP(*(__IO uint *)Updater::MAIN_PROGRAM_START_ADDRESS);

    __enable_irq();

    JumpToApplication();
}
