#pragma once
#include "Display/Display.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void        OnChanged_Background();


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ - ���� -------------------------------------------------------------------------------------------------------------------------------------
static const Choice cService_Language =
{
    Item_Choice, 0,
    {
        "����", "LANGUAGE"
    },
    {
        "�������", "RUSSIAN",
        "����������", "ENGLISH"
    },
    (uint8 *)&set.serv_language
};

// ������ - ���� ���� --------------------------------------------------------------------------------------------------------------------------------
static const Choice cService_Background =
{
    Item_Choice, OnChanged_Background,
    {
        "���� ����", "BACKGROUND"
    },
    {
        "�����",  "WHITE",
        "ר����", "BLACK"
    },
    (uint8 *)&set.serv_bacgroundBlack
};

static void OnChanged_Background(void)
{
    Display_SetColorBackground();
}

const Page pService =
{
    Item_Page, 0,
    {
        "������", "SERVICE"
    },
    {
        (void*)&cService_Language,      ///< ������ - ����
        (void*)&cService_Background     ///< ������ - ���� ����
    }
};
