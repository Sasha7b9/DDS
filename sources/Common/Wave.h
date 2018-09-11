#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Wave
{
public:
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
        Form(E v = Number) : value((E)v) { };
        operator uint8() const           { return (uint8)value; };
        pString Name(Language lang) const;
        bool NameIsEqual(Form &form) const;

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

            Parameter(int v = Number) : value((E)v) { };
            operator uint8() const                  { return (uint8)value; }
            float MinValue() const;
            float MaxValue() const;
            pString Name() const;
            /// ���������� true, ���� �������� �������� ��������� ����������
            bool IsPage() const;
        } parameters[Wave::Form::Parameter::Number];

    } forms[Wave::Form::Number];

    /// ���������� ������������� �����
    Form GetCurrentForm();

    void SetCurrentForm(Wave::Form form);

    int NumberOfForms() const;

    Form GetForm(int i);

    Wave(Chan ch, Form form[Form::Number]);
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

        static void DrawParameterValue(Chan chan, Form::Parameter parameter, int x, int y);
    };
};
