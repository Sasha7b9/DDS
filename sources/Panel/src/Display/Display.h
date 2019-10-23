#pragma once
#include "DisplayTypes.h"
#include "defines.h"
#include "Hardware/Controls.h"
#include "Settings/SettingsTypes.h"




#define DISPLAY_SHOW_WARNING(warn)

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240

#define BUFFER_WIDTH    SCREEN_WIDTH    /* ������ ������ ��� ��������� */
#define BUFFER_HEIGHT   SCREEN_HEIGHT   /* ������ ������ ��� ��������� */


namespace Display
{
    void Init();

    void Update();

    uint8 *GetBuffer();
    /// �����
    extern uint8 frontBuffer[BUFFER_WIDTH * BUFFER_HEIGHT];
    /// ������ �����. � �� ���������� ���������, � ����� ����������� ���������� �� frontBuffer
    extern uint8 backBuffer[BUFFER_WIDTH * BUFFER_HEIGHT];
};
