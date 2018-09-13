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

    static void CommandEmpty();

    static void CommandEnable();

    static void CommandReadData();

    static void CommandFormWave();

    static void CommandParameter();

    static void CommandReset();

    static void CommandModeDebug();

    static void CommandWriteRegister();
    /// ������� ������������ ������� ������������� �������
    static void CommandCreateWave();

    static void CommandSetWave();

    static void CommandSetRampForSine();

    static void CommandSetDurationForRampSine();

    static void CommandSetAmplitudeRampForSine();

private:
    /// ���������� �������� ���� float, ���������� � �������
    static float GetFloat(uint8 buffer[4]);
    /// ��������� �������� ��������, ��� ��� ������� �������� � ������ ��� ���������� ������������ ��������
    static uint freqForSend;

    static uint timeLastReceive;
};
