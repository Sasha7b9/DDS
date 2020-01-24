#include "Display/Symbols.h"
#include "Display/Text.h"
#include "Generator/ParametersSupport.h"
#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Addition/PageTuneParameter.h"


static ParameterTuner tuner;


static void OnDraw_TuneParameter();


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

}

DEF_SMALL_BUTTON(sbEnter,                                                                                                                                         //--- ���� ����� - ���� ---
    "����",
    "����������� ���� ������ ��������",
    *PageTuneParameter::self, Item::FuncActive, OnPress_Enter, Draw_Enter
)


static bool OnControl_TuneParameter(Key &key)
{
    return tuner.ProcessControl(key);
}


DEF_PAGE_SB( pTuneParameter,   //-V641
    "���� ��������", //-V641
    "",
    &sbOrderUp,         ///< ���� ����� - ������ �����
    &sbOrderDown,       ///< ���� ����� - ������ ������
    &sbCancel,          ///< ���� ����� - ������
    &sbEnter,           ///< ���� ����� - ����
    Page::SB_Input, 0, Item::FuncActive, FuncEnter, OnDraw_TuneParameter, OnControl_TuneParameter
)

Page *PageTuneParameter::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pTuneParameter));


/// ���������� �������� ���������
static void DrawNameParameter()
{

}


/// ���������� �������� ���������
static void DrawParameter()
{
}


static void OnDraw_TuneParameter()
{
    tuner.Draw();

    DrawNameParameter();

    DrawParameter();
}
