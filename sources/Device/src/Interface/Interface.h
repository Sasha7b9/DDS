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

private:

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
    /// ��������� �������� ��������, ��� ��� ������� �������� � ������ ��� ���������� ������������ ��������
    static uint freqForSend;

    typedef void(*pFuncInterfaceVV)();

    struct FuncInterface
    {
        pFuncInterfaceVV func;
        FuncInterface(pFuncInterfaceVV f) : func(f) {};
    };
    /// ����� �������� ����������� ������
    static const FuncInterface commands[CommandPanel::Number];

    static uint timeLastReceive;
};
