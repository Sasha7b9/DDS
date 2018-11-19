#include "stdafx.h"
#ifndef WIN32
#include "Interface/InterfacePanel.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Utils/Debug.h"
#include <cstdlib>
#endif


/** @defgroup Panel
 *  @{
 */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    CPU::Init();
    
    Timer::Init();
    
    Display::Init();

    Timer::PauseOnTime(1000);    // �������� �������, ������ ��� ��� �� �� ����������� ���������. ������, �� ���������������� ������� ������� ������

    Settings::Load();

    Menu::Init();

    while (1)
    {
        DEBUG_POINT;
        CPU::Update();
        DEBUG_POINT;
        Menu::Update();
        DEBUG_POINT;
        Display::Update();
        DEBUG_POINT;
        Interface::Update();
        DEBUG_POINT;
    }
}


/** @} */
