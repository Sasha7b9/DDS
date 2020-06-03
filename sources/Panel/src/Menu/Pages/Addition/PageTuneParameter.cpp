#include "Display/Painter.h"
#include "Display/Symbols.h"
#include "Display/Text.h"
#include "Generator/Signals.h"
#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


static ParameterDouble stored = ParameterAmplitude();    // ����� ����� ��������� ������������� �������� ����� ��� ����������, ����� ������������ � ������ ������������� //-V1054

static ParameterDouble *tuned = nullptr;     // ������������� �������� //-V1054


void PageTuneParameter::SetParameter(ParameterDouble *parameter)
{
    if(parameter->IsDouble())
    {
        stored = *parameter;
        tuned = parameter;
    }
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Draw_More(int x, int y)
{
    String(LANG_IS_RU ? "������" : "Increase").DrawInCenterRect(x, y, 70, 30);
    Char(Ideograph::_8::Up).Draw2Horizontal(x + 25, y + 30);
}

DEF_GRAPH_BUTTON(sbMore,
    "������", "More",
    "��������� �������", "Increase order",
    *PageTuneParameter::self, Item::FuncActive, DisplayEntering::OnButtonOrderMore, Draw_More
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Draw_Less(int x, int y)
{
    String(LANG_IS_RU ? "������" : "Decrease").DrawInCenterRect(x, y, 70, 30);
    Char(Ideograph::_8::Down).Draw2Horizontal(x + 25, y + 30);
}


DEF_GRAPH_BUTTON(sbLess,
    "������", "Less",
    "��������� �������", "Decrease order",
    *PageTuneParameter::self, Item::FuncActive, DisplayEntering::OnButtonOrderLess, Draw_Less
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void PageTuneParameter::CallbackOnButtonCancel()
{
    Parameter *parameter = CURRENT_WAVE.GetCurrentForm()->CurrentParameter();

    if (parameter->IsDouble())
    {
        *reinterpret_cast<ParameterDouble *>(parameter) = stored;
    }

    PGenerator::TuneChannel(CURRENT_CHANNEL);

    Menu::ResetAdditionPage();
}

static void OnPress_Cancel()
{
    Tuner::Current()->OnButtonCancel();
}

static void Draw_Cancel(int x, int y)
{
    String(LANG_IS_RU ? "��������" : "Cancel").DrawInCenterRect(x, y, 70, 30);
    Char(Ideograph::_8::Delete).Draw4InRect(x + 25, y + 28);
}

DEF_GRAPH_BUTTON(sbCancel,
    "��������", "Cancel",
    "���������� �� ����� ������ ��������", "Refuse to enter a new value",
    *PageTuneParameter::self, Item::FuncActive, OnPress_Cancel, Draw_Cancel
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void Draw_Enter(int x, int y)
{
    String(LANG_IS_RU ? "���������" : "Apply").DrawInCenterRect(x, y, 70, 30);
    Char(Ideograph::_8::Save).Draw4InRect(x + 25, y + 28);
}

void PageTuneParameter::CallbackOnButtonApply()
{
    Menu::ResetAdditionPage();
}

static void OnPress_Enter()
{
    Tuner::Current()->OnButtonApply();
}

DEF_GRAPH_BUTTON(sbEnter,
    "���������", "Apply",
    "����������� ���� ������ ��������", "Confirm new value entry",
    *PageTuneParameter::self, Item::FuncActive, OnPress_Enter, Draw_Enter
)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static bool OnControl_TuneParameter(const Control control) //-V801
{
    if (control.IsUp() && control.Is(Key::Esc))
    {
        OnPress_Cancel();
        return true;
    }

    if(control.IsDown())
    {
        if(control.Is(Key::RegButton))
        {
            Menu::ResetAdditionPage();
            return true;
        }
        else
        {
            return Tuner::Current()->OnControlKey(control);
        }
    }

    return false;
}

static void OnDraw_TuneParameter()
{
    tuned->GetTuner()->Draw();
}


static void OnOpenClose_TuneParameter(bool enter)
{
    if (enter)
    {
        tuned->GetTuner()->Init();
    }
}


DEF_PAGE_SB(pTuneParameter,   //-V641
    "���� ��������", "ENTER VALUE", //-V641
    "", "",
    &Item::emptyDark,
    &Item::emptyDark,
    &sbCancel,
    &sbEnter,
    Page::SB_Input, 0, Item::FuncActive, OnOpenClose_TuneParameter, OnDraw_TuneParameter, OnControl_TuneParameter
)

Page *PageTuneParameter::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pTuneParameter));


void PageTuneParameter::SetModeEntering()
{
    if (Tuner::Current()->ParameterIsVoltage())
    {

    }
    else
    {
        pTuneParameter.items[0] = reinterpret_cast<Item *>(const_cast<SButtonBase *>(&sbMore));
        pTuneParameter.items[1] = reinterpret_cast<Item *>(const_cast<SButtonBase *>(&sbLess));
    }
}


void PageTuneParameter::ResetModeEntering()
{
    pTuneParameter.items[0] = &Item::emptyDark;
    pTuneParameter.items[1] = &Item::emptyDark;
}


bool PageTuneParameter::IsOpened()
{
    return (CURRENT_PAGE == PageTuneParameter::self);
}
