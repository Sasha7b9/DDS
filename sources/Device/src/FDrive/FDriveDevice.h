#pragma once
#include <ff.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FDrive
{
public:

    static void Init();

    static void Update();
    /// ���������� ���������� ���� ��� ��������
    static uint16 NumBytesForSend();
    /// �������� ������ ��� �������� � ������. ���������� ����� �������� ��������� �� ����� �������� �� ����� ������������� �������� NumBytesForSend ��������
    static uint8 *GetDataForSend(uint8 *buffer);

    static USBH_HandleTypeDef hUSB_Host;
};
