#include "PageUSB.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pUSB;
Page *PageUSB::pointer = (Page *)&pUSB;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_CHOICE_2(cSizeByte,                                                                                                   //--- USB - ������ ����� ---
   "������ �����", "SIZE BYTE",
   "", "",
   "7 ���", "7 bits", "7 ��� � �����",
                      "7 bits in byte",
   "8 ���", "8 bits", "8 ��� � �����",
                      "8 bits in byte",
   FLAG_2, BIT_SIZE_BYTE, pUSB, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cStopBit,                                                                                                        //--- USB - ����-��� ---
    "����-���", "STOP-BIT",
    "", "",
    "1", "1", "1 ����-��� � ����� �����",
              "1 stop bit at the end of the byte",
    "2", "2", "2 ����-���� � ����� �����",
              "2 stop bits at the end of the byte",
    FLAG_2, BIT_STOP_BIT, pUSB, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_CHOICE_2(cParity,                                                                                                         //--- USB - ר������ ---
    "ר������", "PARITY",
    "", "",
    "���������", "VERIFY",        "�������� �������� ��������",
                                  "Parity check enabled",
    "�� ���������", "NOT VERIFY", "�������� �������� ���������",
                                  "Parity check off",
    FLAG_1, BIT_PARITY, pUSB, FuncActive, FuncChangedChoice, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
DEF_PAGE_3(pUSB,                                                                                                                         //--- USB ---
    "USB", "USB",
    "��������� ���������� ����� �� ���������� USB",
    "Communication parameters settings on the USB interface",
    cSizeByte,              ///< USB - ������ �����
    cStopBit,               ///< USB - ����-���
    cParity,                ///< USB - ר������
    Page_USB, 0, FuncActive, FuncPress
)
