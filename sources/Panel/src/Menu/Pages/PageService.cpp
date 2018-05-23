#pragma once
#include "Display/Colors.h"
#include "Display/Display.h"
#include "Generator.h"
#include "Hardware/Timer.h"
#include "Settings/Settings.h"
#include "PageService.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pService;
Page *PageService::pointer = (Page *)&pService;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Reset(void)
{
    Generator::Reset();
    Timer::PauseOnTime(100);
    Settings::Load(true);
}

DEF_BUTTON(bReset,                                                                                                           //--- ������� - ����� ---
           "�����", "RESET",
           "����� �������� �� �������� �� ���������",
           "Resetting settings to default values",
           pService, FuncActive, OnPress_Reset, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2( cService_Language,                                                                                               //--- ������ - ���� ---
    "����", "LANGUAGE",
    "����� ����� ����",
    "Selecting the menu language",
    "�������",    "RUSSIAN", "���� ���� - �������",
                             "Menu language - Russian",
    "����������", "ENGLISH", "���� ���� - ����������",
                             "Menu language - English",
    FLAG_2, LANG, pService, FuncActive, FuncChangedChoice, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
static void OnChanged_Background(bool)
{
    Color::InitGlobalColors();
}

DEF_CHOICE_2( cService_Background,                                                                                        //--- ������ - ���� ���� ---
    "���� ����", "BACKGROUND",
    "����� ����� ����",
    "Select background color",
    "�����",  "WHITE", "���� ���� - �����",
                       "Background color - white",
    "ר����", "BLACK", "���� ���� - ������",
                       "Background color - black",
    BACKGROUND_BLACK, pService, FuncActive, OnChanged_Background, FuncDraw
)
*/


//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_2( pService,                                                                                                                 //--- ������ ---
    "������", "SERVICE",
    "��������� �������",
    "Service functions",
    bReset,
    cService_Language,   ///< ������ - ����
    //cService_Background, ///< ������ - ���� ����
    Page_Service, 0, FuncActive, FuncPress
)
