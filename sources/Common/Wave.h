#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Parameter
{
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

    Parameter(int v = Number) : value((E)v) {};

    Parameter(int v, float _min, float _max) : value((E)v), min(_min), max(_max) { };

    operator uint8() const                  { return (uint8)value; }

    float MinValue() const;

    float MaxValue() const;

    pString Name() const;
    /// ���������� true, ���� �������� �������� ��������� ����������
    bool IsPage() const;
private:

    float min;

    float max;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Form
{
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
    Form(E v, Parameter param[Parameter::Number]);
    operator uint8() const    { return (uint8)value;  };
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
    /// ����� �������� ��������� � ������� params
    int currentParam;

    Parameter params[Parameter::Number];
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Wave
{
public:

    Wave(Chan ch, Form form[Form::Number]);

    Form forms[Form::Number];

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

        static void DrawParameterValue(Chan chan, Parameter *parameter, int x, int y);
    };
};
