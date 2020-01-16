#include "defines.h"
#include "Menu/Pages/PageDebug/PageDebug.h"


extern const PageBase pCalibration;


static uint flag = 0;
#define FLAG_K flag
#define B_CHANNEL   0
#define B_SIGNAL    1
#define B_PARAMETER 2

static uint8 parameter = 0;
static uint8 range = 0;


/// ���������� ��� ��������� ���������� ����������
static void OnChange_Parameters(bool)
{

}


DEF_CHOICE_2(cChannel,
    "�����",
    "",
    "A", "",
    "B", "",
    FLAG_K, B_CHANNEL, pCalibration, Item::FuncActive, OnChange_Parameters, FuncDraw
)

DEF_CHOICE_2(cSignal,
    "������",
    "",
    "�����", "",
    "DDS", "",
    FLAG_K, B_SIGNAL, pCalibration, Item::FuncActive, OnChange_Parameters, FuncDraw
)

DEF_CHOICE_6(cRange,
    "��������",
    "",
    "30 ��", "",
    "100 ��", "",
    "300 ��", "",
    "1 �", "",
    "3 �", "",
    "10 �", "",
    range, pCalibration, Item::FuncActive, OnChange_Parameters, FuncDraw
)

DEF_CHOICE_4(cParameter,
    "��������",
    "",
    "���������", "",
    "+5�", "",
    "0�", "",
    "-5�", "",
    parameter, pCalibration, Item::FuncActive, OnChange_Parameters, FuncDraw
)


DEF_PAGE_6( pCalibration,
    "����������",
    "",
    &cChannel,
    &cSignal,
    &cRange,
    &cParameter,
    PageDebug::_Calibration::PageA::self, ///< ��������� �������� - ���������� A
    PageDebug::_Calibration::PageB::self, ///< ��������� �������� - ���������� B
    Page::Calibration, PageDebug::self, Item::FuncActive, FuncPress, FuncOnKey, Page::FuncDraw
)

Page *PageDebug::Calibartion::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pCalibration));
