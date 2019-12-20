#include "defines.h"
#include "log.h"
#include "Interface/Interface_p.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Menu/Menu.h"
#include "Settings/Settings.h"
#include "Settings/CalibrationSettings.h"
#include "SCPI/SCPI.h"
#include <cstdlib>
#include <cstdio>


//namespace std
//{
//    struct __FILE
//    {
//        int handle;
//    };
//    
//    //FILE  __stdout;
//}
//
//int fputs(int ch, FILE *f)
//{
//    LOG_WRITE("%c", ch);
//    return (ch);
//}

/** @defgroup Panel
 *  @{
 */


int main()
{
    CPU::Init();
    
    Timer::Init();
    
    Display::Init();

    Timer::PauseOnTime(1000);    // �������� �������, ������ ��� ��� �� �� ����������� ���������. ������, �� ���������������� ������� ������� ������

    setCal.Load();

    set.Load();

    Menu::Init();

    while (1)
    {
        CPU::Update();
        Menu::Update();
        Display::Update();
        Interface::Update();
    }
}


/** @} */
