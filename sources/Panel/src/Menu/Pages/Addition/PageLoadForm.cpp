#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "Menu/Menu.h"
#include "Menu/Pages/Addition/PageLoadForm.h"
#include "Menu/Pages/Include/PageSignals.h"
#include "Display/Painter.h"
#include "FDrive/FDrivePanel.h"
#endif



extern const PageBase pageLoad;
Page *PageLoadForm::pointer = reinterpret_cast<Page *>(const_cast<PageBase *>(&pageLoad));


DEF_BUTTON( bUp,                                                                                                                              //--- ��������� �������� - �������� - ����� ---
    "�����",
    "",
    pageLoad, Item::FuncActive, FDrive::PressUp, FuncDraw
)


DEF_BUTTON( bDown,                                                                                                                             //--- ��������� �������� - �������� - ���� ---
    "����",
    "",
    pageLoad, Item::FuncActive, FDrive::PressDown, FuncDraw
)


DEF_BUTTON( bEnter,                                                                                                                           //--- ��������� �������� - �������� - Enter ---
    "�����",
    "",
    pageLoad, Item::FuncActive, FuncPress, FuncDraw
)


static void OnPress_Choose()
{
    FDrive::PressChoose();
    PageSignals::OnPress_Form(true);
}

DEF_BUTTON( bChoose,                                                                                                                     //--- ��������� �������� - �������� - ���������� ---
    "�������",
    "",
    pageLoad, Item::FuncActive, OnPress_Choose, FuncDraw
)



static bool OnKey(KeyEvent &control)
{
    if (control.value == KeyEvent::RegLeft)
    {
        FDrive::PressDown();
        return true;
    }
    else if (control.value == KeyEvent::RegRight)
    {
        FDrive::PressUp();
        return true;
    }
    else if (control.Is(KeyEvent::Esc, KeyEvent::Action::Up))
    {
        Menu::ResetAdditionPage();
        return true;
    }
    else
    {
        // ����� ������
    }

    return false;
}

DEF_PAGE_4( pageLoad, //-V1027                                                                                                                        //--- ��������� �������� - �������� ---
    "�����",  //-V1027
    "�������� ������ ����� ������������� ������� ��� �������� � ������",
    &bChoose,   ///< ��������� �������� - �������� - ����������
    0,
    0,
    0,
    Page::Settings_Load, nullptr, Item::FuncActive, FuncPress, OnKey, FDrive::Draw
)
