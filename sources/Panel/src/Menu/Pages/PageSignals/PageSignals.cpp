#include "Display/InputWindow.h"
#include "Settings/Settings.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Addition/PageInput.h"
#include "Menu/Pages/Include/PageSignals.h"
#include "Generator/Signals.h"
#include "Generator/Generator_p.h"
#include "Menu/Menu.h"


extern const PageBase pageSignals;
Page *PageSignals::pointer = reinterpret_cast<Page *>(const_cast<PageBase *>(&pageSignals));
extern ChoiceParameterBase cParameters;
/// ����� ������� ����� ������
static int numForm = 0;



DEF_CHOICE_2( cChannel,                                                                                                                                  //--- ��������� �������� - ����� ---
    "�����",
    "����� ������ ��� ���������."
    ,
    "A", "���������� ����������� ������� �� ������ A.",
    "B", "���������� ����������� ������� �� ������ B.",
    FLAG, BIT_CHANNEL, pageSignals, Item::FuncActive, PageSignals::OnPress_Channel, FuncDraw
)



DEF_CHOICE_8( cFormA,                                                                                                                                    //--- ��������� �������� - ����� ---
    "�����",
    "����� ����� �������."
    ,
    FORM_RU(Form::Sine),         "�����",
    FORM_RU(Form::RampPlus),     "����������� ����",
    FORM_RU(Form::RampMinus),    "��������� ����",
    FORM_RU(Form::Triangle),     "�����������",
    FORM_RU(Form::Meander),      "������",
    FORM_RU(Form::Impulse),      "�����������",
    FORM_RU(Form::PacketImpuls), "������",
    FORM_RU(Form::Free),         "������������",
    numForm, pageSignals, Item::FuncActive, PageSignals::OnPress_Form, FuncDraw
)

DEF_CHOICE_7( cFormB,                                                                                                                                    //--- ��������� �������� - ����� ---
    "�����",
    "����� ����� �������."
    ,
    FORM_RU(Form::Sine),      "�����",
    FORM_RU(Form::RampPlus),  "����������� ����",
    FORM_RU(Form::RampMinus), "��������� ����",
    FORM_RU(Form::Triangle),  "�����������",
    FORM_RU(Form::Meander),   "������",
    FORM_RU(Form::Impulse),   "�����������",
    FORM_RU(Form::Free),      "������������",
    numForm, pageSignals, Item::FuncActive, PageSignals::OnPress_Form, FuncDraw
)


static void OnPress_ChnageParameter()
{
    FORM_CURRENT->ChangeParameter();
}

DEF_BUTTON( bChangeParameter,                                                                                                        //--- ��������� �������� - ������ �������� ��������� ---
    "��������",
    "��������� ���� ����� ���������.",
    pageSignals, Item::FuncActive, OnPress_ChnageParameter, FuncDraw
)

DEF_CHOICE_PARAMETER( cParameters,                                                                                                                    //--- ��������� �������� - �������� ---
    "��������",
    "����� ��������� ��� ���������.",
    pageSignals, Item::FuncActive, OnPress_ChnageParameter, WAVE(Chan::A).GetForm(0)
)


DEF_CHOICE_2( cTypeTune,                                                                                                                               //--- ��������� �������� - ������� ---
    "�������",
    "���������� ������������� ������� �������� �������� � ���������� ����������.",
    "����������", "������� �������� ������� ���������� ����������, ����� ������� ������ �������������.",
    "����������", "������� �������� ������� ���������� ��������� � ���������� ���������� �� ������.",
    FLAG, BIT_TUNE_FULL, pageSignals, Item::FuncActive, FuncChangedChoice, FuncDraw
)


static bool OnKey_PageSignals(KeyEvent &key)
{
    if(key.Is(KeyEvent::Esc) && key.action.IsRelease())
    {
        return FORM_CURRENT->CloseOpenedParameter();
    }

    return false;
}

DEF_PAGE_7( pageSignals,   //-V641
    "��������� ��������",  
    "",
    &cChannel,                                      ///< ��������� �������� - �����
    &cFormA,                                        ///< ��������� �������� - �����
    &cParameters,                                   ///< ��������� �������� - ��������
    &bChangeParameter,                              ///< ��������� �������� - ������ �������� ���������
    &cTypeTune,                                     ///< ��������� �������� - �������
    PageSignals::PageCalibration::PageA::pointer,   ///< ��������� �������� - ���������� A
    PageSignals::PageCalibration::PageB::pointer,   ///< ��������� �������� - ���������� B
    Page::Settings, Menu::mainPage, Item::FuncActive, FuncPress, OnKey_PageSignals, FuncBeforeDraw
)


void PageSignals::Init()
{
    OnPress_Channel(true);
}


void PageSignals::OnPress_Form(bool)
{
    ChoiceBase *choice = reinterpret_cast<ChoiceBase *>(pageSignals.items[1]);    // ��������� �� ChoiceBase, �������� ������ ��������� ����� �������� ������

    WAVE_CURRENT.SetIndexForm(choice->CurrentIndex());          // ���������� ��� �������� ������� ������ ����� �� ChoiceBase

    cParameters.form = FORM_CURRENT;

    PGenerator::TuneChannel(CURRENT_CHANNEL);
}


void PageSignals::SetForm(Form::E form)
{
    if(form == Form::Free && CURRENT_CHANNEL_IS_B)
    {
        return;
    }

    numForm = form;
    OnPress_Form(true);
}


void PageSignals::OnPress_Channel(bool)
{
    cParameters.form = FORM_CURRENT;
    numForm = FORM_CURRENT->value;

    pageSignals.items[1] = reinterpret_cast<Item *>(const_cast<ChoiceBase *>(Chan(CURRENT_CHANNEL).IsA() ? &cFormA : &cFormB));
}


void PageSignals::SetCurrentChanenl(Chan::E ch)
{
    if(ch == Chan::A)
    {
        CLEAR_FL(BIT_CHANNEL);
    }
    else
    {
        SET_FL(BIT_CHANNEL);
    }
}
