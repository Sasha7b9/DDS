#include "Display/Symbols.h"
#include "Display/Text.h"
#include "Generator/ParametersSupport.h"
#include "Generator/Signals.h"
#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Addition/PageTuneParameter.h"
#include "Settings/Settings.h"


static ParameterTuner tuner;
// ����� ����� ��������� ������������� �������� ����� ��� ����������, ����� ������������ � ������ �������������
static ParameterValue storedParameter = ParameterAmplitude();


void PageTuneParameter::SetParameter(Parameter *parameter)
{
    if(parameter->IsValue())
    {
        storedParameter = *reinterpret_cast<ParameterValue *>(parameter);
    }

    tuner.SetParameter(parameter);
}


static void OnPress_Cancel()
{
    Parameter *parameter = CURRENT_WAVE.GetCurrentForm()->CurrentParameter();

    if(parameter->IsValue())
    {
        *reinterpret_cast<ParameterValue *>(parameter) = storedParameter;
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


static bool OnControl_TuneParameter(const Key &key)
{
    if(key.action == Key::Up)
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


DEF_PAGE_SB( pTuneParameter,   //-V641
    "���� ��������", "ENTER VALUE", //-V641
    "", "",
    Item::EmptyDark(),         ///< ���� ����� - ������ �����
    Item::EmptyDark(),       ///< ���� ����� - ������ ������
    &sbCancel,          ///< ���� ����� - ������
    &sbEnter,           ///< ���� ����� - ����
    Page::SB_Input, 0, Item::FuncActive, Page::FuncEnter, OnDraw_TuneParameter, OnControl_TuneParameter
)

Page *PageTuneParameter::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pTuneParameter));
