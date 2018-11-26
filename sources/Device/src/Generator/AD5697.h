#pragma once
#include "Command.h"
#include "defines.h"
#include "GeneratorSettingsTypes.h"
#include "Hardware/CPU.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AD5697
{
public:

    static void Init();

    static void SetOffset(Chan::E ch, ParamValue offset);

    static void SetFreqLevel(float level);

    static void SetFreqHysteresys(float hyst);

private:

    static void Reset(Chan::E ch);
    /// ������ ��������������� � DAC
    static void TransmitI2C(uint8 address, uint8 data[3]);

    //static void WriteParameter(Chan ch, ParameterValue param, float value_);
    /// �������� ��� ����� ������ �� ������� ������
    static void WriteParameter(uint8 address, uint8 data[3], GeneratorWritePin pin);

    static GeneratorWritePin PinLDAC(Chan::E ch);

    static uint8 CreateCommandByte(ParameterValue param);
};
