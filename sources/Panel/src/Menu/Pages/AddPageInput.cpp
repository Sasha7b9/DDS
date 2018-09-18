#include "Display/InputWindow.h"
#include "Display/Painter.h"
#include "Display/Symbols.h"
#include "Display/Text.h"
#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "Settings/Settings.h"
#include "AddPageInput.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pInput;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Draw_Left(int x, int y)
{
    Font::Set(Font::Type::_UGO2);
    Text::Draw4SymbolsInRect(x + 3, y + 3, SYMBOL_LEFT);
    Font::Set(Font::Type::_8);
}

DEF_SMALL_BUTTON(sbLeft,                                                                                           //--- ���� ����� - ������ ����� ---
    "������ �����", "SYMBOL LEFT",
    "����������� ������ �����",
    "Move the cursor to the left",
    pInput, FuncActive, InputWindow::KeyLeft, Draw_Left
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Draw_Right(int x, int y)
{
    Font::Set(Font::Type::_UGO2);
    Text::Draw4SymbolsInRect(x + 3, y + 3, SYMBOL_RIGHT);
    Font::Set(Font::Type::_8);
}

DEF_SMALL_BUTTON(sbRight,                                                                                         //--- ���� ����� - ������ ������ ---
    "������ ������", "SYMBOL RIGHT",
    "����������� ������ ������",
    "Move the cursor to the right",
    pInput, FuncActive, InputWindow::KeyRight, Draw_Right
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Cancel()
{
    Menu::ResetAdditionPage();
}

static void Draw_Cancel(int x, int y)
{
    Font::Set(Font::Type::_UGO2);
    Text::Draw4SymbolsInRect(x + 3, y + 3, SYMBOL_DELETE);
    Font::Set(Font::Type::_8);
}

DEF_SMALL_BUTTON(sbCancel,                                                                                               //--- ���� ����� - ������ ---
    "������� ���������", "UNITS",
    "���������� �� ����� ������ ��������",
    "Unsubscribe from the new value",
    pInput, FuncActive, OnPress_Cancel, Draw_Cancel
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Draw_Enter(int x, int y)
{
    Font::Set(Font::Type::_UGO2);
    Text::Draw4SymbolsInRect(x + 4, y + 3, SYMBOL_SAVE);
    Font::Set(Font::Type::_8);
}

DEF_SMALL_BUTTON(sbEnter,                                                                                                  //--- ���� ����� - ���� ---
    "����", "ENTER",
    "����������� ���� ������ ��������",
    "Confirm the new value",
    pInput, FuncActive, InputWindow::KeyEnter, Draw_Enter
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnRotate_Reg(int)
{

}

Page *AddPageInput::pointer = (Page *)&pInput;

DEF_PAGE_SB( pInput,
    "���� ��������", "VALUE ENTRY",
    "",
    "",
    &sbLeft,     ///< ���� ����� - ������ �����
    &sbRight,    ///< ���� ����� - ������ ������
    &sbCancel,   ///< ���� ����� - ������
    &sbEnter,    ///< ���� ����� - ����
    0,
    0,
    Page::SB_Input, 0, FuncActive, FuncPress, FuncDrawPage, OnRotate_Reg
)
