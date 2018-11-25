#pragma once
#include "defines.h"
#include <cstring>
#include <limits>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    Order& operator++(int);
    Order& operator--(int);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_DIGITS          5

class Form;
class Wave;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ParameterBase
{
    friend class Form;

public:
    
    enum Type
    {
        Value,
        Exit,
        Choice,
        Complex
    };

    /// ���������� ��������� �� �����, ���������� ������� ��������
    Form *GetForm() { return form; };
    /// ���������� ����� ������������� ���������
    ParameterBase *GetParent() { return parent; };

    bool IsValue() const { return type == Value; }

    bool IsChoice() const { return type == Choice; }
    
    bool IsComplex() const { return type == Complex; };

    bool IsExit() const;

    pString Name() const;

    pString GetStringValue() const;

    pString NameUnit(char buffer[10]) const;

protected:
    /// ��������� �� ������, ������� ����������� ��������
    Form *form;

    ParameterBase(Type t) : form(0), type(t), parent(0) {};

    Type type;
    /// ���� ���� �������� ���������, �� ����� ����� ��������
    ParameterBase *parent;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (*funcDraw)(int, int);

class ParameterChoice : public ParameterBase
{
public:
    friend class Form;

    enum E
    {
        Polarity,               ///< ���������� ���������
        ModeStart,              ///< ����� ������� �������� DDS � ����������
        ManipulationMode,       ///< ����� ����������� ����������� - �� ������������ ������ ��� ���
        ManipulationEnabled,    ///< ������� ��� �������� ����� �����������
        Number
    } value;

    pString Name() const;

    ParameterChoice(E v, pString var0ru, pString var0en, pString var1ru, pString var1en, funcDraw func0 = 0, funcDraw func1 = 0);

    ParameterChoice(E v, pString var0ru, pString var0en, pString var1ru, pString var1en, 
                         pString var2ru, pString var2en, pString var3ru, pString var3en);

    pString GetStringValue() const;

    void NextChoice();

    int GetChoice() const { return choice; };
    /// ���������� ������� ������� � ��������� �����������
    bool DrawChoice(int x, int y);

private:
    /// ������� �������
    int choice;
    /// ���������� ���������
    int num;
    /// �������� �� ������� �����
    char *names[4][2];

