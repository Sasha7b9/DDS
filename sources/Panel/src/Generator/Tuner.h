#pragma once
#include "Display/Colors.h"
#include "Display/Text.h"
#include "Keyboard/Controls.h"
#include "Utils/Stack.h"


class ParameterDouble;
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

    bool IsNumber() const  { return (value >= '0' && value <= '9'); }

    bool IsEmpty() const   { return (value == '\0'); }

    bool IsSigned() const  { return (value == '-') || (value == '+'); }

private:

    char value;
};


// ���������� ����������, ����������� � �����������, � ������� ��� ������������� ��������� ����������
class Indicator
{
    friend class DisplayCorrection;

public:

    Indicator(DisplayCorrection *display);

    int Draw(int x, int y, int width);

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
    void HighlightSymbol(int x, int y) const;

    // ���������� �������������� ������ ������������� ������� (����� ������� � ������� digits)
    int IndexHighlightReal() const;

    // ���������� ��������, ������� ����� ���� ����������
    int NumberHighligthingDigits() const;

    // ���������� true, ���� � ������� pos - ���������� �����
    bool CommaInPosition(int pos) const;

    // ���������� ������� ������� � ������
    int PositionComma() const;

    // ���������� true, ���� � ������� pos - ������ �������� �����
    bool FirstSignedDigitInPosition(int pos) const;

    // ���������� ������� ���������� ����� ��������� ���������� �� pos. -1, ���� �������� �� �������.
    int FindPositionLeftDigit(int pos) const;

    // ������� �������� ������ ����� �� ��������
    void HighlightToLeft();

    // ������� �������� ������ ������ �� ��������
    void HighlightToRight();

    // ��������� �������� � ��������� �������
    void IncreaseInPosition(int pos);

    // ��������� �������� � ��������� �������
    void DecreaseInPosition(int pos);

    // ���������� true, ���� �������� �������� �� �������
    bool IsSigned() const;

    // ���������� "���� �������" � ������� pos
    Value StepPosition(int pos) const;

    // �������� ���� � ��������� �� ������. ���������� true, ���� pos == 0
    bool ChangeSign(Value *value, int pos);

    // ���������� ����, ������� ����� ������������ ������ � ������� pos
    Color CalculateColor(int pos) const;

    // ���������� true, ���� ����� �������������� �������� ����� ���������
    int AdditionShiftForDigit(int pos);

    // ���������� true, ���� ��� �������� ������� ����� ����� ����
    bool AllNumbersOfLeftIsZero(int pos) const;

    // true, ���� ������ �� pos ��������� �����
    bool RightDigitIzComma(int pos) const;
    
    // ���������� true, ���� ��� �������� ������� ������ ����� ����
    bool AllNumberOfRightIsZero(int pos) const;
};


// ����� ��� ����� � ����������� ���������
class DisplayEntering
{
public:
    
    // ��������� ������� ������� ������ ��������� ��������
    static bool OnEnteringKey(const Control &control);

    static void Draw(int x, int y, int width);

    // ���������� ������� ������ "��������� �������"
    static void OnButtonOrderMore();

    // ���������� ������� ������ "��������� �������"
    static void OnButtonOrderLess();

    static void Init();

    // ���������� ��������, ������� �������� ������ � DisplayEntering ( c ������ ������� )
    static Value ToValue();

    // ����� ��� �������� �������� ������ � ������ ����������������� �����
    class EnterBuffer
    {
    public:
        EnterBuffer() : stack(30), param(nullptr) { }
        void Prepare(ParameterDouble *parameter);
        void Push(const Key::E key);
        // ������� ��������� ����������� ������
        void Pop();
        int Size() const;
        char At(const int i) const;
        // ���������� true, ���� ���������� ���������� �����
        bool ConsistComma() const;
        String ToString() const;
        // ���������� true, ���� � ������ ��� ������, �����, ��������, �����
        bool IsEmpty() const;

    private:
        Stack<char> stack;
        ParameterDouble *param;
    };

    class Cursor
    {
    public:
        Cursor() : timeInit(0U) { }
        void Init();
        void Draw(int x, int y);
    private:
        uint timeInit;
    };

private:

    static Cursor cursor;               // �������� ������ ��� ������ ����������������� �����

    static EnterBuffer buffer;          // ����� ����� ������� ������� ������ � ������ �����

    static Order::E order;              // ������� ������� ��������� ��������

    static int DrawValue(int x, int y);

    static void DrawUnits(int x, int y, int width);

    // ������� �������� � ����� ����� ������, �������������� ������� ������
    static void TryToAddSymbol(Key::E key);

    // �������� �������� ��������� � ��������, ������������ ����������� � ������������ ���������� ParameterDouble
    static bool ValueInBoundaries();
};


// ���������� ����������� Tuner
class DisplayCorrection
{
    friend class Tuner;

public:
    
    DisplayCorrection(Tuner *tuner);

    void Init();

    void Init(Value value);

    void Draw();

    bool OnControlKey(const Control &control);

    // ����� ��������� � ������ �� ������� ����������� ���������, ���� ����������
    static void ShowMessageOutRangIfNeed(Value value);

    // ������������, � ������ ������� ����� �������� �������� ��� ��������� (��� ������� � ������� ������� ���������, � ��� ��������� � ���������� - ����������, ������ Order::One)
    static Order::E CalculateOrderForIndication();

private:

    Tuner *tuner;

    Indicator indicator;

    void DrawTitle(int x, int y, int width);

    void DrawUnits(int x, int y);

    // ��������� ������� ����� ����� ���������
    void FillDigitsIntegerPart();

    // ��������� ������� ������� ����� ���������
    void FillDigitsFractPart();
};


// ������������ ��� ���������� ��������� ���������. �������� ��������������� ������ ParameterDouble
class Tuner
{
public:

    struct ModeTuning
    {
        enum E
        {
            Correction,     // ����� ���������� �������� ��������� (������)
            Entering        // ����� ����� ��������
        };
    };

    Tuner(ParameterDouble *param);

    void Init();

    void Draw();

    bool OnControlKey(const Control control);

    // ���������� ������� ������ "������"
    void OnButtonCancel();

    // ���������� ������� ������ "���������"
    void OnButtonApply();

    ParameterDouble *GetParameter() { return param; }

    static bool InModeCorrection() { return (mode == ModeTuning::Correction); }

    static bool InModeEntering()   { return (mode == ModeTuning::Entering);   }

    static void SetModeEntering();

    static Tuner *Current() { return current; };

private:

    ParameterDouble *param;           // ������������� ��������

    DisplayCorrection display;

    static Tuner *current;

    static ModeTuning::E mode;                         // ������� ����� ���������
};
