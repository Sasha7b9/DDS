#pragma once


/*
    ������������ ��� ��������� ���������
*/


class Parameter;
struct Key;


class Tuner
{
public:

    Tuner(Parameter *param);

    void Draw();

    bool OnKeyControl(const Key &control);

private:

    Parameter *param;           // ������������� ��������
};
