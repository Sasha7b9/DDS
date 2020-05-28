#pragma once
#include "Display/Colors.h"
#include "Keyboard/Controls.h"


class ParameterValue;
class Tuner;
class DisplayCorrection;


class Digit
{
public:

    static const char COMMA = '.';

    Digit(char v = '0') : value(v) { }

    operator char() const { return value; }

    // ���������� ����� ��������
    void Set(char v) { value = v; }

    bool IsNumber()  { return (value >= '0' && value <= '9'); }

    bool IsEmpty()   { return (value == '\0'); }

    bool IsSigned()  { return (value == '-') || (value == '+'); }

private:

    char value;
};


// ���������� ����������, ����������� � �����������, � ������� ��� ������������� ��������� ����������
class Indicator
{
    friend class DisplayCorrection;

public:

    Indicator(DisplayCorrection *display);

    int Draw(int x, int y);

    bool OnControlKey(const Control control);

    // ���������� ������ ��������
    char *GetStringDigits() const;

    void InitHighlight();

    static const int MAX_NUM_DIGITS = 25;

private:

    Digit digits[MAX_NUM_DIGITS];           // ����� ��������� ��� �������

    int indexHighlight;                     // ������ ������������� ����������. ���� ������ ������ �� �������� � �������� ��������

    DisplayCorrection *display;

    // ���������� ������ ���������
    void HighlightSymbol(int x, int y);

    // ���������� �������������� ������ ������������� ������� (����� ������� � ������� digits)
    int IndexHighlightReal();

    // ���������� ��������, ������� ����� ���� ����������
    int NumberHighligthingDigits();

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

    Color CalculateColor(int pos);

    // ���������� true, ���� ����� �������������� �������� ����� ���������
    int AdditionShiftForDigit(int pos);

    // ���������� true, ���� ��� �������� ������� ����� ����� ����
    bool AllNumbersOfLeftIsZero(int pos);
    
    // ���������� true, ���� ��� �������� ������� ������ ����� ����
    bool AllNumberOfRightIsZero(int pos);
};


// ����� ��� ����� � ����������� ���������
class DisplayEntering
{
public:
    
    // ��������� ������� ������� ������ ��������� ��������
    static bool OnEnteringKey(const Control &control);

    static void Draw(int x, int y, int width);

private:

    static int DrawValue(int x, int y);

    static void DrawUnits(int x, int y, int width);
};


// ���������� ����������� Tuner
class DisplayCorrection
{
    friend class Tuner;

public:
    
    enum ModeTuning
    {
        Correction,     // ����� ���������� �������� ��������� (������)
        Entering        // ����� ����� ��������
    };

    DisplayCorrection(Tuner *tuner);

    void Init();

    void Init(DoubleValue value);

    void Draw();

    bool OnControlKey(const Control &control);

    static bool InModeCorrection() { return (mode == Correction); }

    static void SetModeEntering();

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

    static ModeTuning mode;                         // ������� ����� ���������
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

    static Tuner *Current() { return current; };

private:

    ParameterValue *param;           // ������������� ��������

    DisplayCorrection display;

    static Tuner *current;
};
