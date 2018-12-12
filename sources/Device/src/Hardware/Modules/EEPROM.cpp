#include "stdafx.h"
#ifndef WIN32
#include "EEPROM.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define SECTOR_0                    ((uint)0x08000000)          // 16k  ���������
#define SECTOR_1                    ((uint)0x08004000)          // 16k
#define SECTOR_2                    ((uint)0x08008000)          // 16k
#define SECTOR_3                    ((uint)0x0800c000)          // 16k
#define SECTOR_CALIBRATION_4        ((uint)0x08010000)          // 64k  SettingsCalibration
#define SIZE_SECTOR_CALIBRATION     (64 * 1024)
#define SECTOR_5                    ((uint)0x08020000)          // 128k �������� �������� 1
#define SECTOR_6                    ((uint)0x08040000)          // 128k �������� �������� 2
#define SECTOR_7                    ((uint)0x08060000)          // 128k �������� �������� 3
#define SECTOR_8                    ((uint)0x08080000)          // 128k
#define SECTOR_9                    ((uint)0x080a0000)          // 128k
#define SECTOR_TEMP_10              ((uint)0x080c0000)          // 128k
#define SIZE_SECTOR_TEMP            (128 * 1024)
#define SECTOR_SIGNAL_FPGA_11       ((uint)0x080e0000)          // ������ � ������ ����� �������
#define SIZE_SECTOR_SIGNAL_FPGA     (128 * 1024)

#define CLEAR_FLASH_FLAGS \
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP    |  /* end of operation flag              */   \
                           FLASH_FLAG_OPERR  |  /* operation error flag               */   \
                           FLASH_FLAG_WRPERR |  /* write protected error flag         */   \
                           FLASH_FLAG_PGAERR |  /* programming alignment error flag   */   \
                           FLASH_FLAG_PGPERR |  /* programming parallelism error flag */   \
                           FLASH_FLAG_PGSERR);  /* programming sequence error flag    */



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���������� ������ �����, �������� � ������� ����� 0xffffffff (����� ����������). ����� ���������� � ������ start, ������������ � ������� ������ �������� sizeFull. ������ ������� sizeObject
static uint FindFirstFreeRecord(uint start, uint sizeSector, uint sizeRecord);
/// ���������� ����� ���������� �����, � ������� ������ ���� �� ����� 0xffffffff (� �� ���������� ��������� ���������)
static uint FindLastOccupiedRecord(uint start, uint sizeSector, uint sizeRecord);
/// ������� ������ � ��������� ������� startAddress
static void EraseSector(uint startAddress);
/// ���������� size ���� �� ������� data �� ������ address
static void WriteData(uint address, void *data, uint size);
/// ���������� ��������� ������������� ������� � ��������� ������� address. ����� �������� ����, ���������� -1
static uint GetSector(uint address);
/// ���������� ������ ������� � ������ ��������� �������
static uint SizeSector(uint address);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EEPROM::SaveSettings(CalibrationSettings *settings)
{
    uint address = FindFirstFreeRecord(SECTOR_CALIBRATION_4, SizeSector(SECTOR_CALIBRATION_4), sizeof(CalibrationSettings));

    if (address == 0)
    {
        EraseSector(SECTOR_CALIBRATION_4);
        address = SECTOR_CALIBRATION_4;
    }

    WriteData(address, settings, sizeof(CalibrationSettings));
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint SizeSector(uint address)
{
    if (address == SECTOR_CALIBRATION_4)
    {
        return SIZE_SECTOR_CALIBRATION;
    }
    else if (address == SECTOR_TEMP_10)
    {
        return SIZE_SECTOR_TEMP;
    }
    else if (address == SECTOR_SIGNAL_FPGA_11)
    {
        return SIZE_SECTOR_SIGNAL_FPGA;
    }

    return (16 * 1024);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EEPROM::LoadSettings(CalibrationSettings *settings)
{
    uint address = FindLastOccupiedRecord(SECTOR_CALIBRATION_4, SizeSector(SECTOR_CALIBRATION_4), sizeof(CalibrationSettings));

    if (address)                                            // ���� ����� ���������� ������
    {
        *settings = *((CalibrationSettings *)address);      // �� ������� � � ������� ������
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint FindFirstFreeRecord(uint start, uint sizeFull, uint sizeRecord)
{
    uint address = start;
    uint end = start + sizeFull;

    while (address < end)
    {
        if (*(uint *)address == 0xffffffff)
        {
            return address;
        }
        address += sizeRecord;
    }

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint FindLastOccupiedRecord(uint start, uint sizeSector, uint sizeRecord)
{
    uint address = FindFirstFreeRecord(start, sizeSector, sizeRecord);

    if (address == 0)                               // ���� ��������� ������ ���, ������, ���� ������� ��������
    {
        return start + sizeSector - sizeRecord;     // ���� �������� ��������� ������
    }

    if (address == start)                           // ���� ������ ��������� ������ ��������� � ������ �������, �� ������ ���� - ������ � ���� �� �������������
    {
        return 0;                                   // ���������� 0 ��� ������� ����, ��� ������� ���
    }

    return address - sizeRecord;                    // �� ���� ��������� ������� ���������� ����� ������, ���������� �� ��������� � ������ ���������
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void EraseSector(uint startAddress)
{
    if (GetSector(startAddress) == (uint)-1)
    {
        return;
    }

    CLEAR_FLASH_FLAGS;

    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef isFLASH;
    isFLASH.TypeErase = TYPEERASE_SECTORS;
    isFLASH.Sector = GetSector(startAddress);
    isFLASH.NbSectors = 1;
    isFLASH.VoltageRange = VOLTAGE_RANGE_3;

    uint error = 0;

    HAL_FLASHEx_Erase(&isFLASH, &error);

    HAL_FLASH_Lock();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static uint GetSector(uint address)
{
    struct StructSector
    {
        uint number;
        uint startAddress;
    };

    static const StructSector sectors[] =
    {
        {FLASH_SECTOR_4,  SECTOR_CALIBRATION_4},
        {FLASH_SECTOR_10, SECTOR_TEMP_10},
        {FLASH_SECTOR_11, SECTOR_SIGNAL_FPGA_11},
        {}
    };

    int i = 0;
    while (sectors[i].startAddress)
    {
        if (sectors[i].startAddress == address)
        {
            return sectors[i].number;
        }
        i++;
    }

    return (uint)(-1);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteData(uint address, void *data, uint size)
{
    CLEAR_FLASH_FLAGS;

    HAL_FLASH_Unlock();

    for (uint i = 0; i < size; i++)
    {
        HAL_FLASH_Program(TYPEPROGRAM_BYTE, address++, ((uint8 *)data)[i]);
    }

    HAL_FLASH_Lock();
}

