#include "defines.h"
#include "Display/Display.h"
#include "Display/Painter.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Generator/Generator.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Display/Console.h"
#include "Utils/Debug.h"


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
