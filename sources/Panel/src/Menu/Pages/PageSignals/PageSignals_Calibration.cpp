#include "stdafx.h"
#ifndef WIN32
#include "Menu/MenuItems.h"
#include "Menu/Pages/Include/PageSignals.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pageCalibration;
Page *PageSignals::PageCalibration::pointer = (Page *)&pageCalibration;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_4( pageCalibration,
    "����������", "CALIBRATION",
    "", "",
    0,      ///< ��������� �������� - ���������� - ����� +5�
    0,      ///< ��������� �������� - ���������� - ����� 0�
    0,      ///< ��������� �������� - ���������� - ����� -5�
    0,      ///< ��������� �������� - ���������� - ����� ������
    Page::Settings_Calibration, PageSignals::pointer, FuncActive, FuncPress, FuncOnKey, FuncDrawPage
)
