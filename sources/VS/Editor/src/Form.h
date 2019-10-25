#pragma once
#include "defines.h"

/*
    ����� ������������� ����� �������
*/


struct Align
{
    enum E
    {
        Left,
        Right,
        LeftTop,
        LeftDown,
        RightTop,
        RightDown
    };
};


class Form
{
public:
    Form();
    /// �������� ������
    void Clear();
    /// �������� ����� � ������������ ����
    void SetPoint(int mouseX, int mouseY);
    /// �������� ����� � ����������� ����������
    void SetPoint(uint16 pos, uint16 data);
    /// ���������� true, ���� ������ ���� ��������� ��� ������������ ������. Pressed - ������ �� ������ ����
    bool ExistPoint(int mouseX, int mouseY, bool pressed);
    /// ������� ����� � ������� ����
    void RemovePoint();
    /// ����������� ����� � ����� �������
    void MovePoint(int mouseX, int mouseY);
    /// ��������� �����
    void AlignPoint(Align::E align);

    void Draw();
};


extern Form *TheForm;
