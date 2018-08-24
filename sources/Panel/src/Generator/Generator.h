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

    static void EnableChannel(Chan ch, bool enable);

    static bool ChannelEnabled(Chan ch);

    static void SetFormWave(Chan ch, WaveForm form);

    static void SetParameter(Chan ch, WaveParameter param, float value);

    static void SetDebugMode(bool enable);

    static void LoadRegister(Register reg, uint value);

private:
    /// ������� � ��������� ������
    static void SendToInterface(uint8 *buffer, int size);

    static void ExecuteCommand(uint8 *buffer, int size);

    static bool enabledCh[Chan::Number];
};

/** @}  @} */
