#include "defines.h"
#include "FDrive/FDrive_d.h"
#include "Interface/Interface_d.h"
#include "Hardware/CPU.h"
#include "Hardware/HAL/HAL.h"


int main()
{
    CPU::Init();
    HAL_TIM::Delay(500);             // �������� ����� ��� ����, ����� AD9952 ����� ������ ���������� �������������
    DDrive::Init();
    HAL_EEPROM::Init();
  
    while (1)
    {
    }
}
