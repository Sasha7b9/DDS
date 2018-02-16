#pragma once
#include "Keyboard/Controls.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���� �������������� ���������� �������� ���������
class InputWindow
{
public:
    static void Init();
    static void Draw();
    static void KeyLeft();
    static void KeyRight();
    static void KeyEnter();
    static void ProcessContorl(StructControl control);
};
