#pragma once
#include "common/Common.h"
#include "Generator/MathSupport.h"
#include "Generator/Tuner.h"
#include "Generator/Viewer.h"
#include "Settings/SettingsTypes.h"


class Form;
struct Key;
class Parameter;


class Parameter
{
public:

    enum E
    {
        Double,     // ��������, ���������� �������� ���������
        Exit,       // ������� ��������� �������� (�����������)
        Choice,     // ����� �� ���������� ��������
        Composite   // ��������� ��������, ��������� �� ���������� ������� (�����������)
    };

    Parameter(E k, const char *nRU, const char *nEN) : viewer(this), form(nullptr), parent(nullptr), kind(k)
    {
        name[0] = nRU;
        name[1] = nEN;
    }

    virtual ~Parameter() { }

    pString Name() const;

    virtual void SetForm(Form *form);

    void SetParent(Parameter *p);
    
    // ���������� ����� ������������� ���������
    Parameter *GetParent();

    // true, ���� �������� ����� ��� Parameter::Value
    bool IsDouble() const;

    // true, ���� �������� ����� ��� Parameter::Complex
    bool IsComplex() const;

    // true, ���� �������� ����� ��� Parameter::Choice
    bool IsChoice() const;

    // ���������� true, ���� �������� ������� � ������
    bool IsOpened() const;

    virtual String ToString() const = 0;

    Form *GetForm();
    
    // ���������� ������� ������ "��������"
    void OnPressButtonTune();

    Viewer viewer;

protected:
    
    Form *form;         // �����, ��� ������� ���� ���� ��������
    Parameter *parent;  // ���� �������� ���������, �� ����� ����� ��������
    E kind;
    const char *name[2];
};


struct ParameterValueType
{
    enum E
    {
        Frequency,              // �������
        Period,                 // ������
        Amplitude,              // ���������
        Offset,                 // ��������
        Duration,               // ������������
        DutyRatio,              // ����������
        Phase,                  // ����� ����
        Delay,                  // ��������
        DurationRise,           // ������������ ����������
        DurationFall,           // ������������ �����
        DurationStady,          // ������������ ������������� ��������
        DutyFactor,             // ����������� ����������
        ManipulationDuration,   // ������������ ��������� � ������ �����������
        ManipulationPeriod,     // ������ ���������� ��������� � ������ �����������
        PacketPeriod,           // ������ ���������� ����� ��������� � �������� ������
        PacketNumber,           // ����� ��������� � ����� ��������� ������
        Exit,                   // ���� �������� ��������� �������� ��������
        Count
    };
};


class ParameterDouble : public Parameter
{
    friend struct LogicFloatValue;
    friend class Tuner;
    friend class TunerDisplay;

public:

    ParameterDouble(ParameterValueType::E t, const char *nameRU, const char *nameEN, const Value &_min, const Value &_max, const Value &_value);

    // ���������� �������� ��������� � ��������� ��� � ������
    bool SetAndLoadValue(double val);
    bool SetAndLoadValue(Value val);
    
    // ���������� true, ���� �������� ����� ����
    bool IsSigned() const { return (type == ParameterValueType::Offset); }

    // ���������� true, ���� �������� ���������� ����������
    bool IsVoltage() const
    {
        return (type == ParameterValueType::Amplitude) || (type == ParameterValueType::Offset);
    }

    void OnPressButtonTune();

    // ���������� ��������� ������������� �������� ���������
    virtual String ToString() const;
    String ToString(Value value) const;

    // ���������� �������� ������� ��������� (��� ����� �������)
    pString GetMainUnits() const;

    // ���������� ������� ���������, ���������� � ������� order. ���� order == Order::Count, ������� ����� �������������� ������ �� �������� �������� value
    pString GetUnits(Order::E order = Order::Count) const;

    // ���������� ������������ ��������, ������� ����� ����� ��������
    Value GetMax() { return max; }
    
    // ���������� ����������� ��������, ������� ����� ����� ��������
    Value GetMin() { return min; }

    Tuner *GetTuner()   { return &tuner; };

    // ���������� ������� �������� ���������
    Value GetValue() const { return value; };

    ParameterValueType::E GetType() const { return type; }

private:
    Tuner tuner;        // ������������ ��� ��������� 
    ParameterValueType::E type;
    Value min;
    Value max;
    Value value;

    // ���������� true, ���� �������� ����� ��������� �������� v
    bool InRange(double v) const;
    bool InRange(Value v) const;
};


class ParameterChoice : public Parameter
{
public:
	enum E
	{
        Polarity,             // ���������� ���������
        ModeStart,            // ����� ������� �������� DDS � ����������
        ManipulationEnabled,  // ������� ��� �������� ����� �����������
        Count
	};

    ParameterChoice(E t, const char *nameRU, const char *nameEN) : Parameter(Parameter::Choice, nameRU, nameEN), type(t), choice(0), names(nullptr) { }

	E Type() { return type; }

    int GetChoice() const;

    void NextChoice();

