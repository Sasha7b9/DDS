#pragma once

/*
    ����� ������������� ����� �������
*/


class Form
{
public:
    Form();
    void SetPoint(int mouseX, int mouseY);
    void Draw();
};


extern Form *TheForm;
