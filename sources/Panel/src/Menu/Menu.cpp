#include "Menu.h"
#include "globals.h"
#include "Menu/Hint.h"
#include "Menu/MenuItems.h"
#include "Display/InputWindow.h"
#include "Display/InputWindowStruct.h"
#include "Generator.h"
#include "Hardware/CPU.h"
#include "Utils/Math.h"
#include "Menu/Pages/PageSettings.h"
#include "Menu/Pages/PageSettings2.h"
#include "Menu/Pages/PageFrequencyCounter.h"
#include "Menu/Pages/PageFrequencyCounter2.h"
#include "Menu/Pages/PageFrequencyCounter3.h"
#include "Menu/Pages/PageService.h"
#include "Menu/Pages/PageDebug.h"
#include "Menu/Pages/PageUSB.h"
#include "Menu/Pages/PageRegisters.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Item *Menu::itemUnderKey = 0;
Item *Menu::openedItem = 0;
//Control Menu::panelControlHint = B_None;

const Page *pages[NUM_PAGES] =
{
    PageSignals::pointer,
    PageSignals2::pointer,
    PageRegisters::pointer,
    PageFrequencyCounter::pointer,
    PageFrequencyCounter3::pointer,
    PageFrequencyCounter2::pointer,
    PageUSB::pointer,
    PageService::pointer,
    PageDebug::pointer
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Menu::Init()
{
    PageSignals::Init();
    PageSignals::OnPress_Form();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::Update()
{
    while (!CPU::Keyboard::BufferIsEmpty())
    {
        StructControl control = CPU::Keyboard::GetNextControl();
        if (ADDITION_PAGE_IS_INPUT)
        {
            InputWindow::ProcessContorl(control);
        }
        else
        {
            ProcessControl(control);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Menu::ProcessControl(StructControl strContr)
{
    Control key = strContr.key;
    TypePress pressed = strContr.typePress;

    if(Hint::ProcessControl(strContr))
    {
    }
    else if(Menu::CurrentPage()->ProcessingControl(strContr))
    {
    }
    else if (openedItem && (key == REG_LEFT || key == REG_RIGHT || key == REG_BTN || key == B_ESC || key == B_LEFT || key == B_RIGHT))
    {
        openedItem = openedItem->Press(strContr);
    }
    else if (key >= B_F1 && key <= B_F5)
    {
        openedItem = CurrentPage()->GetItem(key - B_F1)->Press(strContr);
    }
    else if (key == REG_LEFT)
    {
        if (RegIsControlPages())
        {
            if (CURRENT_PAGE > 0)
            {
                --CURRENT_PAGE;
            }
        }
    }
    else if (key == REG_RIGHT)
    {
        if (RegIsControlPages())
        {
            if (CURRENT_PAGE < NUM_PAGES - 1)
            {
                ++CURRENT_PAGE;
            }
        }
    }
    else if (pressed == Up || pressed == Long)
    {
        if(key == B_ON1)
        {
            SWITCH_CHANNEL_A;
            Generator::EnableChannel(Chan::A, CHANNEL_ENABLED(Chan::A));
        }
        else if (key == B_ON2)
        {
            SWITCH_CHANNEL_B;
            Generator::EnableChannel(Chan::B, CHANNEL_ENABLED(Chan::B));
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Menu::RegIsControlPages()
{
    return openedItem == 0 && ADDITION_PAGE_IS_NONE;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *Menu::NameCurrentParameter()
{
    return PageSignals::cpParameters->NameCurrentSubItem();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Item *Menu::OpenedItem()
{
    return openedItem;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Item *Menu::CurrentItem()
{
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Page *Menu::CurrentPage()
{
    volatile int8 num = CURRENT_PAGE;

    if (num == 1)
    {
        num = num;
    }

    Page *page = (Page *)pages[num];

    return (ADDITION_PAGE_IS_NONE ? page : ADDITION_PAGE);
}
