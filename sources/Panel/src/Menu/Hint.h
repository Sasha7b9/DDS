#pragma once


class Hint
{
public:
    /// ���������� true, ���� ����� �������� ��������� �� �����
    static bool Show();
    /// ����������� ����� ��������� - ���� ���������� - �� ��������, � ��������
    static void Switch();

private:
    static bool show;
};
