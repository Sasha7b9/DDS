#pragma once


struct FloatValue;
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
};


struct MathFloatValue
{
    // ���������� �������� ������������� FloatValue � numDigits ��������� ������� � �������.
    static pString GetIndicatedValue(const ParameterValue *param);

    // ���������� ������� ������� ���������� ������� "1" - ������� (1e1), "0" - ������� (1e0), "-1" - ������� (1e-1), "-2" - ����� (1e-2)
    static int GetPositionFirstDigit(const FloatValue &value);

    // ���������� ����� � ������� position. ����� ��������� �������������� order. One - ����� ������, Kilo - ����� ����� � ��� �����.
    // Order::Count - ��������� �� ��������� - ������� � ������� ������������ ����������� ��������� ��������
    static int GetDigit(const FloatValue &value, int position, Order::E order = Order::Count);

    // ���������� ������ � ������� position. ���� �� �����������. ����� ��������� �������������� order. One - ����� ������, Kilo - ����� ����� � ��� �����.
    // Order::Count - ��������� �� ��������� - ������� � ������� ������������ ����������� ��������� ��������
    static char GetChar(const FloatValue &value, int postition, Order::E order = Order::Count);

    // ���������� ������� ������� ������������ ������� ������� ��������� �������
    static int PositionComma(int posFirstDigit);

    // ����������:
    // Order::Mega  - FloatValue::Integer() >= 1e6
    // Order::Kilo  - FloatValue::Integer() >= 1e3
    // Order::One   - FloatValue::Integer() >= 0
    // Order::Milli - FloatValue::Integer() >= 1e-3
    // Order::Micro - FloatValue::Integer() >= 1e-6
    static Order::E GetOrder(const FloatValue value);

private:

    static void CorrectValueOnOrder(FloatValue *value, Order::E order);
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
