#pragma once
#include "Controls.h"
#include <stm32f4xx_hal.h>


#define TIME_LONG_PRESSURE 1000


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Keyboard_Init();
/// ���������� true, ���� ����� ����
bool Keyboard_BufferIsEmpty();
/// ���������� ��������� ����� ����������, ���� ������� �������
StructControl Keyboard_GetNextControl();
