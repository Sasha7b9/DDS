#pragma once
#include "Menu/MenuItems.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_PAGES     9        ///< ���������� ������� � ����
#define PAGE_IS_MAIN  false
#define MENU_TEMP_ENABLE_STRING_NAVI()

extern const Page *pages[NUM_PAGES];


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
    static Item *OpenedItem();
    /// ���������� ����� �������� �������� ���� (�������, ��� �������, �������� �������, ������ �������� ���� ������ ���������
    static Item *CurrentItem();
    ///\brief  ����� �������� ����� �������� ����, ���������������� �������������� ������� [1..5], ���� ��� ��������� � ������ ���������, � 0, 
    /// ���� �� ���� ������ �� ������.
    static Item *itemUnderKey;
    /// ���������� ����� ������� ��������
    static Page* CurrentPage();
private:

    static void DrawTitle();

    static void DrawPagesUGO();

    static void ProcessControl(StructControl control);

    static Item *openedItem;
};
