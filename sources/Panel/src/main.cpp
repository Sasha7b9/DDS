#include "Display/Display.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Interface/Interface_p.h"
#include "Menu/Menu.h"
#include "Settings/CalibrationSettings.h"
#include "Settings/Settings.h"


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
        PInterface::Update();
    }
}
