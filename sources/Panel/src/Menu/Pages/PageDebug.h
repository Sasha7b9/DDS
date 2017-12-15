#pragma once
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void  OnPress_SaveSettings();
static void  OnPress_Reset();


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������� - ������� ---------------------------------------------------------------------------------------------------------------------------------
static const Choice cConsole =
{
    Item_Choice, 0,
    {
        "�������", "CONSOLE"
    },
    {
        DISABLED_RU, DISABLED_EN,
        ENABLED_RU, ENABLED_EN
    },
    (uint8*)&CONSOLE_ENABLED
};

static void OnPress_DebugMode()
{
    Generator_SetDebugMode(DEBUG_MODE_ENABLED);
}

// ������� - ��������� ��������� ---------------------------------------------------------------------------------------------------------------------
static const Button bSaveSettings =
{
    Item_Button, OnPress_SaveSettings,
    {
        "��������� ���������", "SAVE SETTINGS"
    }
};

static void OnPress_SaveSettings(void)
{
    Settings_Save();
}

// ������� - ����� -----------------------------------------------------------------------------------------------------------------------------------
static const Button bReset =
{
    Item_Button, OnPress_Reset,
    {
        "�����", "RESET"
    }
};

static void OnPress_Reset(void)
{
    Generator_Reset();
    uint time = HAL_GetTick();
    while (HAL_GetTick() - time < 100) {};
    Settings_Load();
}

const Page pDebug =
{
    Item_Page, 0,
    {
        "�������", "DEBUG"
    },
    {
        (void *)&cConsole,      ///< ������� - �������
        (void *)&bSaveSettings, ///< ������� - ��������� ���������
        (void *)&bReset         ///< ������� - �����
    }
};

// ������� - ����� -----------------------------------------------------------------------------------------------------------------------------------
static const Choice cDebugMode =
{
    Item_Choice, OnPress_DebugMode,
    {
        "�����", "MODE"
    },
    {
        "����������", "NORMAL",
        "����������", "DEBUG"
    },
    (uint8 *)&DEBUG_MODE_ENABLED
};
