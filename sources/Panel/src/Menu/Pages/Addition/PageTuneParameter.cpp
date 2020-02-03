#include "Display/Symbols.h"
#include "Display/Text.h"
#include "Generator/ParametersSupport.h"
#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Addition/PageTuneParameter.h"
#include "Settings/Settings.h"


static ParameterTuner tuner;


void PageTuneParameter::SetParameter(Parameter *parameter)
{
    tuner.SetParameter(parameter);
}


static void Draw_Left(int, int)
{
}

static void OnPress_OrderUp()
{

}

DEF_SMALL_BUTTON(sbOrderUp,                                                                                                                               //--- ���� ����� - ������ ����� ---
    "������� ������",
    "��������� ������� ������� ���������",
    *PageTuneParameter::self, Item::FuncActive, OnPress_OrderUp, Draw_Left
)


static void Draw_Right(int, int)
{
}

static void OnPress_OrderDown()
{

}

DEF_SMALL_BUTTON(sbOrderDown,                                                                                                                            //--- ���� ����� - ������ ������ ---
    "������� �������",
    "��������� ������� ������� ���������",
    *PageTuneParameter::self, Item::FuncActive, OnPress_OrderDown, Draw_Right
)



static void OnPress_Cancel()
{
    set.Restore();
    Menu::ResetAdditionPage();
}

static void Draw_Cancel(int x, int y)
{
    String("��������").Draw(x + 13, y + 12);
    Text::Draw4SymbolsInRect(x + 25, y + 28, Ideograph::_8::Delete);
}

DEF_SMALL_BUTTON(sbCancel,                                                                                                                                      //--- ���� ����� - ������ ---
    "������� ���������",
    "���������� �� ����� ������ ��������",
    *PageTuneParameter::self, Item::FuncActive, OnPress_Cancel, Draw_Cancel
)


static void Draw_Enter(int x, int y)
{
    String("�����������").Draw(x + 3, y + 12);
    Text::Draw4SymbolsInRect(x + 25, y + 28, Ideograph::_8::Save);
}

static void OnPress_Enter()
{
    Menu::ResetAdditionPage();
}

DEF_SMALL_BUTTON(sbEnter,                                                                                                                                         //--- ���� ����� - ���� ---
    "����",
    "����������� ���� ������ ��������",
    *PageTuneParameter::self, Item::FuncActive, OnPress_Enter, Draw_Enter
)


static bool OnControl_TuneParameter(const Key &key)
{
    if(key.action == Key::Action::Up)
    {
        if(key.value == Key::Esc)
        {
            OnPress_Cancel();
            return true;
        }
        else if(key.value == Key::RegButton)
        {
            Menu::ResetAdditionPage();
            return true;
        }
    }

    return tuner.ProcessControl(key);
}

static void OnDraw_TuneParameter()
{
    tuner.Draw();
}


static void OnEnter_TuneParameter(bool enter)
{
    if(enter)
    {
        set.Store();
    }
}


DEF_PAGE_SB( pTuneParameter,   //-V641
    "���� ��������", //-V641
    "",
    &sbOrderUp,         ///< ���� ����� - ������ �����
    &sbOrderDown,       ///< ���� ����� - ������ ������
    &sbCancel,          ///< ���� ����� - ������
    &sbEnter,           ///< ���� ����� - ����
    Page::SB_Input, 0, Item::FuncActive, OnEnter_TuneParameter, OnDraw_TuneParameter, OnControl_TuneParameter
)

Page *PageTuneParameter::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pTuneParameter));
