#pragma once
#include "Command.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Interface
{
public:

    static void Init();
    /// ������� � ������ ���������� �������� �������
    static void SendFrequency(uint frequency);

    static void ReceiveCallbackOld();

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

    static void SetManipulationMode();

    static void SetStartMode();

    static void Polarity();

private:
    /// ������� ��������� ������ � ������� ���������
    static void SendData();
    /// ���������� ������ �������� ������ ������ size
    static void ResizeRecieveBuffer(uint16 size);
    /// ��������� �������� ��������, ��� ��� ������� �������� � ������ ��� ���������� ������������ ��������
    static uint freqForSend;

    static uint timeLastReceive;
};
