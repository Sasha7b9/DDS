#pragma once
#include "Controls.h"


#define TIME_LONG_PRESSURE 1000


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Keyboard
{
public:

    static void Init();
    /// ���������� true, ���� ����� ����
    static bool BufferIsEmpty();
    /// ���������� ��������� ����� ����������, ���� ������� �������
    static StructControl GetNextControl();

private:
    static void Update();
};
