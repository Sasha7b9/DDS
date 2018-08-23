#pragma once
#include "Command.h"


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

    static void SendToInterface(uint8 *trans);
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
};
