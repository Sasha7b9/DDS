#pragma once
#include "defines.h"
#include "SettingsTypes.h"
#include "Display/InputWindowStruct.h"
#include "Menu/MenuItems.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const PageBase pInput;

#define CHANNEL                 (set.sig_channel)
#define CHANNEL_IS_A            (CHANNEL == A)
#define CHANNEL_IS_B            (CHANNEL == B)

#define CHANNEL_ENABLED(ch)     (set.sig_enabled[ch])
#define CHANNEL_ENABLED_A       (CHANNEL_ENABLED(A))
#define CHANNEL_ENABLED_B       (CHANNEL_ENABLED(B))

#define WAVE_FORM               (set.sig_form[CHANNEL])
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

#define DEBUG_MODE_ENABLED      (set.dbg_debugModeEnabled)

#define LANG                    (set.serv_language)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)

class Settings
{
public:
    uint16              size;                           ///< ������ ��������� Settings
    col_val             disp_Colors[16];                ///< �����
    Channel             sig_channel;                    ///< ������� ��������� �����
    WaveForm            sig_form[NumChannels];          ///< ������� ��������� ����� �������
    WaveParameter       sig_parameter[NumForms];        ///< ������� ��������� �������� �������
    InputWindowStruct   sig_structParameter[NumChannels][NumForms][NumParameters];
    Language            serv_language;                  ///< ��������� ����
    int8                menu_currentPage;               ///< ������������ �������� ����
    void*               menu_openedItem;                ///< ���� �����-�� ����� ���� �������, �� ����� ��� �����
    Page*               menu_page;                      ///< ���� ������� �������� �� �� �������� ����, �� ����� � �����
    bool                dbg_console;
    bool                sig_enabled[NumChannels];       ///< ��������� ������ - ������� ��� ��������
    bool                serv_bacgroundBlack;            ///< ���� true, �� ���� ���� - ������
    bool                sig_tuneFull;                   ///< ���� true, �� ������� ��������� ���������� ���������� �� ����� ���������
    bool                dbg_debugModeEnabled;           ///< ���� true, �� ������� ���������� ����� - ����������� ������� � �������

    static void Save();
    static void Load();
};

#pragma pack(pop)

extern Settings set;

void TuneGenerator(Channel ch);
