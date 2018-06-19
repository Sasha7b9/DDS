#pragma once
#include "Command.h"
#include "defines.h"
#include "GeneratorSettingsTypes.h"
#include "Hardware/CPU.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AD5697
{
public:

    static void Init();

    static void SetAmplitude(Channel ch, float amplitude);

    static void SetOffset(Channel ch, float offset);

private:

    static void Reset(Channel ch);
    /// ������ ��������������� � DAC
    static void TransmitI2C(uint8 address, uint8 data[3]);

    static void WriteParameter(Channel ch, Type_WaveParameter param, float value_);
    /// �������� ��� ����� ������ �� ������� ������
    static void WriteParameter(uint8 address, uint8 data[3], GeneratorPin pin);

    static GeneratorPin PinLDAC(Channel ch);

    static uint8 CreateCommandByte(Type_WaveParameter param);
};
