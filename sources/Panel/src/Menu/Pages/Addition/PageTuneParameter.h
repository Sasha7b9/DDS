#pragma once


class Parameter;


struct PageTuneParameter
{
    static Page *self;

    // ������������� �������� ��� ��������������
    static void SetParameter(ParameterValue *);

    // ���������� ����� ����� ��������
    static void SetModeEntering();

    // �������� ����� ����� ��������
    static void ResetModeEntering();
};
