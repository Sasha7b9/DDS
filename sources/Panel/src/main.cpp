#include "stdafx.h"
#ifndef WIN32
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Utils/Debug.h"
#endif


/** @defgroup Panel
 *  @{
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        CPU::Update();
        Menu::Update();
        Display::Update();
        Generator::Update();
    }
}


/** @} */
