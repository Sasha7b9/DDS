#include "PageRegisters.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Wave.h"
#include "Menu/Menu.h"
#include "Command.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pRegisters;
Page *PageRegisters::pointer = (Page *)&pRegisters;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PageRegisters::Draw()
{
    if(Menu::CurrentPage() != pointer)
    {
        return;
    }

    Painter::FillRegion(Wave::X(), Wave::Y(A) + 1, Wave::Width() - 1, Wave::Height() * 2, Color::BACK);

    DrawRegisters(Wave::X() + 2, Wave::Y(A) + 3);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageRegisters::DrawRegisters(int x, int y)
{
    for(uint8 i = 0; i < NumRegisters; i++)
    {
        Register reg(i);
        Text::DrawText(x, y + i * 10, reg.Name(), Color::FILL);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Prev()
{
}

DEF_BUTTON( bPrev,                                                                                                     //--- �������� - ���������� ---
    "����������", "Previous",
    "������� � ����������� ��������",
    "Go to the previous register",
    pRegisters, FuncActive, OnPress_Prev, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Next()
{
}

DEF_BUTTON(bNext,                                                                                                       //--- �������� - ��������� ---
    "���������", "Next",
    "������� � ���������� ��������",
    "Go to the next register",
    pRegisters, FuncActive, OnPress_Next, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Send()
{
}

DEF_BUTTON(bSend,                                                                                                         //--- �������� - ������� ---
    "�������", "Send",
    "��������� ���� ����� �������� ��������",
    "Opens the register value entry window",
    pRegisters, FuncActive, OnPress_Send, FuncDraw
)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_3(pRegisters,
    "��������", "REGISTERS",
    "",
    "",
    bPrev,
    bNext,
    bSend,
    Page_Registers, 0, FuncActive, FuncPress
)
