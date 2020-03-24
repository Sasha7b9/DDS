#include "defines.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"
#include "Interface/Interface_p.h"

int main()
{
    CPU::Init();
    Timer::Init();
    HAL_TIM::Delay(1000);    // �������� �������, ������ ��� ��� �� �� ����������� ���������. ������, �� ���������������� ������� ������� ������

    while (1)
    {
    }
}
