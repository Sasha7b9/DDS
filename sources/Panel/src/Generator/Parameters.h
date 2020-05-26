#pragma once
#include "common/Common.h"
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
        Value,
        Exit,
        Choice,
        Complex,
        Page
    };

    Parameter(E k, const char *nRU, const char *nEN) : viewer(this), form(nullptr), parent(nullptr), kind(k)
    {
        name[0] = nRU;
        name[1] = nEN;
    }

    virtual ~Parameter() { }

    pString Name(uint lang) const;

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

    virtual pString GetStringValue() const = 0;

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

    ParameterValue(ParameterValueType::E t, const char *nameRU, const char *nameEN, const FloatValue &_min, const FloatValue &_max, const FloatValue &_value);

    virtual pString GetStringValue() const;

    ParameterValueType::E Type() const { return type; }

    FloatValue GetValue() const { return value; };

    bool SetAndLoadValue(float val);
    
    // ���������� true, ���� �������� ����� ����
    bool IsSigned() const { return (type == ParameterValueType::Offset); }

    void OnPressButtonTune();

    Tuner tuner;        // ������������ ��� ��������� 

private:
    ParameterValueType::E type;
    FloatValue min;
    FloatValue max;
    FloatValue value;

    pString MainUnits(uint lang) const;

    // ���������� true, ���� �������� ����� ��������� �������� v
    bool InRange(float v) const;
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

    virtual pString GetStringValue() const;

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

    virtual pString GetStringValue() const;

    void OnPressButtonTune();

private:
    
    Parameter **params; // ����� ��������� �������������� ��������� � ������, ���� ��� ���������
    int numParams;      // ����� �������������� ���������� ��� 0, ���� ������� �� �������
    E type;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Value ///
class ParameterVoltage : public ParameterValue
{
public:
    ParameterVoltage(ParameterValueType::E type, const char *nameRU, const char *nameEN, const FloatValue &min, const FloatValue &max, const FloatValue &value) :
        ParameterValue(type, nameRU, nameEN, min, max, value) { }
};


class ParameterAmplitude : public ParameterVoltage
{
public:
    ParameterAmplitude(const FloatValue &min = FloatValue("0"), const FloatValue &max = FloatValue("10"), const FloatValue &value = FloatValue("10")) :
        ParameterVoltage(ParameterValueType::Amplitude, "������", "Amplitude", min, max, value) { }
};


class ParameterOffset : public ParameterVoltage
{
public:
    ParameterOffset(const FloatValue &min = FloatValue("-5"), const FloatValue &max = FloatValue("5"), const FloatValue &value = FloatValue("0")) :
        ParameterVoltage(ParameterValueType::Offset, "��������", "Offset", min, max, value) { }
};


class ParameterFrequency : public ParameterValue
{
public:
    ParameterFrequency(const FloatValue &min = FloatValue("0.1"), const FloatValue &max = FloatValue("100", 6), const FloatValue &value = FloatValue("1000")) :
        ParameterValue(ParameterValueType::Frequency, "�������", "Frequency", min, max, value) { }
};


class ParameterTime : public ParameterValue
{
public:
    ParameterTime(ParameterValueType::E t, const char *nameRU, const char *nameEN, const FloatValue &min, const FloatValue &max, const FloatValue &value) :
        ParameterValue(t, nameRU, nameEN, min, max, value) { }
};


class ParameterPhase : public ParameterValue
{
public:
    ParameterPhase() : ParameterValue(ParameterValueType::Phase, "����", "Phase", FloatValue("0"), FloatValue("360"), FloatValue("0")) { }
};


class ParameterPacketPeriod : public ParameterTime
{
public:
    ParameterPacketPeriod(const FloatValue &min, const FloatValue &max, const FloatValue &value) : ParameterTime(ParameterValueType::PacketPeriod, "������", "Period", min, max, value) { }
};


class ParameterPeriod : public ParameterTime
{
public:
    ParameterPeriod(const FloatValue &min, const FloatValue &max, const FloatValue &value) :  ParameterTime(ParameterValueType::Period, "������", "Period", min, max, value) { }
};


class ParameterDuration : public ParameterTime
{
public:
    ParameterDuration(const FloatValue &min, const FloatValue &max, const FloatValue &value) : ParameterTime(ParameterValueType::Duration, "������������", "Duration", min, max, value) { }
};


class ParameterManipulationDuration : public ParameterTime
{
public:
    ParameterManipulationDuration(const FloatValue &min, const FloatValue &max, const FloatValue &value) :
        ParameterTime(ParameterValueType::ManipulationDuration, "������������", "Duration", min, max, value) { }
};


class ParameterManipulationPeriod : public ParameterTime
{
public:
    ParameterManipulationPeriod(const FloatValue &min, const FloatValue &max, const FloatValue &value) :
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

