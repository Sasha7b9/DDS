#pragma once
#include "Controls.h"


#define TIME_LONG_PRESSURE 1000


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Keyboard
{
public:
    static void Init();

private:
    static void Update();
};


/// ���������� true, ���� ����� ����
bool Keyboard_BufferIsEmpty();
/// ���������� ��������� ����� ����������, ���� ������� �������
StructControl Keyboard_GetNextControl();
