#pragma once


/*
    ������������ �������� ���������
*/


class Parameter;


class Viewer
{
public:

    Viewer(Parameter *param);

    // ���������� �������� �� ��������� � ����������� y. �������� ��������� ��������� � xName, �������� - � xValue, ������� ��������� - c xUnits
    void Draw(int y, int xName, int xValue, int xUnits);

private:

    void DrawDoubleValue(int y, int xValue, int xUnits);

    void DrawChoiceValue(int y, int xValue, int xUnits);

    void DrawCompositeValue(int y, int xValue, int xUnits);

    void DrawButton(int y, int xValue, int xUnits);

    void DrawIntegerValue(int y, int xValue, int xUnits);

    Parameter *param;
};
