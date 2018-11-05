#include "stdafx.h"
#ifndef WIN32
#include "Include/PageSignals.h"
#include "Display/Painter.h"
#include "FDrive/FDrivePanel.h"
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pLoad;
Page *PageSignals::PageLoad::pointer = (Page *)&pLoad;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Up()
{

}

DEF_BUTTON( bUp,                                                                                            ///< ��������� �������� - �������� - �����
    "�����", "����",
    "", "",
    pLoad, FuncActive, OnPress_Up, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Down()
{
}

DEF_BUTTON( bDown,                                                                                           ///< ��������� �������� - �������� - ����
    "����", "Down",
    "", "",
    pLoad, FuncActive, OnPress_Down, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Enter()
{
}

DEF_BUTTON(bEnter,                                                                                          ///< ��������� �������� - �������� - Enter
    "Enter", "Enter",
    "", "",
    pLoad, FuncActive, OnPress_Enter, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Choose()
{
}

DEF_BUTTON(bChoose,                                                                                    ///< ��������� �������� - �������� - ����������
    "�������", "Choose",
    "", "",
    pLoad, FuncActive, OnPress_Choose, FuncDraw
)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool OnKey(Control)
{
    return false;
}

DEF_PAGE_4( pLoad,                                                                                                  ///< ��������� �������� - ��������
    "��������", "LOAD",
    "", "",
    &bUp,       ///< ��������� �������� - �������� - �����
    &bDown,     ///< ��������� �������� - �������� - ����
    &bEnter,    ///< ��������� �������� - �������� - Enter
    &bChoose,   ///< ��������� �������� - �������� - ����������
    Page::Settings_Load, PageSignals::pointer, FuncActive, FuncPress, OnKey, FDrive::Graphics::Draw
)
