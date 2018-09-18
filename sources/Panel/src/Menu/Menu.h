#pragma once
#include "Menu/MenuItems.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_PAGES     3        ///< ���������� ������� � ����
#define PAGE_IS_MAIN  false
#define MENU_TEMP_ENABLE_STRING_NAVI()


class Menu
{
public:

    static void Init();
        
    static void Update();

    static void Draw();
    /// ���������� true, ���� ����� ��������� �������������� ���������� ����
    static bool RegIsControlSubPages();
    /// ���������� ����� ��������� �������� ����
    static Item *GetOpenedItem();

    static void SetOpenedItem(Item *item);
    /// ���������� ����� �������� �������� ���� (�������, ��� �������, �������� �������, ������ �������� ���� ������ ���������
    static Item *CurrentItem();
    ///\brief  ����� �������� ����� �������� ����, ���������������� �������������� ������� [1..5], ���� ��� ��������� � ������ ���������, � 0, 
    /// ���� �� ���� ������ �� ������.
    static Item *itemUnderKey;
    /// ���������� ������� �������� �� ��������. ������ ���� �������� ����������� �������� ����. ����� -1
    static int GetPosition(Page *page);
    /// ��������� �� ������� ��������
    static Page *mainPage;
private:
    /// ���������� �����
    static void DrawTitle();

    static void DrawPagesUGO();

    static void ProcessControl(Control control);
    /// ���� �����-�� ���� �������, �� ����� ��� �����
    static Item *openedItem_;
};
