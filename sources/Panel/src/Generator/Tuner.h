#pragma once
#include "Display/Colors.h"
#include "Keyboard/Controls.h"


class ParameterValue;
class Tuner;
class TunerDisplay;


class Digit
{
public:

    static const char COMMA = '.';

    Digit(char v = '0') : value(v) { }

    operator char() const { return value; }

    // ���������� ����� ��������
    void Set(char v) { value = v; }

    bool IsNumber()  { return (value >= '0' && value <= '9'); }

private:

    char value;
};


// ���������� ����������, ����������� � �����������, � ������� ��� ������������� ��������� ����������
class Indicator
{
    friend class TunerDisplay;

public:

    Indicator(TunerDisplay *display);

    int Draw(int x, int y);

    bool OnControlKey(const Control control);

    // ���������� ������ ��������
    char *GetStringDigits() const;

    void InitHighlight();

    static const int MAX_NUM_DIGITS = 25;

private:

    Digit digits[MAX_NUM_DIGITS];           // ����� ��������� ��� �������

    int indexHighlight;                     // ������ ������������� ����������

    TunerDisplay *display;

    // ���������� ������ ���������
    void HighlightSymbol(int x, int y);

    // ���������� ������ ���������� ��������������� ����������
    int LastDigit();

    // ���������� true, ���� � ������� pos - ���������� �����
    bool CommaInPosition(int pos);

    // ���������� ������� ������� � ������
    int PositionComma();

    // ���������� true, ���� � ������� pos - ������ �������� �����
    bool FirstSignedDigitInPosition(int pos);

    // ���������� ������� ���������� ����� ��������� ���������� �� pos. -1, ���� �������� �� �������.
    int FindPositionLeftDigit(int pos);

    // ������� �������� ������ ����� �� ��������
    void HighlightToLeft();

    // ������� �������� ������ ������ �� ��������
    void HighlightToRight();

    // ��������� �������� � ��������� �������
    void IncreaseInPosition(int pos);

    // ��������� �������� � ��������� �������
    void DecreaseInPosition(int pos);

    // ���������� true, ���� �������� �������� �� �������
    bool IsSigned();

    // ���������� "���� �������" � ������� pos
    DoubleValue StepPosition(int pos);

    // �������� ���� � ��������� �� ������. ���������� true, ���� pos == 0
    bool ChangeSign(DoubleValue *value, int pos);

    Color CalculateColor(int pos, bool *fullFill);

    // ���������� true, ���� ����� �������������� �������� ����� ���������
    int AdditionShiftForDigit(int pos);
};


// ���������� ����������� Tuner
class TunerDisplay
{
    friend class Tuner;

public:
    TunerDisplay(Tuner *tuner);

    void Init();

    void Init(DoubleValue value);

    void Draw();

    bool OnControlKey(const Control control);

    Tuner *GetTuner() { return tuner; }

    DoubleValue GetValue() const;

private:
    Tuner *tuner;

    Indicator indicator;

    void DrawTitle(int x, int y, int width);

    // ���������� x �� ����������� ���������
    int DrawValue(int x, int y);

    void DrawUnits(int x, int y);

    // ��������� ������� ����� ����� ���������
    void FillDigitsIntegerPart();

    // ��������� ������� ������� ����� ���������
    void FillDigitsFractPart();
};


// ������������ ��� ���������� ��������� ���������. �������� ��������������� ������ ParameterValue
class Tuner
{

public:

    Tuner(ParameterValue *param);

    void Init();

    void Draw();

    bool OnControlKey(const Control control);

    ParameterValue *GetParameter() { return param; }

private:

    ParameterValue *param;           // ������������� ��������

    TunerDisplay display;
};
