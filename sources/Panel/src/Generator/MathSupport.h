#pragma once


struct DoubleValue;
class Parameter;
class ParameterValue;


struct Order
{
    enum E
    {
        Mega,
        Kilo,
        One,
        Milli,
        Micro,
        Nano,
        Count
    };

    static pString Suffix(Order::E order, uint lang);

    // ���������� �������, �������������� �������
    static int GetPow10(Order::E order);
};


struct MathFloatValue
{
    // ���������� �������� ������������� DoubleValue � numDigits ��������� ������� � �������.
    static pString GetIndicatedValue(const ParameterValue *param);

    // ���������� ������� ������� ���������� ������� "1" - ������� (1e1), "0" - ������� (1e0), "-1" - ������� (1e-1), "-2" - ����� (1e-2)
    static int GetPositionFirstDigit(const ParameterValue *param, Order::E order = Order::Count);

    // ���������� ����� � ������� position. ����� ��������� �������������� order. One - ����� ������, Kilo - ����� ����� � ��� �����.
    // Order::Count - ��������� �� ��������� - ������� � ������� ������������ ����������� ��������� ��������
    static int GetDigit(const DoubleValue &value, int position, Order::E order = Order::Count);

    // ���������� ������ � ������� position. ���� �� �����������. ����� ��������� �������������� order. One - ����� ������, Kilo - ����� ����� � ��� �����.
    // Order::Count - ��������� �� ��������� - ������� � ������� ������������ ����������� ��������� ��������
    static char GetChar(const DoubleValue &value, int postition, Order::E order = Order::Count);

    // ����������:
    // Order::Mega  - DoubleValue::Integer() >= 1e6
    // Order::Kilo  - DoubleValue::Integer() >= 1e3
    // Order::One   - DoubleValue::Integer() >= 0
    // Order::Milli - DoubleValue::Integer() >= 1e-3
    // Order::Micro - DoubleValue::Integer() >= 1e-6
    static Order::E GetOrder(DoubleValue value);

private:

    static void CorrectValueOnOrder(DoubleValue *value, Order::E order);
};


struct MathParameterValue
{
    static void SetParameterValue(ParameterValue *parameter) { param = parameter; };

    // ���������� ���������� �������� ��������� ����� ������� (�������� �������� ������)
    static int GetNumberDigitsBeforeComma();

    // ���������� ���������� �������� ��������� ����� �������
    static int GetNumberDigitsAfterComma();

private:

    // ���������� ��������, �� �������� ����� ������������ ����������
    static ParameterValue *param;
};
