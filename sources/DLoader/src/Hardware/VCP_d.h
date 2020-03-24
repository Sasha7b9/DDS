#pragma once
#include <usbd_def.h>


class SimpleMessage;


struct DVCP
{
    static const int DEVICE_FS = 0;

    /// �������������
    static void Init();

    static void SendData(const void *data, uint size = 0);
    /// ��������� ������ ��� ������������ �������
    static void SendString(char *data);
    /// �������� ������ � �������� ����� ������
    static void SendStringEOF(char *data);

    static void SendByte(uint8 data);

    static USBD_HandleTypeDef handleUSBD;

    struct Handler
    {
        static void Processing(SimpleMessage *msg);
    };

    static void SetConnectedToUSB(bool connected);

    static void SetCableUSBisConnected(bool connected);

private:
    bool PrevSendingComplete();

    static bool connectedToUSB;

    static bool cableUSBisConnected;
};
