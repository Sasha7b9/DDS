#pragma once
#include "Keyboard/Controls.h"


/*
    ������������ ��� ��������� ���������
*/


class Parameter;


class Tuner
{
public:

    Tuner(Parameter *param);

    void Draw();

    bool OnKeyControl(const Control control);

private:

    Parameter *param;           // ������������� ��������
};