    bool SetAndLoadChoice(int ch);

    bool DrawChoice(int x, int y) const;

    virtual String ToString() const;

    void OnPressButtonTune();

private:
	E type;
    int choice;             // ������� �����
    const char **names;
    
    // ���������� ��������� ������
    int NumChoices() const;
};


class ParameterComposite : public Parameter
{
public:
    enum E
    {
        Manipulation,   // ��������� �������� / �������� / ����������� �� ����� �����
        Count
    } value;

    ParameterComposite(E v, const char *nameRU, const char *nameEN, Parameter **parameters) :
        Parameter(Parameter::Composite, nameRU, nameEN), value(Count), params(parameters), numParams(0), type(v) { }

    virtual void SetForm(Form *form);

    int NumParams() const { return numParams; }
    Parameter **Params() { return params; }

    ParameterDouble *FindParameter(ParameterValueType::E p);
    ParameterChoice *FindParameter(ParameterChoice::E p);

    virtual String ToString() const;

    void OnPressButtonTune();

private:
    
    Parameter **params; // ����� ��������� �������������� ��������� � ������, ���� ��� ���������
    int numParams;      // ����� �������������� ���������� ��� 0, ���� ������� �� �������
    E type;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Value ///
class ParameterVoltage : public ParameterDouble
{
public:
    ParameterVoltage(ParameterValueType::E type, const char *nameRU, const char *nameEN, const Value &min, const Value &max, const Value &value) :
        ParameterDouble(type, nameRU, nameEN, min, max, value) { }
};


class ParameterAmplitude : public ParameterVoltage
{
public:
    ParameterAmplitude(const Value &min = Value("0"), const Value &max = Value("10"), const Value &value = Value("0.123")) :
        ParameterVoltage(ParameterValueType::Amplitude, "������", "Amplitude", min, max, value) { }
};


class ParameterOffset : public ParameterVoltage
{
public:
    ParameterOffset(const Value &min = Value("-5"), const Value &max = Value("5"), const Value &value = Value("0")) :
        ParameterVoltage(ParameterValueType::Offset, "��������", "Offset", min, max, value) { }
};


class ParameterFrequency : public ParameterDouble
{
public:
    ParameterFrequency(const Value &min = Value("0.1"), const Value &max = Value("100", Order::Mega), const Value &value = Value("1", Order::Kilo)) :
        ParameterDouble(ParameterValueType::Frequency, "�������", "Frequency", min, max, value) { }
};


class ParameterTime : public ParameterDouble
{
public:
    ParameterTime(ParameterValueType::E t, const char *nameRU, const char *nameEN, const Value &min, const Value &max, const Value &value) :
        ParameterDouble(t, nameRU, nameEN, min, max, value) { }
};


class ParameterPhase : public ParameterDouble
{
public:
    ParameterPhase() : ParameterDouble(ParameterValueType::Phase, "����", "Phase", Value("0"), Value("360"), Value("0")) { }
};


class ParameterPacketPeriod : public ParameterTime
{
public:
    ParameterPacketPeriod(const Value &min, const Value &max, const Value &value) : ParameterTime(ParameterValueType::PacketPeriod, "������", "Period", min, max, value) { }
};


class ParameterPeriod : public ParameterTime
{
public:
    ParameterPeriod(const Value &min, const Value &max, const Value &value) :  ParameterTime(ParameterValueType::Period, "������", "Period", min, max, value) { }
};


class ParameterDuration : public ParameterTime
{
public:
    ParameterDuration(const Value &min, const Value &max, const Value &value) : ParameterTime(ParameterValueType::Duration, "������������", "Duration", min, max, value) { }
};


class ParameterManipulationDuration : public ParameterTime
{
public:
    ParameterManipulationDuration(const Value &min, const Value &max, const Value &value) :
        ParameterTime(ParameterValueType::ManipulationDuration, "������������", "Duration", min, max, value) { }
};


class ParameterManipulationPeriod : public ParameterTime
{
public:
    ParameterManipulationPeriod(const Value &min, const Value &max, const Value &value) :
        ParameterTime(ParameterValueType::ManipulationPeriod, "������", "Period", min, max, value) { }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Choice ///
class ParameterModeStart : public ParameterChoice
{
public:
    //ParameterModeStart(pString choice0 = " ����", pString choice1 = " ������", pString choice2 = " ���� �", pString choice3 = " ���� B");

    ParameterModeStart() : ParameterChoice(ParameterChoice::ModeStart, "������", "Start") { }
};


class ParameterManipulationEnabled : public ParameterChoice
{
public:
    ParameterManipulationEnabled(pString, pString) : ParameterChoice(ParameterChoice::ManipulationEnabled, "�����������", "Manipulation") { }
};


class ParameterPolarity : public ParameterChoice
{
public:
    ParameterPolarity() : ParameterChoice(ParameterChoice::Polarity, "����������", "Polarity") { }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Complex ///
class ParameterManipulation : public ParameterComposite
{
public:
    ParameterManipulation(Parameter **paramaters);
};

