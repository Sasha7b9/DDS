#include "Display/InputWindow.h"
#include "Display/Painter.h"
#include "Display/Symbols.h"
#include "Display/Text.h"
#include "Menu/MenuItems.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pInput;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Draw_Left(int x, int y)
{
    Text::SetFont(TypeFont_UGO2);
    Text::Draw4SymbolsInRect(x + 3, y + 3, SYMBOL_LEFT);
    Text::SetFont(TypeFont_8);
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
    Text::SetFont(TypeFont_UGO2);
    Text::Draw4SymbolsInRect(x + 3, y + 3, SYMBOL_RIGHT);
    Text::SetFont(TypeFont_8);
}

DEF_SMALL_BUTTON(sbRight,                                                                                         //--- ���� ����� - ������ ������ ---
    "������ ������", "SYMBOL RIGHT",
    "����������� ������ ������",
    "Move the cursor to the right",
    pInput, FuncActive, InputWindow::KeyRight, Draw_Right
)


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Cancel(void)
{
    ADDITION_PAGE = 0;
}

static void Draw_Cancel(int x, int y)
{
    Text::SetFont(TypeFont_UGO2);
    Text::Draw4SymbolsInRect(x + 3, y + 3, SYMBOL_DELETE);
    Text::SetFont(TypeFont_8);
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
    Text::SetFont(TypeFont_UGO2);
    Text::Draw4SymbolsInRect(x + 4, y + 3, SYMBOL_SAVE);
    Text::SetFont(TypeFont_8);
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
    PageSB_Input, 0, FuncActive, FuncPress, FuncDrawPage, OnRotate_Reg
)
