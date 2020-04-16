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
    2.1 ��������� ������� ��������, ������� �����, ����� ������ �������� ��������
    2.2 � PLoader ��������� ��������� PortionUpgradeDevice ��� ���������� � �������� ����������. ��� ���������� ��� 0, 1, 2 � �.�. ��������� ����������.
    3. ����� �� ������ ����� G6-49-P.bat. ���� ���� ���������, ���������� ����������.
    3.1 ���������� ��������� AnswerUpgrade � ����������� � ������� ��������.
    3.2 ����� PLoader �������� ����������� "������" �������� �������� SIZE_CHUNK � ������� ������� RequestPortionUpgradePanel. � ����� �� ������ ����� ������� DLoader �������� �������
        AnswerPortionUpgradePanel � SIZE_CHUNK ������� ��������, ���������� ������� ������ (��� ������� ���������� ������) � ����������� ������ ������ ������.
        ����� ��� ������ �������� � ������� ��������������, PLoader �������� RequestPortionUpgradePanel � ������� 65535 - ��� �������� ����� ����������.
    4. � ����� ���������� (��� ������, ���� ������ �� ���������� �� ������) DLoader �������� ������� StartApplication
*/



#define FILE_NAME_DEVICE "G6-49-D.bin"
#define FILE_NAME_PANEL  "G6-49-P.bin"

static bool needUpgrade = false;

struct StructUpgradePanel
{
    StructUpgradePanel() : inProcess(false), sizeFirmware(-1), sector(-1) { }

    bool inProcess;     // ������������� � true �������� ��������, ��� ��� ������� �������� panel
    int sizeFirmware;   // ������ �������� Panel
    int sector;         // ���� ������ �������� Panel ������ ������� � ������ EEPROM::TEMP. -1, ���� ������ �� �������
};


volatile static StructUpgradePanel sup;


// ������ ���������� ���������
static void E(SimpleMessage *);

// ���������� ������� �� ����������
static void OnRequestUpgrade(SimpleMessage *);

// ���������� ������� �� ��������� ������ ������ ��������
static void OnRequestPortionUpgradePanel(SimpleMessage *);

// ������� ��������� � ������� ��������� ���������� device
static void SendMessageAboutDevicePortion(int size, int fullSize);

static int CalculatePortion(int size, int fullSize);

// ���������� � ������ ������ sector � EEPROM
static void WriteSectorToEEPROM(int sector);


void Updater::Handler(SimpleMessage *message)
{
    typedef void(*pFunc)(SimpleMessage *);

    static const pFunc funcs[Command::Count] =
    {
        /* RequestData                */ E,
        /* EnableChannel              */ E,
        /* SetFormWave                */ E,
        /* SetFrequency               */ E,
        /* SetAmplitude               */ E,
        /* SetOffset                  */ E,
        /* SetDuration                */ E,
        /* SetDutyRatio               */ E,
        /* SetPhase                   */ E,
        /* ModeDebug                  */ E,
        /* SetDelay                   */ E,
        /* WriteRegister              */ E,
        /* SetDurationRise            */ E,
        /* SetDurationFall            */ E,
        /* SetDurationStady           */ E,
        /* SetDutyFactor              */ E,
        /* SetManipulation            */ E,
        /* SetManipulationDuration    */ E,
        /* SetManipulationPeriod      */ E,
        /* SetPacketPeriod            */ E,
        /* SetPacketNumber            */ E,
        /* SetStartMode               */ E,
        /* SetPeriod                  */ E,
        /* SetPolarity                */ E,
        /* LoadFromDDS                */ E,
        /* FreqMeasure                */ E,
        /* Log                        */ E,
        /* FDrive_NumDirsAndFiles     */ E,
        /* FDrive_Mount               */ E,
        /* FDrive_RequestDir          */ E,
        /* FDrive_RequestFile         */ E,
        /* Test                       */ E,
        /* FDrive_RequestFileSize     */ E,
        /* FDrive_RequestFileString   */ E,
        /* FDrive_LoadFromExtStorage  */ E,
        /* FDrive_GetPictureDDS       */ E,
        /* SCPI_RecvData              */ E,
        /* PortCPU                    */ E,
        /* CalibrationLoad            */ E,
        /* CalibrationSet             */ E,

        /* StartApplication           */ E,
        /* RequestUpgrade             */ OnRequestUpgrade,
        /* PortionUpgradeDevice       */ E,
        /* AnswerUpgradePanel         */ E,
        /* RequestPortionUpgradePanel */ OnRequestPortionUpgradePanel,
        /* AnswerPortionUpgradePanel  */ E
    };

    message->ResetPointer();

    uint8 com = message->TakeUINT8();

    if(com < Command::Count)
    {
        pFunc func = funcs[com];

        func(message);
    }
}


