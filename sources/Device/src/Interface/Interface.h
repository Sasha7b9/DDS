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

    static void ParameterValue();

    static void Reset();

    static void ModeDebug();

    static void WriteRegister();
    /// ������� ������������ ������� ������������� �������
    static void CreateWave();

    static void SetManipulation();

    static void SetManipulationDuration();

    static void SetManipulationPeriod();

    static void SetStartMode();

    static void Polarity();

private:

    /// ���������� �������� ���� float, ���������� � �������
    static float GetFloat(uint8 buffer[4]);
    /// ��������� �������� ��������, ��� ��� ������� �������� � ������ ��� ���������� ������������ ��������
    static uint freqForSend;

    static uint timeLastReceive;
};
