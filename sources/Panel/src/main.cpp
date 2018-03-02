#include "defines.h"
#include "Log.h"
#include "Display/Display.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Generator/Generator.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"


/** @defgroup Panel
 *  @{
 */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    CPU::Init();

    Timer::Init();
   
    Display::Init();

    Timer::PauseOnTime(200);    // �������� �������, ������ ��� ��� �� �� ����������� ���������. ������, �� ���������������� ������� ������� ������

    Generator::Reset();

    Timer::PauseOnTime(200);

    Settings::Load();

    Menu::Init();

    while (1)
    {
        Menu::Update();
        Display::Update();
    }
}


/** @} */
