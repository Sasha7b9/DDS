#pragma once
#include "Display/Painter.h"
#include "Display/Symbols.h"
#include "Menu/MenuItems.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//static const  SButton sbLeft;
static void     Draw_Left(int, int);
//static const  SButton sbRight;
static void     Draw_Right(int, int);
//static const  SButton sbCancel;
static void     OnPress_Cancel();
static void     Draw_Cancel(int, int);
//static const  SButton sbEnter;
static void     Draw_Enter(int, int);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ����� - ������ ����� -------------------------------------------------------------------------------------------------------------------------
static const SButton sbLeft =
{
    Item_SButton, InputWindow::KeyLeft,
    {
        (char *)"������ �����", (char *)"SYMBOL LEFT"
    },
    0,
    Draw_Left
};

static void Draw_Left(int x, int y)
{
    Painter::SetFont(TypeFont_UGO2);
    Painter::Draw4SymbolsInRect(x + 3, y + 3, SYMBOL_LEFT);
    Painter::SetFont(TypeFont_8);
}

// ���� ����� - ������ ������ ------------------------------------------------------------------------------------------------------------------------
static const SButton sbRight =
{
    Item_SButton, InputWindow::KeyRight,
    {
        "������ ������", "SYMBOL RIGHT"
    },
    0,
    Draw_Right
};

// ���� ����� - ������ -------------------------------------------------------------------------------------------------------------------------------
static uint8 units = 0;

static const SButton sbCancel =
{
    Item_SButton, OnPress_Cancel,
    {
        "������� ���������", "UNITS"
    },
    &units,
    Draw_Cancel
};

static void OnPress_Cancel(void)
{
    ADDITION_PAGE = 0;
}

static void Draw_Cancel(int x, int y)
{
    Painter::SetFont(TypeFont_UGO2);
    Painter::Draw4SymbolsInRect(x + 3, y + 3, SYMBOL_DELETE);
    Painter::SetFont(TypeFont_8);
}

// ���� ����� - ���� ---------------------------------------------------------------------------------------------------------------------------------
static const SButton sbEnter =
{
    Item_SButton, InputWindow::KeyEnter,
    {
        "����", "ENTER"
    },
		0,
    Draw_Enter
};

static void Draw_Enter(int x, int y)
{
    Painter::SetFont(TypeFont_UGO2);
    Painter::Draw4SymbolsInRect(x + 4, y + 3, SYMBOL_SAVE);
    Painter::SetFont(TypeFont_8);
}

Page pInput =
{
    Item_SB_Page, 0,
    {
        "���� ��������", "VALUE ENTRY"
    },
    {
        (void*)&sbLeft,       ///< ���� ����� - ������ �����
        (void*)&sbRight,      ///< ���� ����� - ������ ������
        (void*)&sbCancel,     ///< ���� ����� - ������
        (void*)&sbEnter       ///< ���� ����� - ����
    }
};

static void Draw_Right(int x, int y)
{
    Painter::SetFont(TypeFont_UGO2);
    Painter::Draw4SymbolsInRect(x + 3, y + 3, SYMBOL_RIGHT);
    Painter::SetFont(TypeFont_8);
}