static void E(SimpleMessage *)
{

}


static void OnRequestUpgrade(SimpleMessage *)
{
    needUpgrade = true;
}


void Updater::UpgradeDevice()
{
    const int fullSize = DLDrive::File::Open(FILE_NAME_DEVICE);

    if(fullSize != -1)
    {
        int numSectors = fullSize / (128 * 1024) + 1;

        HAL_EEPROM::EraseSectors(numSectors);

        int address = MAIN_PROGRAM_START_ADDRESS;

        static uint8 buffer[SIZE_CHUNK];

        int size = fullSize;

        while(size > 0)
        {
            int readed = DLDrive::File::Read(SIZE_CHUNK, buffer);

            HAL_EEPROM::WriteBuffer(address, buffer, readed);

            SendMessageAboutDevicePortion(size, fullSize);

            size -= readed;
            address += readed;
        }

        DLDrive::File::Close();
    }
}


void Updater::UpgradePanel()
{
    sup.sizeFirmware = DLDrive::File::Open(FILE_NAME_PANEL);

    if(sup.sizeFirmware != -1)
    {
        Message::AnswerUpgradePanel(sup.sizeFirmware).TransmitAndSend();

        sup.inProcess = true;       // ������������� ������� ���������� ������

        while(sup.inProcess)        // � ���, ���� �� �� ������ �� ����� ���������.
        {
            DInterface::Update();
        }

        DLDrive::File::Close();
    }
}


static void OnRequestPortionUpgradePanel(SimpleMessage *msg)
{
    int16 num = msg->TakeINT16();

    if(num == 0xFFFF)                           // ���� ������ �� ������ 65535, ��� ������� ����, ��� ������� ���������� ��������
    {
        sup.inProcess = false;
    }
    else
    {
        int address = num * SIZE_CHUNK;         // ����� ������������ ������ ��������

        int sector = address / (128 * 1024);    // ���������� ����� �������, � ������� ��������� ������������� "����"

        if (sector != sup.sector)
        {
            WriteSectorToEEPROM(sector);        // ������������ ������ � ������ � EEPROM, ���� ��� ����������

            sup.sector = sector;
        }

        address = address - sector * (128 * 1024) + HAL_EEPROM::ADDRESS_SECTOR_TEMP;    // ������ ��� ����� ������ ����� ������������ ������ �������

        Message::AnswerPortionUpgradePanel(num, reinterpret_cast<uint8 *>(address)).TransmitAndSend();
    }
}


static void WriteSectorToEEPROM(int sector)
{
    HAL_EEPROM::EraseSectorTemp();

    static const int SIZE_STRING = 1024;

    DLDrive::File::Seek(sector * 128 * SIZE_STRING);        // ������������� ��������� � ����� �� ������ �������

    uint8 buffer[SIZE_STRING];                              // ���� ����� ��������� ���� ����

    int readed = SIZE_STRING;                               // ����� ����� ��������� ���������� ������� ��������� ����

    int address = HAL_EEPROM::ADDRESS_SECTOR_TEMP;          // � ����� ������ ����� ��������� ������ � EEPROM

    for (int i = 0; (i < 128) && (readed == SIZE_STRING); i++)
    {
        readed = DLDrive::File::Read(SIZE_STRING, buffer);  // ������ ��������� ������ ������

        HAL_EEPROM::WriteBuffer(address, buffer, readed);   // ���������� � � EEPROM

        address += SIZE_STRING;                             // ��������� ������ ������ ����� ���������� �� ����� ������
    }
}


static void SendMessageAboutDevicePortion(int size, int fullSize)
{
    static int prevPortion = -1;        // ����� ����� ���������� ��� ���������. ���������� �� 0 �� 100. ���������� ������ ����� ����������

    int portion = CalculatePortion(size, fullSize);

    if(portion != prevPortion)
    {
        prevPortion = portion;

        Message::PortionUpgradeDevice(portion).TransmitAndSend();
    }
}


static int CalculatePortion(int size, int fullSize)
{
    return static_cast<int>((1.0F - static_cast<float>(size) / fullSize) * 100);
}


bool Updater::NeedUpgrade()
{
    return needUpgrade;
}
