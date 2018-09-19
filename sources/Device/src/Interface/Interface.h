#pragma once
#include "Command.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Interface
{
public:

    static void Init();

    static void Update();
    /// ������� � ������ ���������� �������� �������
    static void SendFrequency(uint frequency);

    static SPI_HandleTypeDef *HandleSPI();

    static void ReceiveCallback();

    static void Empty();

    static void Enable();

    static void ReadData();

    static void FormWave();

    static void Parameter();

    static void Reset();

    static void ModeDebug();

    static void WriteRegister();
    /// ������� ������������ ������� ������������� �������
    static void CreateWave();

    static void SetRampForSine();

    static void SetDurationForRampSine();

    static void SetAmplitudeRampForSine();

    static void SetPacketPeriod();

    static void SetPacketNumber();

private:

    /// ���������� �������� ���� float, ���������� � �������
    static float GetFloat(uint8 buffer[4]);
    /// ��������� �������� ��������, ��� ��� ������� �������� � ������ ��� ���������� ������������ ��������
    static uint freqForSend;

    static uint timeLastReceive;
};
