#pragma once
#include "Keyboard/Controls.h"


/*
    ������������ ��� ��������� ���������
*/


class Parameter;


class Title
{
public:
};


class Digit
{
public:
};


class Indicator
{
public:
    Indicator(Parameter *parameter) : param(parameter) { }

    void Draw();

private:
    Parameter *param;

    Title title;

    static const int MAX_NUM_DIGITS = 15;

    Digit digits[MAX_NUM_DIGITS];

    void DrawTitle(int x, int y, int width);

    void DrawValue();
};


class Tuner
{
public:

    Tuner(Parameter *param);

    void Draw();

    bool OnKeyControl(const Control control);

private:

    Parameter *param;           // ������������� ��������

    Indicator indicator;
};
