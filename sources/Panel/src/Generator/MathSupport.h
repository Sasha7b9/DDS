#pragma once
#include "common/Common.h"


struct DoubleValue;
class Parameter;
class ParameterDouble;


struct MathDoubleValue
{
    // ���������� �������� ������������� DoubleValue � numDigits ��������� ������� � �������.
    static pString GetIndicatedValue(const ParameterDouble *param);

    // ���������� ������� ������� ���������� ������� "1" - ������� (1e1), "0" - ������� (1e0), "-1" - ������� (1e-1), "-2" - ����� (1e-2)
    static int GetPositionFirstDigit(const ParameterDouble *param, Order::E order = Order::Count);

    static int GetPositionFirstDigit(const DoubleValue &value, Order::E order);

    // ���������� ����� � ������� position. ����� ��������� �������������� order. One - ����� ������, Kilo - ����� ����� � ��� �����.
    // Order::Count - ��������� �� ��������� - ������� � ������� ������������ ����������� ��������� ��������
    static int GetDigit(const DoubleValue &value, int position, Order::E order = Order::Count);

    // ���������� ������ � ������� position. ���� �� �����������. ����� ��������� �������������� order. One - ����� ������, Kilo - ����� ����� � ��� �����.
    // Order::Count - ��������� �� ��������� - ������� � ������� ������������ ����������� ��������� ��������
    static char GetChar(const DoubleValue &value, int postition, Order::E order = Order::Count);

private:

    static void CorrectValueOnOrder(DoubleValue *value, Order::E order);
};


struct MathParameterValue
{
    static void SetParameterValue(ParameterDouble *parameter) { param = parameter; };

    // ���������� ���������� �������� ��������� ����� ������� (�������� �������� ������)
    static int GetNumberDigitsBeforeComma();

    // ���������� ���������� �������� ��������� ����� �������
    static int GetNumberDigitsAfterComma();

private:

    // ���������� ��������, �� �������� ����� ������������ ����������
    static ParameterDouble *param;
};
