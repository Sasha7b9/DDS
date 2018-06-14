#pragma once
#include "GeneratorSettingsTypes.h"
#include "Command.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Multiplexor
{
public:
    /// �������������� �������������
    static void Init();
    /// �������������� ������������� � ������������ � ������ ���������������� ������� �� ������ ������
    static void SetMode(Channel ch, Type_WaveForm form);

private:
    static void SetPin(uint16 pin);
    static void ResetPin(uint16 pin);
};
