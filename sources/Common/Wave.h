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
    Order& operator++(int)
    {
        value = (E)(value + 1);
        return *this;
    }
    Order& operator--(int)
    {
        value = (E)(value - 1);
        return *this;
    }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_DIGITS          5

class Form;
class Wave;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    
    bool IsComplex() const;

    bool IsExit() const;

    pString Name() const;

    pString GetStringValue() const;

    pString NameUnit(char buffer[10]) const;

protected:
    /// ��������� �� ������, ������� ����������� ��������
    Form *form;

    ParameterBase(Type t) : type(t), parent(0) {};

    Type type;
    /// ���� ���� �������� ���������, �� ����� ����� ��������
    ParameterBase *parent;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (*funcDraw)(int, int);

class ParameterChoice : public ParameterBase
{
public:
    friend class Form;

    enum E
    {
        Polarity,           ///< ���������� ���������
        ModeStart,          ///< ����� �������
        ModeManipulation,   ///< ����� ����������� ����������� - �� ������������ ������ ��� ���
        Number
    } value;

    pString Name() const;

    ParameterChoice(E v, pString var0ru, pString var0en,
                    pString var1ru, pString var1en, funcDraw func0 = 0, funcDraw func1 = 0) : 
        ParameterBase(Choice), value(v), choice(0), num(2)
    {
        names[0][0] = (char *)var0ru;
        names[0][1] = (char *)var0en;
        names[1][0] = (char *)var1ru;
        names[1][1] = (char *)var1en;

        func[0] = func0;
        func[1] = func1;
    };

    ParameterChoice(E v, pString var0ru, pString var0en, pString var1ru, pString var1en, 
                    pString var2ru, pString var2en, pString var3ru, pString var3en) : ParameterBase(Choice), value(v), choice(0), num(4)
    {
        names[0][0] = (char *)var0ru;
        names[0][1] = (char *)var0en;
        names[1][0] = (char *)var1ru;
        names[1][1] = (char *)var1en;
        names[2][0] = (char *)var2ru;
        names[2][1] = (char *)var2en;
        names[3][0] = (char *)var3ru;
        names[3][1] = (char *)var3en;
    }

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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        Manipulation,           ///< ��������� ����� ��� ���������
        ManipulationDuration,   ///< ������������ ��������� � ������ �����������
        ManipulationPeriod,     ///< ������ ���������� ��������� � ������ �����������
        PacketPeriod,           ///< ������ ���������� ����� ��������� � �������� ������
        PacketNumber,           ///< ����� ��������� � ����� ��������� ������
        Exit,                   ///< ���� �������� ��������� �������� ��������
        Number
    } value;

    ParameterValue(int v = Number) : ParameterBase(Value), value((E)v), inNumLockMode(false) {};

    ParameterValue(int v, float _min, float _max, pString buf, int8 pos, Order o, ParameterBase *param[] = 0, int8 hd = NUM_DIGITS - 1, char s = ' ') : 
        ParameterBase(Value),
        value((E)v), order(o), hightLightDigit(hd), posComma(pos), sign(s), min(_min), max(_max), inNumLockMode(false), params(param)
    {
        strcpy(buffer, buf);
        numParams = 0;
        if(param)
        {
            while(params[numParams])
            {
                numParams++;
            }
        }
    };

    bool Is(ParameterValue::E v) { return value == v; };

    float MinValue() const { return min; };

    float MaxValue() const { return max; };

    float GetValue() const;

    pString GetStringValue() const;

    pString Name() const;
    /// ���������� true, ���� �������� �������� ��������� ����������
    bool IsComplex() const;

    bool InNumLockMode() const { return inNumLockMode; };

    void SetNumLockMode(bool mode) { inNumLockMode = mode; };
    /// ���������� true, ���� �������� ���������� ���� e
    bool Is(ParameterValue::E e) const { return value == e; };
    /// ���������� true, ���� �������� ��������������� �������� ���������
    bool IsInputValue() const { return IsValue() && value != Manipulation && value != Exit; };
    /// ���������� true, ���� ���� �������� - ������ ������.
    bool IsExit() const { return value == Exit; };
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
    /// ����� ��������� �������������� ��������� � ������, ���� ��� ���������
    ParameterBase **params;
    /// ����� �������������� ����������. 0, ���� ������� �� �������
    int numParams;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Form
{
    friend class Wave;

public:
    enum E
    {
        Sine,           ///< �����
        RampPlus,       ///< ����+
        RampMinus,      ///< ����-
        Meander,        ///< ������
        Impulse,        ///< ��������
        PacketImpuls,   ///< ����� ���������
        Number
    } value;

    Form(E v = Number) : value(v), wave(0), currentParam(0)   { };

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

        static void DrawMeander(Chan ch, int x, int y, int width, int height);

        static void DrawImpulse(Chan ch, int x, int y, int width, int height);

        static void DrawPacketImpulse(Chan ch, int x, int y, int width, int height);

        static void DrawParameters(Chan chan, int y0);

        static void DrawParameterValue(ParameterBase *parameter, int x, int y);
    };
};
