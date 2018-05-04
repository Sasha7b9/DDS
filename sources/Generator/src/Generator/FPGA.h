#pragma once
#include "defines.h"
#include "Command.h"
#include "GeneratorSettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FPGA_NUM_POINTS 1024


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FPGA
{
public:
    static void Init();

    static void SetWaveForm(WaveForm form);

    static void SetFrequency(Channel ch, float frequency);

    static void SetDuration(Channel ch, float duration);

    static void SetDelay(float delay);

private:
    enum ModeWorkFPGA
    {
        ModeNone,
        ModeDDS,
        ModeImpulse,    ///< �����, � ������� ������c� ����� ����� ������ �������
        ModeImpulse2    ///< �����, � ������� �������� ����� ���������� �������. ��� ���� ����� ������������ �������� ������� ������ ���. �������
    };

    static void GenerateSine();

    static void GenerateSaw();
    /// ���������� ���������� ����� ������
    static void SetModeImpulse();
    /// ������� ������������ ����� � ����
    static void SendData();
    /// �������� �������� � �������
    static void WriteRegister(uint8 reg, uint value);
    /// ���������� �� A0_RG...A3_RG �����, ������������� ��������
    static void WriteAddress(uint8 reg);

    static void WriteControlRegister();

    static uint8 RegisterForDuration(Channel ch);

    static ModeWorkFPGA modeWork;

    static uint16 dataA[FPGA_NUM_POINTS];   ///< ����� ������� ��� ������� � ����
    static uint16 dataB[FPGA_NUM_POINTS];
};
