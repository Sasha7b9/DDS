#pragma once
#include "Settings/SettingsTypes.h"
#include "Generator/Parameters.h"


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
    /// ���������� ������� X ������� � �������� pos
    int X(uint pos) const;
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
    /// ���������� ������� ��������� �������
    uint GetPositionActive() const { return static_cast<uint>(positionActive); };

    /// ������� �������� ��������� ������
    void SetActiveNext();
    /// ������� �������� ���������� ������
    void SetActivePrev();
    /// ��������� �������� � ������� �������
    void IncreaseInCurrentPosition();
    /// ��������� �������� � ������� ������e
    void DecreaseInCurrentPosition();
    /// ������ ���� �������
    int WidthDigit() const { return 11; };
    /// ������� ���� �������
    int HeightDigit() const { return 17; }

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
    /// ������ ������� �������� ���� ����� �, ���� ������� ���������� true
    bool ChangedSign();
};


/// ������������ ��� ��������� ��������� � ����������
class ParameterTuner
{
public:
    ParameterTuner() {}
    /// ���������� ��������, ���������� ���������
    void SetParameter(Parameter *param);
    /// ���������� ������� ����������. ���������� true, ���� ����������
    bool ProcessControl(const Key &key);
    /// ���������� �������� � ������ ���������
    void Draw();

private:
    ParameterPainterSupporting support;
    /// ���������� ��� ���������
    void DrawNameParameter();
    /// ���������� ��������
    void DrawParameter();
    /// ���������� �������������� � �������������� �������
    void DrawHighlighter();
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


struct LogicFloatValue
{
    static void SetParameter(Parameter *param);
    /// ������ ������� �������� ���� � ���������� true, ���� ��� ��������
    static bool ChangedSign();
    /// �������� �������� ����� � ������� pos, ��� pos - ����� ����������� �������, ������� �� 10e0
    static void ChangeDigit(int pos, int delta);

private:
    
    static FloatValue *value;

    static ParameterValue *parameter;
};
