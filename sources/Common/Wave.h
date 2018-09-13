#pragma once
#include "defines.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Order
{
    enum E
    {
        Nano,       // ����
        Micro,      // �����
        Milli,      // �����
        One,        // �������
        Kilo,       // ����
        Mega,       // ����
        Number
    } value;
    Order(E v = Number) : value(v)  { };
    operator uint8() const { return (uint8)value; };
    pString Name() const;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_DIGITS          5

class Form;

class Parameter
{
public:
    friend class Form;

    enum E
    {
        Frequency,          ///< �������
        Period,             ///< ������
        Amplitude,          ///< ���������
        Offset,             ///< ��������
        Duration,           ///< ������������
        DutyRatio,          ///< ����������
        Phase,              ///< ����� ����
        Delay,              ///< ��������
        DepthModulation,    ///< ������� ����������� ���������
        Polarity,           ///< ����������
        DurationRise,       ///< ������������ ����������
        DurationFall,       ///< ������������ �����
        DurationStady,      ///< ������������ ������������� ��������
        DutyFactor,         ///< ����������� ����������
        Modulation,         ///< ���������
        Number
    } value;

    Parameter(int v = Number) : value((E)v), inNumLockMode(false) {};

    Parameter(int v, float _min, float _max, pString buf, int8 pos, Order o, Parameter *param = 0, 
        int num = 0, int8 hd = NUM_DIGITS - 1, char s = ' ') :
        value((E)v), order(o), hightLightDigit(hd), posComma(pos), sign(s), min(_min), max(_max), inNumLockMode(false), params(param), numParams(num),
        parent(0)
    {
        strcpy(buffer, buf);
    };

    float MinValue() const { return min; };

    float MaxValue() const { return max; };

    float GetValue()  const;

    char *GetStringValue() const;

    pString Name() const;
    /// ���������� true, ���� �������� �������� ��������� ����������
    bool IsComplexParameter() const;

    bool InNumLockMode() const { return inNumLockMode; };

    void SetNumLockMode(bool mode) { inNumLockMode = mode; };
    /// ���������� true, ���� �������� ���������� ���� e
    bool Is(Parameter::E e) const { return value == e; };
    /// ���������� true, ���� �������� ��������������� �������� ���������
    bool IsInputValue() const { return !IsComplexParameter(); };
    /// ���������� ��������� �� �����, ���������� ������� ��������
    Form *GetForm() { return form; };
    /// ���������� ����� ������������� ���������
    Parameter *GetParent() { return parent; };
   
    Order order;
    /// ������� ������������� �������
    int8 hightLightDigit;
    /// ����� ����� ����� �������� �������
    int8 posComma;
    /// � ���� ������ �������� ���� �����, � ����� ����� � ������
    char buffer[NUM_DIGITS + 1];
    /// ���� �����. ' ' � ������, ���� ����� ����� �� ����� - ������ �������������
    char sign;
private:

    float min;

    float max;
    /// ���� true, �� ��������� � ������ ������������� ����� (�������� 1...9)
    bool inNumLockMode;
    /// ����� ��������� �������������� ��������� � ������, ���� ��� ���������
    Parameter *params;
    /// ����� �������������� ����������. 0, ���� ������� �� �������
    int numParams;
    /// ��������� �� ������, ������� ����������� ��������
    Form *form;
    /// ���� ���� �������� ���������, �� ����� ����� ��������
    Parameter *parent;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Form
{
public:
    enum E
    {
        Sine,       ///< �����
        RampPlus,   ///< ����+
        RampMinus,  ///< ����-
        Meander,    ///< ������
        Impulse,    ///< ��������
        Number
    } value;

    Form(E v = Number) : value(v), currentParam(0)   { };

    Form(E v, Parameter *param, int numParams);
    /// ���������� ������������ �������� ����� �������
    pString Name(Language lang) const;
    /// ���������� ������ �� ������� ��������
    Parameter *CurrentParameter();
    /// ���������� ���������� ��������� ����������
    int NumParameters() const;
    /// ���������� ������ �� i-�� �������� �� ������� params
    Parameter *GetParameter(int i);
    /// ���������� ������� �������� ��������
    void SetNextParameter();
    /// ����������� ��������� � ������������ � �������������� �����������
    void TuneGenerator(Chan ch);
    /// ���������� true, ���� ��� ����� ������� ������������� e
    bool Is(Form::E e) const { return e == value; };
    /// ���������� �������� �������� ���������
    void OpenCurrentParameter();
    /// ��������� �������� ��������, ���� ������� ������� � ���������� true � ���� ������
    bool CloseOpenedParameter();

private:
    /// ������� ��������� ��������. ���������� 0, ���� ������ ��������� ���
    Parameter *FindParameter(Parameter::E p);
    /// �������� �������� � ���������
    void SendParameterToGenerator(Chan ch, Parameter::E p);
    /// ����� �������� ���������
    Parameter *params;
    /// ������� ����� ����������
    int numParams;
    /// ����� �������� ��������� � ������� params
    int currentParam;
    /// ����� ����������� ��������� �� �������� ��������� � ������ ��������� �������� ���������
    Parameter *oldParams;
    /// ��������� � oldParams
    int oldNumParams;
    /// ��������� � oldParams
    int oldCurrentParams;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Wave
{
public:

    Wave(Chan ch, Form *forms, int numForms);
    /// ���������� ������������� �����
    Form *GetCurrentForm();
    /// ���������� ������� ��������� �����
    void SetNextForm();

    int NumberOfForms() const;

    Form *GetForm(int i);
    /// ������ ������ ����������� ������
    Chan channel;

private:
    /// ������� ����� ������� - ��������� �� ����� ������� � �������
    int currentForm;
    /// ������ ����, ������� ����� ���� ���������
    Form *forms;
    /// ���������� ��������� ����
    int numForms;

public:

    class Graphics
    {
    public:
        /// ���������� ���������� � ���������� ������� �� ������
        static void Draw(Chan ch);
        /// ������� x ������� ��������� �������
        static int X();
        /// ������� y ������� ��������� �������
        static int Y(Chan ch);
        /// ������ ������� ��������� �������
        static int Width();
        /// ������ ������� ��������� �������
        static int Height();
    private:

        static void DrawUGO(Chan chan, int y0);

        static void DrawSine(int x, int y, int width, int height);

        static void DrawRampPlus(int x, int y, int width, int height);

        static void DrawRampMinus(int x, int y, int width, int height);

        static void DrawMeander(int x, int y, int width, int height);

        static void DrawImpulse(int x, int y, int width, int height);

        static void DrawParameters(Chan chan, int y0);

        static void DrawParameterValue(Parameter *parameter, int x, int y);
    };
};
