#include "Display/Painter.h"
#include "Display/Symbols.h"
#include "Display/Text.h"
#include "Generator/Signals.h"
#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "Settings/Settings.h"
#include "PageInput.h"


extern const PageBase pInput;



static void Draw_Left(int, int)
{
}

static void OnPress_OrderUp()
{

}

DEF_SMALL_BUTTON(sbOrderUp,                                                                                                                               //--- ���� ����� - ������ ����� ---
    "������� ������",
    "��������� ������� ������� ���������",
    pInput, Item::FuncActive, OnPress_OrderUp, Draw_Left
)


static void Draw_Right(int, int)
{
}

static void OnPress_OrderDown()
{

}

DEF_SMALL_BUTTON(sbOrderDown,                                                                                                                            //--- ���� ����� - ������ ������ ---
    "������� �������",
    "��������� ������� ������� ���������",
    pInput, Item::FuncActive, OnPress_OrderDown, Draw_Right
)



static void OnPress_Cancel()
{
    Menu::ResetAdditionPage();
}

static void Draw_Cancel(int x, int y)
{
    String("��������").Draw(x + 13, y + 12);
    Text::Draw4SymbolsInRect(x + 25, y + 28, Ideograph::_8::Delete);
}

DEF_SMALL_BUTTON(sbCancel,                                                                                                                                      //--- ���� ����� - ������ ---
    "������� ���������",
    "���������� �� ����� ������ ��������",
    pInput, Item::FuncActive, OnPress_Cancel, Draw_Cancel
)


static void Draw_Enter(int x, int y)
{
    String("�����������").Draw(x + 3, y + 12);
    Text::Draw4SymbolsInRect(x + 25, y + 28, Ideograph::_8::Save);
}

static void OnPress_Enter()
{

}

DEF_SMALL_BUTTON(sbEnter,                                                                                                                                         //--- ���� ����� - ���� ---
    "����",
    "����������� ���� ������ ��������",
    pInput, Item::FuncActive, OnPress_Enter, Draw_Enter
)


static bool OnControl(Key &)
{
    return false;
}

Page *PageInput::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pInput));

DEF_PAGE_SB( pInput,   //-V641
    "���� ��������",   
    "",
    &sbOrderUp,         ///< ���� ����� - ������ �����
    &sbOrderDown,       ///< ���� ����� - ������ ������
    &sbCancel,          ///< ���� ����� - ������
    &sbEnter,           ///< ���� ����� - ����
    nullptr,
    nullptr,
    Page::SB_Input, 0, Item::FuncActive, FuncPress, Page::FuncDraw, OnControl
)
