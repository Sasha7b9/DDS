#pragma once
#include "Menu/MenuItems.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_PAGES     4        ///< ���������� ������� � ����
#define PAGE_IS_MAIN  false
#define MENU_TEMP_ENABLE_STRING_NAVI()

extern const Page *menu[NUM_PAGES];

class Menu
{
public:
        
    static void Init();

    static void Update();

    static void Draw();
    /// ���������� true, ���� ����� ��������� �������������� ������� ����
    static bool RegIsControlPages();

    static const char *NameCurrentParameter();
    /// ���������� ����� ��������� �������� ����
    static Control *OpenedItem();
    /// ���������� ����� �������� �������� ���� (�������, ��� �������, �������� �������, ������ �������� ���� ������ ���������
    static Control *CurrentItem();
    ///\brief  ����� �������� ����� �������� ����, ���������������� �������������� ������� [1..5], ���� ��� ��������� � ������ ���������, � 0, 
    /// ���� �� ���� ������ �� ������.
    static Control *itemUnderKey;

    static void SetItemForHint(void *item);

private:

    static void DrawTitle();

    static void DrawPagesUGO();

    static void ProcessControl(StructControl control);
};
