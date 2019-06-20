#pragma once
#include "defines.h"
#include <cstring>
#include <limits>
#include "Common.h"


class ParameterValue;


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
        Count
    } value;
    Order(E v = Count) : value(v)  { };
    operator uint8() const { return (uint8)value; };
    pString Name() const;
    Order& operator++(int);
    Order& operator--(int);
    static Order::E Min(ParameterValue *param);
    static Order::E Max(ParameterValue *param);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Form;
class Wave;
class PageBase;


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
        Complex,
        Page
    };

    /// ���������� ��������� �� �����, ���������� ������� ��������
    Form *GetForm() { return form; }
    /// ���������� ����� ������������� ���������
    ParameterBase *GetParent() { return parent; }

    bool IsValue() const { return type == Value; }

    bool IsChoice() const { return type == Choice; }
    
    bool IsComplex() const { return type == Complex; }

    bool IsPage() const { return type == Page; }

    bool IsExit() const;

    pString Name() const;

    pString GetStringValue() const;

    pString NameUnit(char buffer[10]) const;
    /// ���������� true, ���� ��������� ����� �������� �������
    bool AssumeArbitaryOrder() const;

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
        Count
    } value;

    pString Name() const;

    ParameterChoice(E v, pString var0, pString var1, funcDraw func0 = 0, funcDraw func1 = 0);

    ParameterChoice(E v, pString var0, pString var1, pString var2, pString var3);

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
    char *names[4];

    funcDraw func[4];
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ParameterComplex : public ParameterBase
{
    friend class Form;
public:

    enum E
    {
        Manipulation,       ///< ��������� �������� / �������� / ����������� �� ����� �����
        Count
    } value;

    ParameterComplex(E v, ParameterBase **param);

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
class ParameterPage : public ParameterBase
{
    friend class Form;
public:

    enum E
    {
        ChoiceForm,         ///< ��������� �������� / �������� / ����� �� ����� ������������
        Count
    } value;

    ParameterPage(E v, PageBase *p) : ParameterBase(Page), value(v), page(p) {};

    pString Name() const;

private:
    PageBase *page;

    void OpenPage();
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ParameterValue : public ParameterBase
{
private:
    static int const NUM_DIGITS = 5;
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
        Count
    } value;

    ParameterValue(int v = Count);

    ParameterValue(int v, float _min, float _max, pString buf, int8 pos, Order o, int8 hd = NUM_DIGITS - 1, char s = ' ');

    bool Is(ParameterValue::E v) { return value == v; };

    float MinValue() const { return min; };

    float MaxValue() const { return max; };

    ParamValue GetValueNano() const;

    pString GetStringValue() const;
    /// ��������� �������
    void IncreaseOrder();
    /// ��������� �������
    void DecreaseOrder();

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

    int numDigits;

    /// ���������� true, ���� ������� �������� ��������� ����� ���� ������
    bool AssumeArbitaryOrder() const;
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
        Count
    } value;

    Form(E v = Count) :
        value(v),
        wave(0),
		params(nullptr),
		numParams(0),
        currentParam(0),
        oldParams(0),
        oldNumParams(0),
        oldCurrentParams(0)
    { };

    Form(E v, ParameterBase **param, Wave *w);
    /// ���������� ������������ �������� ����� �������
    pString Name() const;
    /// ���������� ������ �� ������� ��������
    ParameterBase *CurrentParameter();
    /// ���������� ���������� ��������� ����������
    int NumParameters() const;
    /// ���������� ������ �� i-�� �������� �� ������� params
    ParameterBase *GetParameter(int i);
    /// ���������� ������� �������� ��������
    void SetNextParameter();
    /// ����������� ��������� � ������������ � �������������� �����������
    void TuneGenerator(Chan::E ch);
    /// ���������� true, ���� ��� ����� ������� ������������� e
    bool Is(Form::E e) const { return e == value; };
    /// ���������� true, ���� ����� ������� ����������� � ������� ����
    bool IsDDS() const;
    /// ���������� ��������� �� ������������ Wave
    Wave *GetWave() { return wave; };
    /// ���������� true, ���� ������� �������� ������� � ������.
    bool ParameterIsOpened() const;

    ParameterValue *GetParameterValue(ParameterValue::E value);
    /// ������� ���������� ��� ������� ������ "�������� ��������". ���������� ������������ ������� ��������
    void ChangeParameter();
    /// ��������� �������� ��������, ���� ������� ������� � ���������� true � ���� ������
    bool CloseOpenedParameter();
    /// ���������� ����������� �������
    void DrawUGO(Chan::E ch, int y0);
    /// ���������� ������ ������������� ������� ��� ���������
    static void SetFormFlash(Chan::E ch, const uint8 data[300]);
    /// ���������� ��������� �� ������ ������������� ������� ��� ���������
    static uint8 *GetFormFlash(Chan::E ch);
    /// �������� �������� �������
    float GetOffset();
    /// �������� ������ �������
    float GetAmplitude();

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

    static void DrawSine(Chan::E ch, int x, int y, int width, int height);

    static void DrawRampPlus(Chan::E ch, int x, int y, int width, int height);

    static void DrawRampMinus(Chan::E ch, int x, int y, int width, int height);

    static void DrawTriangle(Chan::E ch, int x, int y, int width, int height);

    static void DrawMeander(Chan::E ch, int x, int y, int width, int height);

    static void DrawImpulse(Chan::E ch, int x, int y, int width, int height);

    static void DrawPacketImpulse(Chan::E ch, int x, int y, int width, int height);

    static void DrawDDS(Chan::E ch, int x, int y, int width, int height);


};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Wave
{
public:

    Wave(Chan::E ch, Form **forms);
    /// ���������� ������������� �����
    Form *GetCurrentForm();
    /// ���������� ������ ������� ����� �������.
    void SetIndexForm(int8 num);

    int NumberOfForms() const;

    Form *GetForm(int i);

    Form *GetForm(Form::E form);

    Chan::E GetChannel() const { return channel; };
    /// ���������� true, ���� ���������� ������ ����� �������
    bool StartModeIsSingle();

private:
    /// ������ ������ ����������� ������
    Chan::E channel;
    /// ������� ����� ������� - ��������� �� ����� ������� � �������
    int indexCurrentForm;
    /// ������ ����, ������� ����� ���� ���������
    Form **forms;
    /// ���������� ��������� ����
    int numForms;

public:

    class Graphics
    {
    public:
        /// ���������� ���������� � ���������� ������� �� ������
        static void Draw(Chan::E ch);
        /// ������� x ������� ��������� �������
        static int X();
        /// ������� y ������� ��������� �������
        static int Y(Chan::E ch);
        /// ������ ������� ��������� �������
        static int Width();
        /// ������ ������� ��������� �������
        static int Height();
    private:

        static void DrawParameters(Chan::E chan, int y0);

        static void DrawParameterValue(ParameterBase *parameter, int x, int y);
    };
};
