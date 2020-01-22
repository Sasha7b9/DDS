#pragma once
#include "Settings/SettingsTypes.h"


struct FloatValue;
class Parameter;


class ParameterPainter
{
public:
    static void SetPatameter(Parameter *param)
    {
        parameter = param;
    }

    /// ���������� ������ �������� ��������� �� ������ ��� ���������������
    static pString DigitsWithSign();
    /// ���������� ������ � ��������� ���������
    static pString Units();

private:
    static Parameter *parameter;
    /// ���������� ������ �������� ��������
    static pString DigitsWithSignOffset();
    /// ���������� ������ �������� ��������� ParameterValue
    static pString DigitsWithSignValue();
};


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

    pString Suffix(Language::E lang) const;
};


struct MathFloatValue
{
    /// ���������� �������� ������������� FloatValue � numDigits ��������� ������� � �������. � order ����������� ������� ����� ������������ �������
    static pString GetStringValue(const FloatValue &value, bool sign, int numDigits, Order::E *order, int posFirst = 255);
    /// ���������� ������� ������� ���������� �������
    /// "1" - ������� (1e1), "0" - ������� (1e0), "-1" - ������� (1e-1), "-2" - ����� (1e-2)
    static int GetPositionFirstDigit(const FloatValue &value);
    /// ���������� ����� � ������� position
    static int GetDigit(const FloatValue &value, int position);
    /// ���������� ������ � ������� position
    static char GetChar(const FloatValue &value, int postition);
    /// ���������� ������� ������� ������������ ������� ������� ��������� �������
    static int PositionComma(int posFirstDigit, Order::E *order);
};
