#pragma once
#include "Keyboard/Controls.h"


class ParameterValue;


class Digit
{
    friend class Indicator;

public:

    Digit(char v = '0') : value(v) { }

private:

    char value;
};


// ���������� ����������, ����������� � �����������, � ������� ��� ������������� ��������� ����������
class Indicator
{
public:

    Indicator();

    void Draw(int x, int y);

private:

    static const int MAX_NUM_DIGITS = 15;

    Digit digits[MAX_NUM_DIGITS];           // ����� ��������� ��� �������

    int indexHighlight;                     // ������ ������������� ����������

    // ���������� ������ ���������
    void HighlightSymbol(int x, int y);
};


// ���������� ����������� Tuner
class TunerDisplay
{
public:
    TunerDisplay(ParameterValue *parameter) : param(parameter) { }

    void Draw();

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

    bool OnKeyControl(const Control control);

private:

    ParameterValue *param;           // ������������� ��������

    TunerDisplay display;
};
