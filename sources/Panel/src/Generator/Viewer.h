#pragma once


/*
    ������������ �������� ���������
*/


class Parameter;


class Viewer
{
public:
    static void Draw(Parameter *param, int x, int y);

private:
    static void DrawParameterValue(Parameter *param, int x, int y);
};
