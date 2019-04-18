#pragma once
#include "defines.h"
#include <usbd_def.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @defgroup VCP
 *  @brief Virtual Com Port
 *  @{
 */
 
#define VCP_FLUSH()                       VCP::Flush()
#define VCP_SEND_DATA_SYNCH(buffer, size) VCP::SendDataSynch(buffer, size)
#define CONNECTED_TO_USB                  VCP::connectedToUSB
#define CABLE_USB_IS_CONNECTED            VCP::cableUSBisConnected

namespace VCP
{
    const int DEVICE_FS = 0;

    /// �������������
    void Init();

    void SendDataAsynch(uint8 *data, uint size);

    void SendDataSynch(const void *data, uint size = 0);
    /// ��������� ������ ��� ������� ��������� ������
    void SendStringAsynch(char *data);
    /// ��������� ������ � �������� ��������� ������
    void SendStringAsynchEOF(char *data);
    /// ��������� ������ ��� ������������ ����
    void SendStringSynch(char *data);
    /// ��� ������ ��������� � ������������ ��������� \\r\\n
    void SendFormatStringAsynch(char *format, ...);
    /// ��� ������ ��������� � ������������ ��������� \\r\\n
    void SendFormatStringSynch(char *format, ...);

    void SendByte(uint8 data);

    void Flush();

    extern USBD_HandleTypeDef handleUSBD;

    extern bool connectedToUSB;

    extern bool cableUSBisConnected;
};



/** @}
 */
