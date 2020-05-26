#pragma once
#include "Keyboard/Controls.h"


class ParameterValue;
class Tuner;


class Digit
{
public:

    static const char COMMA = '.';

    Digit(char v = '0') : value(v) { }

    operator char() { return value; }

    // ��������� �������� � �������. ���� ���������� (����� '9') - ��������� false
    bool Increase();

    // ��������� �������� � �������. ���� ���������� (����� '0') - ���������� false
    bool Decrease();

    // ���������� ����� ��������
    void Set(char v) { value = v; }

    bool IsDigit()
    {
        return (value >= '0' && value <= '9');
    }

private:

    char value;
};


// ���������� ����������, ����������� � �����������, � ������� ��� ������������� ��������� ����������
class Indicator
{
public:

    Indicator();

    void Draw(int x, int y);

    bool OnControlKey(const Control control);

    Digit *Digits() { return digits; }

private:

    static const int MAX_NUM_DIGITS = 25;

    Digit digits[MAX_NUM_DIGITS];           // ����� ��������� ��� �������

    int indexHighlight;                     // ������ ������������� ����������

    // ���������� ������ ���������
    void HighlightSymbol(int x, int y);

    // ���������� ������ ���������� ��������������� ����������
    int LastDigit();

    // ���������� true, ���� � ������� pos - ���������� �����
    bool CommaInPosition(int pos);

    // ���������� true, ���� � ������� pos - ������ �������� �����
    bool FirstSignedDigitInPosition(int pos);

    // ���������� ������� ���������� ����� ��������� ���������� �� pos. -1, ���� �������� �� �������
    int FindPositionLeftDigit(int pos);

    // ������� �������� ������ ����� �� ��������
    void HighlightToLeft();

    // ������� �������� ������ ������ �� ��������
    void HighlightToRight();

    // ��������� �������� � ��������� �������
    void IncreaseInPosition(int pos);

    // ��������� �������� � ��������� �������
    void DecreaseInPosition(int pos);

    // ���������� true, ���� �������� ���������� pos ����� ���� ���������
    bool CanBeDecreased(int pos);

    // ���������� true, ���� �������� ���������� pos ����� ���� ���������
    bool CanBeIncreased(int pos);
};


// ���������� ����������� Tuner
class TunerDisplay
{
public:
    TunerDisplay(Tuner *tuner);

    void Init();

    void Draw();

    bool OnControlKey(const Control control);

private:
    Tuner *tuner;

    Indicator indicator;

    void DrawTitle(int x, int y, int width);

    void DrawValue(int x, int y);
};


// ������������ ��� ���������� ��������� ���������. �������� ��������������� ������ ParameterValue
class Tuner
{

public:

    Tuner(ParameterValue *param);

    void Init();

    void Draw();

    bool OnControlKey(const Control control);

    ParameterValue *Parameter() { return param; }

private:

    ParameterValue *param;           // ������������� ��������

    TunerDisplay display;
};
