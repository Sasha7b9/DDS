#pragma once
#include "PageSignals2.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pSignals2;
Page *PageSignals2::pointer = (Page *)&pSignals2;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2( cTypeTune,                                                                                      //--- ��������� �������� 2 - ������� ---
    "�������", "SENDING",
    "���������� ������������� ������� �������� �������� � ���������� ����������",
    "Specifies the frequency of sending signal settings to the control device",
    "����������", "SINGLE",
    "����������", "CONTINUOUSLY",
    set.sig_tuneFull, pSignals2, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_1( pSignals2,                                                                                                  //--- ��������� �������� 2 ---
    "��������� �������� 2", "SIGNAL SETTINGS 2",
    "",
    "",
    cTypeTune,                                      ///< ��������� �������� 2 - �������
    Page_Settings2, 0, FuncActive, FuncPress
)
