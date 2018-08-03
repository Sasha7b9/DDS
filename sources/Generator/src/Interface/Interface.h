#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Interface
{
public:

    static void Init();

    static void ProcessingCommand();
    /// ������� � ������ ���������� �������� �������
    static void SendFrequency(uint frequency);

private:

    static void CommandEmpty();

    static void ProcessCommand();

    static void CommandEnable();

    static void CommandReadData();

    static void CommandFormWave();

    static void CommandParameter();

    static void CommandReset();

    static void CommandModeDebug();

    static void CommandWriteRegister();

    static void WriteToInterface(uint8 *buffer, int size);
    /// ��������� �������� ��������, ��� ��� ������� �������� � ������ ��� ���������� ������������ ��������
    static uint freqForSend;
};
