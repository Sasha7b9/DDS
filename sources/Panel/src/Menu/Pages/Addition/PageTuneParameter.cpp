#include "Display/Symbols.h"
#include "Display/Text.h"
#include "Generator/Signals.h"
#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Addition/PageTuneParameter.h"
#include "Settings/Settings.h"


static ParameterValue stored = ParameterAmplitude();    // ����� ����� ��������� ������������� �������� ����� ��� ����������, ����� ������������ � ������ ������������� //-V1054

static ParameterValue *tuned = nullptr;     // ������������� �������� //-V1054


void PageTuneParameter::SetParameter(ParameterValue *parameter)
{
    if(parameter->IsValue())
    {
        stored = *parameter;
        tuned = parameter;
    }
}


static void OnPress_Cancel()
{
    Parameter *parameter = CURRENT_WAVE.GetCurrentForm()->CurrentParameter();

    if(parameter->IsValue())
    {
        *reinterpret_cast<ParameterValue *>(parameter) = stored;
    }

    PGenerator::TuneChannel(CURRENT_CHANNEL);

    Menu::ResetAdditionPage();
}

static void Draw_Cancel(int x, int y)
{
    String("��������").Draw(x + 13, y + 12);
    Text::Draw4SymbolsInRect(x + 25, y + 28, Ideograph::_8::Delete);
}

DEF_SMALL_BUTTON(sbCancel,                                                                                                                                      //--- ���� ����� - ������ ---
    "������", "CANCEL",
    "���������� �� ����� ������ ��������", "Refuse to enter a new value",
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
    "����", "ENTER",
    "����������� ���� ������ ��������", "Confirm new value entry",
    *PageTuneParameter::self, Item::FuncActive, OnPress_Enter, Draw_Enter
)


static bool OnControl_TuneParameter(const Control control) //-V801
{
    if(control.IsDown())
    {
        if(control.Is(Key::Esc))
        {
            OnPress_Cancel();
            return true;
        }
        else if(control.Is(Key::RegButton))
        {
            Menu::ResetAdditionPage();
            return true;
        }
        else
        {
            return tuned->tuner.OnControlKey(control);
        }
    }

    return false;
}

static void OnDraw_TuneParameter()
{
    tuned->tuner.Draw();
}


DEF_PAGE_SB( pTuneParameter,   //-V641
    "���� ��������", "ENTER VALUE", //-V641
    "", "",
    Item::EmptyDark(),      // ���� ����� - ������ �����
    Item::EmptyDark(),      // ���� ����� - ������ ������
    &sbCancel,              // ���� ����� - ������
    &sbEnter,               // ���� ����� - ����
    Page::SB_Input, 0, Item::FuncActive, Page::FuncEnter, OnDraw_TuneParameter, OnControl_TuneParameter
)

Page *PageTuneParameter::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pTuneParameter));
