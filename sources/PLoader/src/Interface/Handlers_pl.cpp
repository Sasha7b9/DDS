#include "defines.h"
#include "common/Command.h"
#include "common/Messages.h"
#include "Handlers_pl.h"
#include "FDrive/FDrive_p.h"
#include <stm32f429xx.h>


static bool OnStartMainApplication(SimpleMessage *message);


bool PHandlers::Processing(SimpleMessage *msg)
{
    typedef bool(*pFuncBpM)(SimpleMessage *);

    static const pFuncBpM funcs[Command::Count] =
    {
        /* RequestData               */ PHandlers::Request,
        /* EnableChannel             */ PHandlers::E,
        /* SetFormWave               */ PHandlers::E,
        /* SetFrequency              */ PHandlers::E,
        /* SetAmplitude              */ PHandlers::E,
        /* SetOffset                 */ PHandlers::E,
        /* SetDuration               */ PHandlers::E,
        /* SetDutyRatio              */ PHandlers::E,
        /* SetPhase                  */ PHandlers::E,
        /* RunReset                  */ PHandlers::E,
        /* ModeDebug                 */ PHandlers::E,
        /* SetDelay                  */ PHandlers::E,
        /* WriteRegister             */ PHandlers::E,
        /* SetDurationRise           */ PHandlers::E,
        /* SetDurationFall           */ PHandlers::E,
        /* SetDurationStady          */ PHandlers::E,
        /* SetDutyFactor             */ PHandlers::E,
        /* SetManipulation           */ PHandlers::E,
        /* SetManipulationDuration   */ PHandlers::E,
        /* SetManipulationPeriod     */ PHandlers::E,
        /* SetPacketPeriod           */ PHandlers::E,
        /* SetPacketNumber           */ PHandlers::E,
        /* SetStartMode              */ PHandlers::E,
        /* SetPeriod                 */ PHandlers::E,
        /* SetPolarity               */ PHandlers::E,
        /* SetManipulationMode       */ PHandlers::E,
        /* LoadFromDDS               */ PHandlers::E,
        /* FreqMeasure               */ PHandlers::E,
        /* Log                       */ PHandlers::E,
        /* FDrive_NumDirsAndFiles    */ FDrive::Handler::Processing,
        /* FDrive_Mount              */ FDrive::Handler::Processing,
        /* FDrive_RequestDir         */ FDrive::Handler::Processing,
        /* FDrive_RequestFile        */ FDrive::Handler::Processing,
        /* Test                      */ PHandlers::E,
        /* SetKoeffCalibration       */ PHandlers::E,
        /* GetKoeffCalibration       */ PHandlers::E,
        /* FDrive_RequestFileSize    */ FDrive::Handler::Processing,
        /* FDrive_RequestFileString  */ FDrive::Handler::Processing,
        /* FDrive_LoadFromExtStorage */ FDrive::Handler::Processing,
        /* FDrive_GetPictureDDS      */ FDrive::Handler::Processing,
        /* SCPI_Data                 */ PHandlers::E,
        /* PortCPU                   */ PHandlers::E,
        /* CalibrationLoad           */ PHandlers::E,
        /* CalibrationSet            */ PHandlers::E,
        /* StartApplication          */ OnStartMainApplication
    };
   
    uint8 command = msg->TakeByte();
    
    if (command < Command::Count)
    {
        /// ���� ��������� ��������� ��� ��� ������� �����
        return funcs[command](msg);
    }

    return false;
}


bool PHandlers::E(SimpleMessage *)
{
    return false;
}


bool PHandlers::Request(SimpleMessage *)
{
    return false;
}


static bool OnStartMainApplication(SimpleMessage *)
{
#define MAIN_PROGRAM_START_ADDRESS  (uint)0x8020000

    typedef void(*pFunction)();

    __disable_irq();

    pFunction JumpToApplication;

    JumpToApplication = (pFunction)(*(__IO uint *)(MAIN_PROGRAM_START_ADDRESS + 4));

    __set_MSP(*(__IO uint *)MAIN_PROGRAM_START_ADDRESS);

    __enable_irq();

    JumpToApplication();

    return true;
}
