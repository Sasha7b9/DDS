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

    void OnKeyControl(const Key &control);

private:

    Parameter *param;           // ������������� ��������
};
