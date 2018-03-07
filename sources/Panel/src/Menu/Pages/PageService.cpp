#pragma once
#include "Display/Colors.h"
#include "Display/Display.h"
#include "Settings/Settings.h"
#include "PageService.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pService;
Page *PageService::pointer = (Page *)&pService;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2( cService_Language,                                                                                               //--- ������ - ���� ---
    "����", "LANGUAGE",
    "����� ����� ����",
    "Selecting the menu language",
    "�������",    "RUSSIAN",
    "����������", "ENGLISH",
    LANG, pService, FuncActive, FuncChangedChoice, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnChanged_Background(bool)
{
    Color::InitGlobalColors();
}

DEF_CHOICE_2( cService_Background,                                                                                        //--- ������ - ���� ���� ---
    "���� ����", "BACKGROUND",
    "����� ����� ����",
    "Select background color",
    "�����",  "WHITE",
    "ר����", "BLACK",
    BACKGROUND_BLACK, pService, FuncActive, OnChanged_Background, FuncDraw
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_2( pService,                                                                                                                 //--- ������ ---
    "������", "SERVICE",
    "��������� �������",
    "Service functions",
    cService_Language,   ///< ������ - ����
    cService_Background, ///< ������ - ���� ����
    Page_Service, 0, FuncActive, FuncPress
)
