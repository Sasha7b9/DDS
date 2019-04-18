#pragma once
#include "defines.h"
#include <usbd_def.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace VCP
{
    const int DEVICE_FS = 0;

    /// �������������
    void Init();

    void SendData(const void *data, uint size = 0);
    /// ��������� ������ ��� ������������ ����
    void SendString(char *data);
    /// ��� ������ ��������� � ������������ ��������� \\r\\n
    void SendFormatStringSynch(char *format, ...);

    void SendByte(uint8 data);

    void Flush();

    extern USBD_HandleTypeDef handleUSBD;

    extern bool connectedToUSB;

    extern bool cableUSBisConnected;
};
