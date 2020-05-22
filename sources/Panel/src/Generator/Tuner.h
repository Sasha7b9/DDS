#pragma once
#include "Keyboard/Controls.h"


class ParameterValue;


class Digit
{
public:

    Digit(char v = '0') : value(v) { }

    operator char() { return value; }

    // ��������� �������� � �������. ���� ���������� (����� '9') - ��������� false
    bool Increase();

    // ��������� �������� � �������. ���� ���������� (����� '0') - ���������� false
    bool Decrease();

    // ���������� ����� ��������
    void Set(char v) { value = v; }

private:

    char value;
};


// ���������� ����������, ����������� � �����������, � ������� ��� ������������� ��������� ����������
class Indicator
{
public:

    Indicator();

    void Draw(int x, int y);

    // ������� �������� ������ ����� �� ���������
    void HighlightLeft();

    // ������� �������� ������ ������ �� ���������
    void HighlightRight();

    // �������� �������� � ������� �������
    void HighlightIncrease();

    // ��������� �������� � ������ �������
    void HighlightDecrease();

private:

    static const int MAX_NUM_DIGITS = 15;

    Digit digits[MAX_NUM_DIGITS];           // ����� ��������� ��� �������

    int indexHighlight;                     // ������ ������������� ����������

    // ���������� ������ ���������
    void HighlightSymbol(int x, int y);

    // ���������� ������ ���������� ��������������� ����������
    int LastDigit();

    // ���������� true, ���� � ������� pos - ���������� �����
    bool CommaInPosition(int pos);
};


// ���������� ����������� Tuner
class TunerDisplay
{
public:
    TunerDisplay(ParameterValue *parameter) : param(parameter) { }

    void Draw();

    bool OnControlKey(const Control control);

private:
    ParameterValue *param;

    Indicator indicator;

    void DrawTitle(int x, int y, int width);

    void DrawValue(int x, int y);
};


// ������������ ��� ���������� ��������� ���������. �������� ��������������� ������ ParameterValue
class Tuner
{
public:

    Tuner(ParameterValue *param);

    void Draw();

    bool OnControlKey(const Control control);

private:

    ParameterValue *param;           // ������������� ��������

    TunerDisplay display;
};
