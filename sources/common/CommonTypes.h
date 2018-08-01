#pragma once


enum Channel
{
    A,
    B,
    NumChannels
};

/// ������������� ����� �����������
enum FreqResist
{
    FreqResist_1MOhm,
    FreqResist_50Ohm
};

/// ��������/�������� ���� �����������
enum FreqCouple
{
    FreqCouple_AC,
    FreqCouple_DC
};

/// ��� �����������
enum FreqFiltr
{
    FreqFiltr_Enable,
    FreqFiltr_Disable
};
