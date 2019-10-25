#pragma once
#include "defines.h"

/*
    ����� ������������� ����� �������
*/


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

    void Draw();
};


extern Form *TheForm;
