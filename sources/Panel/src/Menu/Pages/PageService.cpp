#include "stdafx.h"
#ifndef WIN32
#include "Display/Colors.h"
#include "Display/Display.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Generator/GeneratorPanel.h"
#include "Hardware/Timer.h"
#include "Settings/Settings.h"
#include "PageService.h"
#include "Menu/Menu.h"
#include "Utils/StringUtils.h"
#include "Utils/NumberBuffer.h"
#include "Utils/Math.h"
#include "Display/Symbols.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pUSB;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pService;
Page *PageService::pointer = (Page *)&pService;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Reset()
{
    Generator::Reset();
    Timer::PauseOnTime(100);
    set.Load(true);
}

DEF_BUTTON(bReset,                                                                                                           //--- ������� - ����� ---
    "�����", "RESET",
    "����� �������� �� �������� �� ���������",
    "Resetting settings to default values",
    pService, Item::FuncActive, OnPress_Reset, FuncDraw
)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2(cSizeByte,                                                                                                   //--- USB - ������ ����� ---
    "������ �����", "SIZE BYTE",
    "", "",
    "7 ���", "7 bits", "7 ��� � �����",
    "7 bits in byte",
    "8 ���", "8 bits", "8 ��� � �����",
    "8 bits in byte",
    FLAG_1, BIT_SIZE_BYTE, pUSB, Item::FuncActive, FuncChangedChoice, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cStopBit,                                                                                                        //--- USB - ����-��� ---
    "����-���", "STOP-BIT",
    "", "",
    "1", "1", "1 ����-��� � ����� �����",
    "1 stop bit at the end of the byte",
    "2", "2", "2 ����-���� � ����� �����",
    "2 stop bits at the end of the byte",
    FLAG_1, BIT_STOP_BIT, pUSB, Item::FuncActive, FuncChangedChoice, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cParity,                                                                                                         //--- USB - ר������ ---
    "ר������", "PARITY",
    "", "",
    "���������", "VERIFY", "�������� �������� ��������",
    "Parity check enabled",
    "�� ���������", "NOT VERIFY", "�������� �������� ���������",
    "Parity check off",
    FLAG_1, BIT_PARITY, pUSB, Item::FuncActive, FuncChangedChoice, FuncDraw
)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_3(pUSB,                                                                                                                         //--- USB --- //-V641 //-V1027
    "USB", "USB",
    "��������� ���������� ����� �� ���������� USB",
    "Communication parameters settings on the USB interface",
    cSizeByte,              ///< USB - ������ �����
    cStopBit,               ///< USB - ����-���
    cParity,                ///< USB - ר������
    Page::USB, &pService, Item::FuncActive, FuncPress, FuncOnKey
)



extern const PageBase pDebug;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_3( pService,                                                                                                                 //--- ������ --- //-V641 //-V1027
    "������", "SERVICE",
    "��������� �������",
    "Service functions",
    bReset,
    pUSB,
    pDebug,
    Page::Service, Menu::mainPage, Item::FuncActive, FuncPress, FuncOnKey
)
