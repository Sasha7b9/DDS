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
        Value,      // ��������, ���������� �������� ���������
        Exit,       // ������� ��������� �������� (�����������)
        Choice,     // ����� �� ���������� ��������
        Complex     // ��������� ��������, ��������� �� ���������� ������� (�����������)
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
    bool IsValue() const;

    // true, ���� �������� ����� ��� Parameter::Complex
    bool IsComplex() const;

    // true, ���� �������� ����� ��� Parameter::Choice
    bool IsChoice() const;

    // ���������� true, ���� �������� ������� � ������
    bool IsOpened() const;

    virtual pString ToString() const = 0;

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


class ParameterValue : public Parameter
{
    friend struct LogicFloatValue;
    friend class Tuner;
    friend class TunerDisplay;

public:

    ParameterValue(ParameterValueType::E t, const char *nameRU, const char *nameEN, const DoubleValue &_min, const DoubleValue &_max, const DoubleValue &_value);

    // ���������� �������� ��������� � ��������� ��� � ������
    bool SetAndLoadValue(double val);
    bool SetAndLoadValue(DoubleValue val);
    
    // ���������� true, ���� �������� ����� ����
    bool IsSigned() const { return (type == ParameterValueType::Offset); }

    // ���������� true, ���� �������� ���������� ����������
    bool IsVoltage() const
    {
        return (type == ParameterValueType::Amplitude) || (type == ParameterValueType::Offset);
    }

    void OnPressButtonTune();

    // ���������� ��������� ������������� �������� ���������
    virtual pString ToString() const;
    virtual pString ToString(DoubleValue value) const;

    // ���������� �������� ������� ��������� (��� ����� �������)
    pString GetMainUnits() const;

    // ���������� ������� ���������, ���������� � ������� order. ���� order == Order::Count, ������� ����� �������������� ������ �� �������� �������� value
    pString GetUnits(Order::E order = Order::Count) const;

    // ���������� ������������ ��������, ������� ����� ����� ��������
    DoubleValue GetMax() { return max; }
    
    // ���������� ����������� ��������, ������� ����� ����� ��������
    DoubleValue GetMin() { return min; }

    Tuner *GetTuner()   { return &tuner; };

    // ���������� ������� �������� ���������
    DoubleValue GetValue() const { return value; };

    ParameterValueType::E GetType() const { return type; }

private:
    Tuner tuner;        // ������������ ��� ��������� 
    ParameterValueType::E type;
    DoubleValue min;
    DoubleValue max;
    DoubleValue value;

    // ���������� true, ���� �������� ����� ��������� �������� v
    bool InRange(double v) const;
    bool InRange(DoubleValue v) const;
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

    virtual pString ToString() const;
    virtual pString ToString(DoubleValue) const { return ""; }

    void OnPressButtonTune();

private:
	E type;
    int choice;             // ������� �����
    const char **names;
    
    // ���������� ��������� ������
    int NumChoices() const;
};


class ParameterComplex : public Parameter
{
public:
    enum E
    {
        Manipulation,   // ��������� �������� / �������� / ����������� �� ����� �����
        Count
    } value;

    ParameterComplex(E v, const char *nameRU, const char *nameEN, Parameter **parameters) :
        Parameter(Parameter::Complex, nameRU, nameEN), value(Count), params(parameters), numParams(0), type(v) { }

    virtual void SetForm(Form *form);

    int NumParams() const { return numParams; }
    Parameter **Params() { return params; }

    ParameterValue *FindParameter(ParameterValueType::E p);
    ParameterChoice *FindParameter(ParameterChoice::E p);

    virtual pString ToString() const;

    void OnPressButtonTune();

private:
    
    Parameter **params; // ����� ��������� �������������� ��������� � ������, ���� ��� ���������
    int numParams;      // ����� �������������� ���������� ��� 0, ���� ������� �� �������
    E type;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Value ///
class ParameterVoltage : public ParameterValue
{
public:
    ParameterVoltage(ParameterValueType::E type, const char *nameRU, const char *nameEN, const DoubleValue &min, const DoubleValue &max, const DoubleValue &value) :
        ParameterValue(type, nameRU, nameEN, min, max, value) { }
};


class ParameterAmplitude : public ParameterVoltage
{
public:
    ParameterAmplitude(const DoubleValue &min = DoubleValue("0"), const DoubleValue &max = DoubleValue("10"), const DoubleValue &value = DoubleValue("10")) :
        ParameterVoltage(ParameterValueType::Amplitude, "������", "Amplitude", min, max, value) { }
};


class ParameterOffset : public ParameterVoltage
{
public:
    ParameterOffset(const DoubleValue &min = DoubleValue("-5"), const DoubleValue &max = DoubleValue("5"), const DoubleValue &value = DoubleValue("0")) :
        ParameterVoltage(ParameterValueType::Offset, "��������", "Offset", min, max, value) { }
};


class ParameterFrequency : public ParameterValue
{
public:
    ParameterFrequency(const DoubleValue &min = DoubleValue("0.1"), const DoubleValue &max = DoubleValue("100", 6), const DoubleValue &value = DoubleValue("1000")) :
        ParameterValue(ParameterValueType::Frequency, "�������", "Frequency", min, max, value) { }
};


class ParameterTime : public ParameterValue
{
public:
    ParameterTime(ParameterValueType::E t, const char *nameRU, const char *nameEN, const DoubleValue &min, const DoubleValue &max, const DoubleValue &value) :
        ParameterValue(t, nameRU, nameEN, min, max, value) { }
};


class ParameterPhase : public ParameterValue
{
public:
    ParameterPhase() : ParameterValue(ParameterValueType::Phase, "����", "Phase", DoubleValue("0"), DoubleValue("360"), DoubleValue("0")) { }
};


class ParameterPacketPeriod : public ParameterTime
{
public:
    ParameterPacketPeriod(const DoubleValue &min, const DoubleValue &max, const DoubleValue &value) : ParameterTime(ParameterValueType::PacketPeriod, "������", "Period", min, max, value) { }
};


class ParameterPeriod : public ParameterTime
{
public:
    ParameterPeriod(const DoubleValue &min, const DoubleValue &max, const DoubleValue &value) :  ParameterTime(ParameterValueType::Period, "������", "Period", min, max, value) { }
};


class ParameterDuration : public ParameterTime
{
public:
    ParameterDuration(const DoubleValue &min, const DoubleValue &max, const DoubleValue &value) : ParameterTime(ParameterValueType::Duration, "������������", "Duration", min, max, value) { }
};


class ParameterManipulationDuration : public ParameterTime
{
public:
    ParameterManipulationDuration(const DoubleValue &min, const DoubleValue &max, const DoubleValue &value) :
        ParameterTime(ParameterValueType::ManipulationDuration, "������������", "Duration", min, max, value) { }
};


class ParameterManipulationPeriod : public ParameterTime
{
public:
    ParameterManipulationPeriod(const DoubleValue &min, const DoubleValue &max, const DoubleValue &value) :
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
class ParameterManipulation : public ParameterComplex
{
public:
    ParameterManipulation(Parameter **paramaters);
};

