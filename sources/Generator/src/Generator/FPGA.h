#pragma once
#include "defines.h"
#include "../../Common/Command.h"
#include "GeneratorSettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FPGA_NUM_POINTS 1024


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FPGA
{
public:
    FPGA();

    void Init();

    void SetWaveForm(WaveForm form);

    void SetFrequency(Channel ch, float frequency);

    void SetDuration(Channel ch, float duration);

    void SetDelay(float delay);

private:
    typedef enum
    {
        ModeNone,
        ModeDDS,
        ModeImpulse,    ///< �����, � ������� ������c� ����� ����� ������ �������
        ModeImpulse2    ///< �����, � ������� �������� ����� ���������� �������. ��� ���� ����� ������������ �������� ������� ������ ���. �������
    } ModeWorkFPGA;

    void GenerateSine();

    void GenerateSaw();
    /// ���������� ���������� ����� ������
    void SetModeImpulse();
    /// ������� ������������ ����� � ����
    void SendData();
    /// �������� �������� � �������
    void WriteRegister(uint8 reg, uint value);
    /// ���������� �� A0_RG...A3_RG �����, ������������� ��������
    void WriteAddress(uint8 reg);

    void WriteControlRegister();

    uint8 RegisterForDuration(Channel ch);

    ModeWorkFPGA modeWork;

    uint16 dataA[FPGA_NUM_POINTS];   ///< ����� ������� ��� ������� � ����
    uint16 dataB[FPGA_NUM_POINTS];
};