    funcDraw func[4];
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ParameterComplex : public ParameterBase
{
    friend class Form;
public:

    enum E
    {
        Manipulation,
        Number
    } value;

    ParameterComplex(ParameterBase *param[]);

    pString Name() const;
    
    pString GetStringValue() const;

    bool Is(E v) const { return value == v; };

private:
    /// ����� ��������� �������������� ��������� � ������, ���� ��� ���������
    ParameterBase **params;
    /// ����� �������������� ����������. 0, ���� ������� �� �������
    int numParams;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ParameterValue : public ParameterBase
{
public:
    friend class Form;

    enum E
    {
        Frequency,              ///< �������
        Period,                 ///< ������
        Amplitude,              ///< ���������
        Offset,                 ///< ��������
        Duration,               ///< ������������
        DutyRatio,              ///< ����������
        Phase,                  ///< ����� ����
        Delay,                  ///< ��������
        DurationRise,           ///< ������������ ����������
        DurationFall,           ///< ������������ �����
        DurationStady,          ///< ������������ ������������� ��������
        DutyFactor,             ///< ����������� ����������
        ManipulationDuration,   ///< ������������ ��������� � ������ �����������
        ManipulationPeriod,     ///< ������ ���������� ��������� � ������ �����������
        PacketPeriod,           ///< ������ ���������� ����� ��������� � �������� ������
        PacketNumber,           ///< ����� ��������� � ����� ��������� ������
        Exit,                   ///< ���� �������� ��������� �������� ��������
        Number
    } value;

    ParameterValue(int v = Number) : ParameterBase(Value),
        value((E)v),
        hightLightDigit(0),
        posComma(0),
        sign('+'),
        /// \todo �� ���������� ��� ������-��
        //min(std::numeric_limits<float>::min()),
        //max(std::numeric_limits<float>::max()),
        //min(-1e30f),
        //max(1e30f),
        inNumLockMode(false)
    {};

    ParameterValue(int v, float _min, float _max, pString buf, int8 pos, Order o, int8 hd = NUM_DIGITS - 1, char s = ' ');

    bool Is(ParameterValue::E v) { return value == v; };

    float MinValue() const { return min; };

    float MaxValue() const { return max; };

    float GetValue() const;

    pString GetStringValue() const;

    pString Name() const;
    /// ���������� true, ���� �������� ���������� ���� e
    bool Is(ParameterValue::E e) const { return value == e; };
    /// ���������� true, ���� ���� �������� - ������ ������.
    bool IsExit() const { return value == Exit; };

    bool IsInputValue() const { return IsValue() && value != Exit; };
    /// ���������� true, ���� ������� � ������
    bool IsOpened();

    pString NameUnit(char buffer[10]) const;
   
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
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Form
{
    friend class Wave;

public:
    enum E
    {
        Sine,           ///< �����
        RampPlus,       ///< ����+
        RampMinus,      ///< ����-
        Triangle,       ///< �����������
        Meander,        ///< ������
        Impulse,        ///< ��������
        PacketImpuls,   ///< ����� ���������
        DDS,            ///< ������������ ������
        Number
    } value;

    Form(E v = Number) :
        value(v),
        wave(0),
        currentParam(0),
        oldParams(0),
        oldNumParams(0),
        oldCurrentParams(0)
    { };

    Form(E v, ParameterBase *param[], Wave *w);
    /// ���������� ������������ �������� ����� �������
    pString Name(Language lang) const;
    /// ���������� ������ �� ������� ��������
    ParameterBase *CurrentParameter();
    /// ���������� ���������� ��������� ����������
    int NumParameters() const;
    /// ���������� ������ �� i-�� �������� �� ������� params
    ParameterBase *GetParameter(int i);
    /// ���������� ������� �������� ��������
    void SetNextParameter();
    /// ����������� ��������� � ������������ � �������������� �����������
    void TuneGenerator(Chan ch);
    /// ���������� true, ���� ��� ����� ������� ������������� e
    bool Is(Form::E e) const { return e == value; };
    /// ���������� true, ���� ����� ������� ����������� � ������� ����
    bool IsDDS() const;
    /// ���������� ��������� �� ������������ Wave
    Wave *GetWave() { return wave; };
    /// ���������� true, ���� ������� �������� ������� � ������.
    bool ParameterIsOpened() const;
    /// ������� ���������� ��� ������� ������ "�������� ��������". ���������� ������������ ������� ��������
    void ChangeParameter();
    /// ��������� �������� ��������, ���� ������� ������� � ���������� true � ���� ������
    bool CloseOpenedParameter();
private:
    /// ������� ��������� ��������. ���������� 0, ���� ������ ��������� ���
    ParameterBase *FindParameter(ParameterValue::E p);
    ParameterBase *FindParameter(ParameterChoice::E p);
    /// �������� �������� � ���������
    void SendParameterToGenerator(ParameterValue::E p);
    void SendParameterToGenerator(ParameterChoice::E p);
    /// ���������� �������� �������� ���������
    void OpenCurrentParameter();
    /// Wave, � �������� ��������� ������ Form
    Wave *wave;
    /// ����� �������� ���������
    ParameterBase **params;
    /// ������� ����� ����������
    int numParams;
    /// ����� �������� ��������� � ������� params
    int currentParam;

    /// ����� ����������� ��������� �� �������� ��������� � ������ ��������� �������� ���������
    ParameterBase **oldParams;
    /// ��������� � oldParams
    int oldNumParams;
    /// ��������� � oldParams
    int oldCurrentParams;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Wave
{
public:

    Wave(Chan ch, Form *forms, int numForms);
    /// ���������� ������������� �����
    Form *GetCurrentForm();
    /// ���������� ������� ��������� �����
    void SetForm(int8 num);

    int NumberOfForms() const;

    Form *GetForm(int i);

    Form *GetForm(Form::E form);

    Chan GetChannel() const { return channel; };
    /// ���������� true, ���� ���������� ������ ����� �������
    bool StartModeIsSingle();

private:
    /// ������ ������ ����������� ������
    Chan channel;
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

        static void DrawSine(Chan ch, int x, int y, int width, int height);

        static void DrawRampPlus(Chan ch, int x, int y, int width, int height);

        static void DrawRampMinus(Chan ch, int x, int y, int width, int height);

        static void DrawTriangle(Chan ch, int x, int y, int width, int height);

        static void DrawMeander(Chan ch, int x, int y, int width, int height);

        static void DrawImpulse(Chan ch, int x, int y, int width, int height);

        static void DrawPacketImpulse(Chan ch, int x, int y, int width, int height);

        static void DrawDDS(Chan ch, int x, int y, int width, int height);

        static void DrawParameters(Chan chan, int y0);

        static void DrawParameterValue(ParameterBase *parameter, int x, int y);
    };
};
