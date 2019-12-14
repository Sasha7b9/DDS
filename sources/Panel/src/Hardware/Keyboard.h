#pragma once


struct Keyboard
{
    friend class CPU;

private:

    static void Init();

public:
    static void InitInputs(const uint16 *sl, const char *portSL, int numSL, const uint16 *rl, const char *portRL, int numRL);
    /// ���������� true, ���� ����� ����
    static bool BufferIsEmpty();
    /// ���������� ��������� ����� ����������, ���� ������� �������
    static KeyEvent GetNextControl();
    /// �������-��������. ��� ���������, �� ������� ��� ���������� ���������� � ����� � �������� �� ������
    static void Draw();

private:

    static void Update();
};
