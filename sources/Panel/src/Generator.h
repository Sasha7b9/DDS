#pragma once
#include "Settings/SettingsTypes.h"


/** @addtogroup Panel
 *  @{
 *  @defgroup Interface
 *  @{
 */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Generator
{
public:
    static void Reset();
    /// ��� ������� ���������� � ����� ��� ����� ��������� �� �������
    static void Update();

    static void EnableChannel(Channel ch, bool enable);

    static void SetFormWave(Channel ch, WaveForm form);

    static void SetParameter(Channel ch, WaveParameter param, float value);

    static void SetDebugMode(bool enable);

    static void LoadRegister(Register reg, uint value);

private:
    /// ������� � ��������� ������
    static void SendToInterface(uint8 *buffer, int size);
    /// ������ � ��������� ������ �� ����������
    static void ReadAndRunFromInterface();

    static void MasterSynchro();

    static void ExecuteCommand(uint8 *buffer, int size);
};

/** @}  @} */
