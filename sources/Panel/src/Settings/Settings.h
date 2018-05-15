#pragma once
#include "defines.h"
#include "SettingsTypes.h"
#include "Display/InputWindowStruct.h"
#include "Menu/MenuItems.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pInput;

#define CURRENT_CHANNEL         (set.sig_channel)
#define CURRENT_CHANNEL_IS_A    (CURRENT_CHANNEL == A)
#define CURRENT_CHANNEL_IS_B    (CURRENT_CHANNEL == B)

#define CHANNEL_ENABLED(ch)     (set.sig_enabled[ch])
#define CHANNEL_ENABLED_A       (CHANNEL_ENABLED(A))
#define CHANNEL_ENABLED_B       (CHANNEL_ENABLED(B))

#define WAVE_FORM               (set.sig_form[CURRENT_CHANNEL])
#define WAVE_FORM_CH(ch)        (set.sig_form[ch])
#define WAVE_FORM_IS_FPGA       (WAVE_FORM != Form_Sine && WAVE_FORM != Form_Impulse)

#define INPUT_WINDOW_STRUCT(ch, form, param)    (set.sig_structParameter[ch][form][param])

#define COLOR(x)                (set.disp_Colors[x])
#define LANGUAGE                (set.serv_language)
#define CURRENT_PAGE            (set.menu_currentPage)
#define OPENED_ITEM             (set.menu_openedItem)
#define OPENED_ITEM_IS_NONE     (OPENED_ITEM == 0)
#define ADDITION_PAGE           (set.menu_page)
#define ADDITION_PAGE_IS_INPUT  (ADDITION_PAGE == (Page *)&pInput)
#define ADDITION_PAGE_IS_NONE   (ADDITION_PAGE == 0)

#define CONSOLE_ENABLED         (set.dbg_console)

#define FREQ_COUNTER_ENABLED    (set.freq_enabled)

#define DEBUG_MODE_ENABLED      (set.dbg_debugModeEnabled)

#define LANG                    (set.serv_language)
#define LANG_RU                 (LANG == Russian)

#define MENU_POS_ACT_ITEM(x)    (set.menu_posActItem[x])
#define MENU_CURRENT_SUBPAGE(x) (set.menu_currentSubPage[x])

#define BACKGROUND_BLACK        (set.serv_bacgroundBlack)

#define CURRENT_PARAMETER(form) (set.sig_parameter[form])

#define SIZE_BYTE               (set.usb_sizeByte)
#define STOP_BIT                (set.usb_stopBit)
#define PARITY                  (set.usb_parity)
#define INTERVAL                (set.freq_interval)
#define BILLING_TIME            (set.freq_billingTime)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)

class Settings
{
public:
    uint16              size;                           ///< ������ ��������� Settings
    union
    {
        uint8 empty[2 * 4 * 8];                         ///< ����������� ����� ��� ������������� ������������� ������ �� ����, ��� 2 ������,
                                                        ///< ������ ��������� �� ������ ����� � � ������ ��������� 8 ����
        struct Cal
        {
        }cal;
    };
    col_val             disp_Colors[16];                ///< �����
    Channel             sig_channel;                    ///< ������� ��������� �����
    Type_WaveForm            sig_form[NumChannels];          ///< ������� ��������� ����� �������
    WaveParameter       sig_parameter[NumForms];        ///< ������� ��������� �������� �������
    InputWindowStruct   sig_structParameter[NumChannels][NumForms][NumParameters];
    Language            serv_language;                  ///< ��������� ����
    int8                menu_currentPage;               ///< ������������ �������� ����
    Control*            menu_openedItem;                ///< ���� �����-�� ����� ���� �������, �� ����� ��� �����
    Page*               menu_page;                      ///< ���� ������� �������� �� �� �������� ����, �� ����� � �����
    bool                dbg_console;
    bool                sig_enabled[NumChannels];       ///< ��������� ������ - ������� ��� ��������
    bool                serv_bacgroundBlack;            ///< ���� true, �� ���� ���� - ������
    bool                sig_tuneFull;                   ///< ���� true, �� ������� ��������� ���������� ���������� �� ����� ���������
    bool                dbg_debugModeEnabled;           ///< ���� true, �� ������� ���������� ����� - ����������� ������� � �������
    int8                menu_posActItem[NumPages];      ///< ������� ��������� ������ ���� ��� ������ ��������
    int8                menu_currentSubPage[NumPages];  ///< ����� ������� ����������� ��� ������ ��������
    bool                freq_enabled;                   ///< ����������� ��������� �����������
    SizeByte            usb_sizeByte;                   ///< ������ ����� ��� ����� �� USB
    StopBit             usb_stopBit;                    ///< ���������� ����-���
    Parity              usb_parity;                     ///< ���� ��������
    Interval            freq_interval;                  ///< �������� ������� ���������
    BillingTime         freq_billingTime;               ///< ����� �����

    static void Save();
    static void Load(bool _default = false);
};

#pragma pack(pop)

extern Settings set;

void TuneGenerator(Channel ch);
