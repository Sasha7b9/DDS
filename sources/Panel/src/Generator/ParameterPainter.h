#pragma once
#include "Settings/SettingsTypes.h"


struct FloatValue;
class Parameter;


/// ��������������� ����� ��� ��������� �������� ���������
class ParameterPainterSupporting
{
public:
    ParameterPainterSupporting(Parameter *param, int x, int width);
    /// ��������� ���������� �������������� ��������
    uint NumSymbols() const;
    /// ���������� ������� ������� �� ������� pos ������������ 0-�� �������
    int X(uint pos) const;
    /// ���������� ������ � ������� pos
    char Symbol(uint pos) const;
private:
    Parameter *parameter;
    char buffer[50];
    /// ���������� ������� ������� ������� ������ ���������
    uint PositionFirstUnit() const;
    /// ������� X ������� �������
    int x0;
};


/// ��������� ������������ ��� ��������� �������� ���������
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
    static pString Units(Language::E lang = Language::RU);

private:
    static Parameter *parameter;
    /// ���������� ������ �������� ��������� ParameterValue
    static pString DigitsWithSignValue();
    /// ���������� ������ �������� ��������
    static pString DigitsWithSignOffset();
    /// ���������� ������� ��������� ParameterValue
    static pString UnitsValue(Language::E lang = Language::RU);
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
