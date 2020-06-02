#pragma once
#include "common/Common.h"
#include "Generator/MathSupport.h"
#include "Generator/Tuner.h"
#include "Generator/Viewer.h"
#include "Settings/SettingsTypes.h"


class Form;
struct Key;
class Parameter;


struct ParameterKind
{
    enum E
    {
        Double,     // ��������, ���������� �������� ���������
        Exit,       // ������� ��������� �������� (�����������)
        Choice,     // ����� �� ���������� ��������
        Composite,  // ��������� ��������, ��������� �� ���������� ������� (�����������)
        Count
    };
};


class Parameter
{
public:

    Parameter(ParameterKind::E k, const char *nRU, const char *nEN) : viewer(this), form(nullptr), parent(nullptr), kind(k)
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
    bool IsComposite() const;

    // true, ���� �������� ����� ��� Parameter::Choice
    bool IsChoice() const;

    // ���������� true, ���� �������� ������� � ������
    bool IsOpened() const;

    virtual String ToString() const = 0;

    Form *GetForm();
    
    // ���������� ������� ������ "��������"
    virtual void OnPressButtonTune() = 0;

    ParameterKind::E GetKind() { return kind; }

    Viewer viewer;

protected:
    
    Form *form;         // �����, ��� ������� ���� ���� ��������
    Parameter *parent;  // ���� �������� ���������, �� ����� ����� ��������
    ParameterKind::E kind;
    const char *name[2];
};


struct ParameterDoubleType
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
        Count
    };
};


class ParameterDouble : public Parameter
{
    friend struct LogicFloatValue;
    friend class Tuner;
    friend class TunerDisplay;

public:

    ParameterDouble(ParameterDoubleType::E t, const char *nameRU, const char *nameEN, const Value &_min, const Value &_max, const Value &_value);

    // ���������� �������� ��������� � ��������� ��� � ������
    bool SetAndLoadValue(double val);
    bool SetAndLoadValue(Value val);
    
    // ���������� true, ���� �������� ����� ����
    bool IsSigned() const { return (type == ParameterDoubleType::Offset); }

    // ���������� true, ���� �������� ����� ����������� "�����"
    bool IsVoltage() const;

    // ���������� true, ���� �������� ������ ����������� "�������"
    bool IsTime() const;

    virtual void OnPressButtonTune();

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

    ParameterDoubleType::E GetType() const { return type; }

private:
    Tuner tuner;        // ������������ ��� ��������� 
    ParameterDoubleType::E type;
    Value min;
    Value max;
    Value value;

    // ���������� true, ���� �������� ����� ��������� �������� v
    bool InRange(double v) const;
    bool InRange(Value v) const;
};


struct ParameterChoiceType
{
    enum E
    {
        Polarity,             // ���������� ���������
        ModeStart,            // ����� ������� �������� DDS � ����������
        ManipulationEnabled,  // ������� ��� �������� ����� �����������
        Count
    };
};


class ParameterChoice : public Parameter
{
public:

    ParameterChoice(ParameterChoiceType::E t, const char *nameRU, const char *nameEN, const char **_choices = nullptr) :
        Parameter(ParameterKind::Choice, nameRU, nameEN), type(t), choice(0), choices(_choices) { }

    ParameterChoiceType::E GetType() { return type; }

    int GetChoice() const            {  return choice; }

    void NextChoice();

    bool SetAndLoadChoice(int ch);

    virtual String ToString() const;

    virtual void OnPressButtonTune();

private:
	ParameterChoiceType::E type;
    int choice;                     // ������� �����
    const char **choices;           // ���� ��� - 0(���), 0(����), 1(���), 1(����)...
    
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
        Parameter(ParameterKind::Composite, nameRU, nameEN), value(Count), params(parameters), type(v) { }

    virtual void SetForm(Form *form);

    int NumParameters() const;
    Parameter **Parameters() { return params; }

    ParameterDouble *FindParameter(ParameterDoubleType::E p);
    ParameterChoice *FindParameter(ParameterChoiceType::E p);

