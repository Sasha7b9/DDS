#pragma once


/*
    ������������ �������� ���������
*/


class Parameter;


class Viewer
{
public:
    void Draw(Parameter *param, int x, int y);

private:
    void DrawParameterValue(Parameter *param, int x, int y);
};
