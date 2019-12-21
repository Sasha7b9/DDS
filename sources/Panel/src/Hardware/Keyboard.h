#pragma once
#include "Hardware/Controls.h"


struct Keyboard
{
    friend class CPU;

public:
    static void InitInputs(const uint16 *sl, const char *portSL, int numSL, const uint16 *rl, const char *portRL, int numRL);
    /// ���������� true, ���� ����� ����
    static bool BufferIsEmpty();
    /// ���������� ��������� ����� ����������, ���� ������� �������
    static KeyEvent GetNextControl();
    /// �������-��������. ��� ���������, �� ������� ��� ���������� ���������� � ����� � �������� �� ������
    static void Draw();

    static void AppendEvent(KeyEvent::E key, KeyEvent::Action::E action);

private:

    static void Init();

    static void Update();
};
