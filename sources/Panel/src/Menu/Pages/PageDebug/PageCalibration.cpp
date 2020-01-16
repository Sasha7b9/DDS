#include "defines.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Menu/Pages/PageDebug/PageDebug.h"
#include "Menu/Pages/PageDebug/StructCalibration.h"
#include "Settings/Settings.h"
#include "Utils/StringUtils.h"


extern const PageBase pCalibration;


static uint8 channel = 0;
static uint8 signal = 0;
static uint8 parameter = 0;
static uint8 range = 0;

static int16 *k = nullptr;


void PageDebug::Calibartion::Init()
{
    k = StructCalibration::GetK(channel, signal, range, parameter);
}

/// ���������� ��� ��������� ������������ ���������
static void OnChange_Parameters(bool)
{

}


/// ���������� ��� ��������� ��������� ������
static void OnChange_Source(bool)
{
    k = StructCalibration::GetK(channel, signal, range, parameter);
    OnChange_Parameters(true);
}

DEF_CHOICE_3(cChannel,
    "�����",
    "",
    "A", "",
    "B", "",
    "", "",
    channel, pCalibration, Item::FuncActive, OnChange_Source, FuncDraw
)

DEF_CHOICE_3(cSignal,
    "������",
    "",
    "�����", "",
    "DDS", "",
    "", "",
    signal, pCalibration, Item::FuncActive, OnChange_Source, FuncDraw
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


static void DrawPage()
{
    Painter::FillRegion(10, 10, 100, 100, Color::WHITE);

    char buffer[30];

    SU::Int2String(*k, true, 1, buffer);

    Text::Draw(20, 20, buffer, Color::BLACK);
}


static bool FuncOnKeyPage(Key &key)
{
    if(key.IsRotate())
    {
        return true;
    }

    return false;
}


DEF_PAGE_6( pCalibration,
    "����������",
    "",
    &cChannel,
    &cSignal,
    &cRange,
    &cParameter,
    PageDebug::_Calibration::PageA::self, ///< ��������� �������� - ���������� A
    PageDebug::_Calibration::PageB::self, ///< ��������� �������� - ���������� B
    Page::Calibration, PageDebug::self, Item::FuncActive, FuncPress, FuncOnKeyPage, DrawPage
)

Page *PageDebug::Calibartion::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pCalibration));
