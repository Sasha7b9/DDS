#pragma once
#include "Settings/SettingsTypes.h"


struct FloatValue;
class Parameter;


/// ��������������� ����� ��� ��������� �������� ���������
class ParameterPainterSupporting
{
public:
    ParameterPainterSupporting();
    /// ���������� ���������������� ���������
    void SetParameter(Parameter *param);
    /// ��������� ���������� �������������� ��������
    uint NumSymbols() const;
    /// ���������� ������� X ������� �� ������� pos ������������ 0-�� �������
    int X(uint pos) const;
    /// ���������� ������� Y ��������
    int Y() const;
    /// ���������� ������ � ������� pos
    char Symbol(uint pos) const;
    /// ���������� � �������� ������ ���� �������� ������
    int X0() const;
    /// ���������� Y �������� ������ ���� ������� ������
    int Y0() const;
    /// ������ ������� ������
    int Width() const;
    /// �������������� ��������
    Parameter *parameter;
    /// ������� �������� ��������� ������
    void SetActiveNext();
    /// ������� �������� ���������� ������
    void SetActivePrev();
    /// ���������� ������� ��������� �������
    uint GetPositionActive() const { return static_cast<uint>(positionActive); };

public:
    static const int NUM_SYMBOLS = 50;
    /// ����� �������� �������������� �������
    char buffer[NUM_SYMBOLS];
    /// ����� �������� ������� �������� �� FloatValue, ��������������� �������� �������� � buffer. ��� ���������� �������� == 255;
    int8 indexes[NUM_SYMBOLS];
    /// ������� ������� �������
    int x0;
    /// ������� ��������� �������
    int positionActive;
    /// ���������� ������� ������� ������� ������ ���������
    uint PositionFirstUnit() const;
    /// ��������������� ������� ��������� �������
    void InitPositionActive();
    /// ���������� true, ���� ������ � ������ ������� ����� ���� ���������
    bool PositionMayBeActived(int pos);
};


/// ��������� ������������ ��� ��������� �������� ���������
class ParameterPainter
{
public:
    static void SetPatameter(Parameter *param)
    {
        parameter = param;
    }

    /// ���������� ������ �������� ��������� �� ������ ��� ���������������. � ������� indexes ����������� ������� �������� ������������ ����� (� �������������, ��� ����� ����� ����� ������� � ������� �������)
    static pString DigitsWithSign(int8 *indexes);
    /// ���������� ������ � ��������� ���������
    static pString Units(Language::E lang = Language::RU);

private:
    static Parameter *parameter;
    /// ���������� ������ �������� ��������� ParameterValue
    static pString DigitsWithSignValue(int8 *indexes);
    /// ���������� ������ �������� ��������
    static pString DigitsWithSignOffset(int8 *indexes);
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
