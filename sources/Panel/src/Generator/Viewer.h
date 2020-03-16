#pragma once


/*
    ������������ �������� ���������
*/


class Parameter;


class Viewer
{
public:

    Viewer(Parameter *param);

    // ���������� �������� � "��������" ����
    void Draw(int x, int y);

    // ���������� �������� � ������ ���������
    void DrawTuned();

private:

    void DrawParameterValue(int x, int y);

    Parameter *param;
};
