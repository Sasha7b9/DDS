#include "defines.h"
#include "globals.h"
#include "Log.h"
#include "Display/Display.h"
#include "Display/Painter.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Generator.h"
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

    Settings::Load();
       
    Menu::Init();

    LOG_WRITE("%d %d %d", sizeof(InputWindowStruct), sizeof(Settings), sizeof(sig_structParameter));

    while (1)
    {
        CPU::Update();
        Menu::Update();
        Display::Update();
    }
}


/** @} */