    virtual String ToString() const;

    virtual void OnPressButtonTune();

private:
    
    Parameter **params; // ����� ��������� �������������� ��������� � ������, ���� ��� ���������
    E type;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Value ///
class ParameterVoltage : public ParameterDouble
{
public:
    ParameterVoltage(ParameterDoubleType::E type, const char *nameRU, const char *nameEN, const Value &min, const Value &max, const Value &value) :
        ParameterDouble(type, nameRU, nameEN, min, max, value) { }
};


class ParameterAmplitude : public ParameterVoltage
{
public:
    ParameterAmplitude(const Value &min = Value("0"), const Value &max = Value("10"), const Value &value = Value("10")) :
        ParameterVoltage(ParameterDoubleType::Amplitude, "������", "Amplitude", min, max, value) { }
};


class ParameterOffset : public ParameterVoltage
{
public:
    ParameterOffset(const Value &min = Value("-5"), const Value &max = Value("5"), const Value &value = Value("0")) :
        ParameterVoltage(ParameterDoubleType::Offset, "��������", "Offset", min, max, value) { }
};


class ParameterFrequency : public ParameterDouble
{
public:
    ParameterFrequency(const Value &min = Value("0.1"), const Value &max = Value("100", Order::Mega), const Value &value = Value("1", Order::Kilo)) :
        ParameterDouble(ParameterDoubleType::Frequency, "�������", "Frequency", min, max, value) { }
};


class ParameterTime : public ParameterDouble
{
public:
    ParameterTime(ParameterDoubleType::E t, const char *nameRU, const char *nameEN, const Value &min, const Value &max, const Value &value) :
        ParameterDouble(t, nameRU, nameEN, min, max, value) { }
};


class ParameterPhase : public ParameterDouble
{
public:
    ParameterPhase() : ParameterDouble(ParameterDoubleType::Phase, "����", "Phase", Value("0"), Value("360"), Value("0")) { }
};


class ParameterPacketPeriod : public ParameterTime
{
public:
    ParameterPacketPeriod(const Value &min, const Value &max, const Value &value) : ParameterTime(ParameterDoubleType::PacketPeriod, "������", "Period", min, max, value) { }
};


class ParameterPeriod : public ParameterTime
{
public:
    ParameterPeriod(const Value &min, const Value &max, const Value &value) :  ParameterTime(ParameterDoubleType::Period, "������", "Period", min, max, value) { }
};


class ParameterDuration : public ParameterTime
{
public:
    ParameterDuration(const Value &min, const Value &max, const Value &value) : ParameterTime(ParameterDoubleType::Duration, "������������", "Duration", min, max, value) { }
};


class ParameterManipulationDuration : public ParameterTime
{
public:
    ParameterManipulationDuration(const Value &min, const Value &max, const Value &value) :
        ParameterTime(ParameterDoubleType::ManipulationDuration, "������������", "Duration", min, max, value) { }
};


class ParameterManipulationPeriod : public ParameterTime
{
public:
    ParameterManipulationPeriod(const Value &min, const Value &max, const Value &value) :
        ParameterTime(ParameterDoubleType::ManipulationPeriod, "������", "Period", min, max, value) { }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Choice ///
class ParameterModeStart : public ParameterChoice
{
public:
    ParameterModeStart(const char **names) : ParameterChoice(ParameterChoiceType::ModeStart, "������", "Start", names) { }
};


class ParameterManipulationEnabled : public ParameterChoice
{
public:
    ParameterManipulationEnabled(const char **names) : 
        ParameterChoice(ParameterChoiceType::ManipulationEnabled, "�����������", "Manipulation", names) { }
};


class ParameterPolarity : public ParameterChoice
{
public:
    ParameterPolarity(const char **names) : ParameterChoice(ParameterChoiceType::Polarity, "����������", "Polarity", names) { }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Complex ///
class ParameterManipulation : public ParameterComposite
{
public:
    ParameterManipulation(Parameter **paramaters);
};

