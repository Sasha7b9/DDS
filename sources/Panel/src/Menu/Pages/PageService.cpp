#include "Display/Colors.h"
#include "Display/Display.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Generator/Generator_p.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"
#include "Settings/Settings.h"
#include "Settings/CalibrationSettings.h"
#include "PageService.h"
#include "Menu/Menu.h"
#include "Utils/StringUtils.h"
#include "Utils/NumberBuffer.h"
#include "Utils/Math.h"
#include "Display/Symbols.h"


extern const PageBase pUSB;



extern const PageBase pService;
Page *PageService::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pService));


static void OnPress_Reset()
{
    PGenerator::Reset();
    HAL_TIM::Delay(100);
    setCal.Load();
    set.Load(true);
}

DEF_BUTTON( bReset,                                                                                                                                                 //--- ������� - ����� ---
    "�����",
    "����� �������� �� �������� �� ���������",
    pService, Item::FuncActive, OnPress_Reset, FuncDraw
)


DEF_CHOICE_2( cSizeByte,                                                                                                                                         //--- USB - ������ ����� ---
    "������ �����",
    ""
    ,
    "7 ���", "7 ��� � �����",
    "8 ���", "8 ��� � �����",
    FLAG, BIT_SIZE_BYTE, pUSB, Item::FuncActive, FuncChangedChoice, FuncDraw
)


DEF_CHOICE_2( cStopBit,                                                                                                                                              //--- USB - ����-��� ---
    "����-���",
    ""
    ,
    "1", "1 ����-��� � ����� �����",
    "2", "2 ����-���� � ����� �����",
    FLAG, BIT_STOP_BIT, pUSB, Item::FuncActive, FuncChangedChoice, FuncDraw
)


DEF_CHOICE_2( cParity,                                                                                                                                               //--- USB - ר������ ---
    "ר������",
    ""
    ,
    "���������",    "�������� �������� ��������",
    "�� ���������", "�������� �������� ���������",
    FLAG, BIT_PARITY, pUSB, Item::FuncActive, FuncChangedChoice, FuncDraw
)


DEF_PAGE_3( pUSB,                                                                                                                                                               //--- USB ---
    "USB", 
    "��������� ���������� ����� �� ���������� USB",
    &cSizeByte,              ///< USB - ������ �����
    &cStopBit,               ///< USB - ����-���
    &cParity,                ///< USB - ר������
    Page::USB, &pService, Item::FuncActive, FuncPress, FuncOnKey, Page::FuncDraw
)



extern const PageBase pDebug;


DEF_PAGE_3( pService,                                                                                                                                                        //--- ������ --- //-V641
    "������",   
    "��������� �������",
    &bReset,
    &pUSB,
    &pDebug,
    Page::Service, Menu::mainPage, Item::FuncActive, FuncPress, FuncOnKey, Page::FuncDraw
)
