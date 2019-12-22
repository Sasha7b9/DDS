#include "defines.h"
#include "log.h"
#include "Menu/Menu.h"
#include "Menu/Pages/Addition/PageLoadForm.h"
#include "Menu/Pages/Include/PageSignals.h"
#include "Display/Painter.h"
#include "FDrive/FDrive_p.h"


extern const PageBase pageLoad;
Page *PageLoadForm::pointer = reinterpret_cast<Page *>(const_cast<PageBase *>(&pageLoad));


DEF_BUTTON( bUp,                                                                                                                              //--- ��������� �������� - �������� - ����� ---
    "�����",
    "",
    pageLoad, Item::FuncActive, FDrive::PressUp, FuncDraw
)

volatile const ButtonBase *pbUp = &bUp;


DEF_BUTTON( bDown,                                                                                                                             //--- ��������� �������� - �������� - ���� ---
    "����",
    "",
    pageLoad, Item::FuncActive, FDrive::PressDown, FuncDraw
)

volatile const ButtonBase *pbDown = &bDown;


DEF_BUTTON( bEnter,                                                                                                                           //--- ��������� �������� - �������� - Enter ---
    "�����",
    "",
    pageLoad, Item::FuncActive, FuncPress, FuncDraw
)

volatile const ButtonBase *pbEnter = &bEnter;


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



static bool OnKey(Key &control)
{
    if (control.value == Key::RegLeft)
    {
        FDrive::PressDown();
        return true;
    }
    else if (control.value == Key::RegRight)
    {
        FDrive::PressUp();
        return true;
    }
    else if (control.Is(Key::Esc, Key::Action::Up))
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

DEF_PAGE_4( pageLoad,                                                                                                                                 //--- ��������� �������� - �������� --- //-V641
    "�����",  
    "�������� ������ ����� ������������� ������� ��� �������� � ������",
    &bChoose,   ///< ��������� �������� - �������� - ����������
    0,
    0,
    0,
    Page::Settings_Load, nullptr, Item::FuncActive, FuncPress, OnKey, FDrive::Draw
)
