#include "defines.h"
#include "common/Command.h"
#include "common/Messages_pl.h"
#include "Updater_dl.h"
#include "FDrive/FDrive_dl.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"
#include "Interface/Interface_dl.h"
#include <cstring>


/*

    ���������� ���������� ��������� �������.
    ��� ������� DLoader ������� ������� RequestUpdate. ���� ��� ������� � ������� ���������� �������, ����������� ������� ����������.
    ���� ������� ���������� ���.
    1. ������������, ���������� �� ������. ���� �� ���������� - �����.
    2. ����� �� ������ ����� G6-49-D.bat. ���� ���� ���������, ���������� ��������� �������.
    2.1 ������������, ������� �������� ����� �������.
    2.2 ���������� ��������� � ������ � ���, ��� ����� ������� �������� ��������.
    2.3 ����� ��������� �������� ���������� ��������� � ���, ��� �������� ���������.
    2.4 � ������ ���������� ��������� � ������ ������
    2.5 � ������ ������� ����������� �������� ���� � ����������� � ������������ � ������. ����� ������ ������ � ������ ���������� ��������� � ���, ����� ����� ���������� ���������.
    2.6 �� ��������� ������ � ������ ���������� ��������� � ���, ��� ���������� �������� Device ���������.

*/


#define FILE_NAME_DEVICE "G6-49-D.bin"
#define FILE_NAME_PANEL  "G6-49-P.bin"


struct Mode
{
    enum E
    {
        Device,
        Panel
    };
};


static bool needUpgrade = false;

// ������ ���������� ���������
static void E(SimpleMessage *);

// ���������� ������� �� ����������
static void OnRequestUpdate(SimpleMessage *);

// �������� �������� �� ����� fileName (�������� device ��� panel)
static void Upgrade(const char *fileName);

// ������� ��������� � ������� ��������� ����������, ���� ����������
static void SendMessageToPanelIfNeed(Mode::E mode, int size, int fullSize);


void Updater::Handler(SimpleMessage *message)
{
    typedef void(*pFunc)(SimpleMessage *);

    static const pFunc funcs[Command::Count] =
    {
        /* RequestData               */ E,
        /* EnableChannel             */ E,
        /* SetFormWave               */ E,
        /* SetFrequency              */ E,
        /* SetAmplitude              */ E,
        /* SetOffset                 */ E,
        /* SetDuration               */ E,
        /* SetDutyRatio              */ E,
        /* SetPhase                  */ E,
        /* ModeDebug                 */ E,
        /* SetDelay                  */ E,
        /* WriteRegister             */ E,
        /* SetDurationRise           */ E,
        /* SetDurationFall           */ E,
        /* SetDurationStady          */ E,
        /* SetDutyFactor             */ E,
        /* SetManipulation           */ E,
        /* SetManipulationDuration   */ E,
        /* SetManipulationPeriod     */ E,
        /* SetPacketPeriod           */ E,
        /* SetPacketNumber           */ E,
        /* SetStartMode              */ E,
        /* SetPeriod                 */ E,
        /* SetPolarity               */ E,
        /* SetManipulationMode       */ E,
        /* LoadFromDDS               */ E,
        /* FreqMeasure               */ E,
        /* Log                       */ E,
        /* FDrive_NumDirsAndFiles    */ E,
        /* FDrive_Mount              */ E,
        /* FDrive_RequestDir         */ E,
        /* FDrive_RequestFile        */ E,
        /* Test                      */ E,
        /* SetKoeffCalibration       */ E,
        /* GetKoeffCalibration       */ E,
        /* FDrive_RequestFileSize    */ E,
        /* FDrive_RequestFileString  */ E,
        /* FDrive_LoadFromExtStorage */ E,
        /* FDrive_GetPictureDDS      */ E,
        /* SCPI_RecvData             */ E,
        /* PortCPU                   */ E,
        /* CalibrationLoad           */ E,
        /* CalibrationSet            */ E,
        /* StartApplication          */ E,
        /* RequestUpdate             */ OnRequestUpdate,
        /* PortionUpdateDevice       */ E
    };

    message->ResetPointer();

    uint8 com = message->TakeByte();

    if(com < Command::Count)
    {
        pFunc func = funcs[com];

        func(message);
    }
}


static void E(SimpleMessage *)
{

}


static void OnRequestUpdate(SimpleMessage *)
{
    needUpgrade = true;
}


void Updater::UpgradeDevice()
{
    Upgrade(FILE_NAME_DEVICE);
}


void Updater::UpgradePanel()
{
    Upgrade(FILE_NAME_PANEL);
}


static void Upgrade(const char *fileName)
{
    Mode::E mode = (std::strcmp(fileName, FILE_NAME_DEVICE) == 0 ? Mode::Device : Mode::Panel);

    static const int SIZE_CHUNK = 512;    /* ������ ������������ ������ ������ */

    const int fullSize = DLDrive::File::Open(fileName);

    if(fullSize != -1)
    {
        int numSectors = fullSize / (128 * 1024) + 1;

        HAL_EEPROM::EraseSectors(numSectors);

        uint address = Updater::MAIN_PROGRAM_START_ADDRESS;

        static uint8 buffer[SIZE_CHUNK];

        int size = fullSize;

        while(size > 0)
        {
            int readed = (size < SIZE_CHUNK) ? size : SIZE_CHUNK;
            size -= readed;

            DLDrive::File::Read(readed, buffer);

            HAL_EEPROM::WriteBuffer(address, buffer, readed);

            address += readed;

            SendMessageToPanelIfNeed(mode, size, fullSize);
        }

        DLDrive::File::Close();
    }
}


static void SendMessageToPanelIfNeed(Mode::E mode, int size, int fullSize)
{
    static int prevPortion = -1;        // ����� ����� ���������� ��� ���������. ���������� �� 0 �� 100. ���������� ������ ����� ����������

    int portion = static_cast<int>((1.0F - static_cast<float>(size) / fullSize) * 100);

    if(portion != prevPortion)
    {
        if(mode == Mode::Device)
        {
            Message::PortionUpdateDevice(portion).Transmit();
        }
        
        prevPortion = portion;

        while(DInterface::GetOutbox().Size())
        {
            DInterface::Update();
        }
    }
}


bool Updater::NeedUpgrade()
{
    return needUpgrade;
}
