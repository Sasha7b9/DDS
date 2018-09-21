#pragma once
#include "Settings/SettingsTypes.h"
#include "Command.h"


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

    static void SetFormWave(Chan ch, Form form);

    static void SetParameter(Chan ch, Parameter *param);

    static void SetDebugMode(bool enable);

    static void LoadRegister(Register reg, uint64 value);

    static void TuneChannel(Chan ch);

    static void EmptyCommand();

private:
    /// ������� � ��������� ������
    static void SendToInterface(uint8 *buffer, uint16 size);

    static void SendToInterfaceNew(uint8 *buffer, uint16 size);

    static bool enabledCh[Chan::Number];
};

/** @}  @} */
