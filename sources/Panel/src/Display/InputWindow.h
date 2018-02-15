#pragma once
#include "Keyboard/Controls.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������� ���� �������� ��� ������ ���� �� �����

class InputWindow
{
public:
    static void KeyLeft();
    static void KeyRight();
    static void KeyEnter();
};

void InputWindow_Init();

void InputWindow_Draw();

void InputWindow_ProcessContorl(StructControl control);
