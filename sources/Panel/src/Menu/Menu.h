#pragma once
#include "Menu/MenuItems.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Menu
{
public:

    static const int NUM_ITEMS_ON_PAGE = 4;

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
    static int DrawTitle();

    static void DrawPagesUGO(int x);

    static void ProcessControl(Control control);
    /// ���� �����-�� ���� �������, �� ����� ��� �����
    static Item *openedItem_;
};
