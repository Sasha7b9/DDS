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
    } value;

    pString Suffix(uint lang) const;
};


struct MathFloatValue
{
    // ���������� �������� ������������� FloatValue � numDigits ��������� ������� � �������. � order ����������� ������� ����� ������������ �������
    static pString GetStringValue(const FloatValue &value, bool sign, int numDigits, Order::E *order, int posFirst = 255);

    // ���������� ������� ������� ���������� �������
    // "1" - ������� (1e1), "0" - ������� (1e0), "-1" - ������� (1e-1), "-2" - ����� (1e-2)
    static int GetPositionFirstDigit(const FloatValue &value);

    // ���������� ����� � ������� position
    static int GetDigit(const FloatValue &value, int position);

    // ���������� ������ � ������� position
    static char GetChar(const FloatValue &value, int postition);

    // ���������� ������� ������� ������������ ������� ������� ��������� �������
    static int PositionComma(int posFirstDigit, Order::E *order);
};


struct LogicFloatValue
{
    static void SetParameter(Parameter *param);

    // ������ ������� �������� ���� � ���������� true, ���� ��� ��������
    static bool ChangedSign();

    // �������� �������� ����� � ������� pos, ��� pos - ����� ����������� �������, ������� �� 10e0
    static void ChangeDigit(int pos, int delta);

private:

    static FloatValue *value;

    static ParameterValue *parameter;
};
