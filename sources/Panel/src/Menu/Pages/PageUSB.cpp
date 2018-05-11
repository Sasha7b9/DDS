#include "PageUSB.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pUSB;
Page *PageUSB::pointer = (Page *)&pUSB;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2(cSizeByte,
   "������ �����", "SIZE BYTE",
   "", "",
   "7 ���", "7 bits",
   "8 ���", "8 bits",
   SIZE_BYTE, pUSB, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_1(pUSB,
    "USB", "USB",
    "��������� ���������� ����� �� ���������� USB",
    "Communication parameters settings on the USB interface",
    cSizeByte,
    Page_USB, 0, FuncActive, FuncPress
)
