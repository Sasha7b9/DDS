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
    Value StepPosition(int pos);

    // �������� ���� � ��������� �� ������. ���������� true, ���� pos == 0
    bool ChangeSign(Value *value, int pos);

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
        EnterBuffer() : stack(30), param(nullptr)
        {
        }
        void Prepare(ParameterDouble *parameter);
        void Push(const Key::E key);
        // ������� ��������� ����������� ������
        void Pop();
        int Size() const;
        char At(const int i) const;
        // ���������� true, ���� ���������� ���������� �����
        bool ConsistComma() const;
        String ToString() const;

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
