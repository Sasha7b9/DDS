#pragma once
#include "common/Common.h"
#include "Settings/SettingsTypes.h"


class Form;


class Parameter
{
public:
    virtual pString Name() const { return ""; }

    virtual void SetForm(Form *form);

    void SetParent(Parameter *p) { parent = p; }
    /// ���������� ����� ������������� ���������
    Parameter *GetParent() { return parent; }

    bool IsValue();

    bool IsComplex();

    bool IsChoice();
    /// ���������� true, ���� �������� ������� � ������
    bool IsOpened() const { return parent != 0; }

    virtual pString GetStringDigits() const;

    Form *GetForm() { return form; }

    pString NameUnit(char buffer[10]);

protected:
    /// �����, ��� ������� ���� ���� ��������
    Form *form;
    /// ���� �������� ���������, �� ����� ����� ��������
    Parameter *parent;
};


class ParameterValue : public Parameter
{
public:

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
    };

    ParameterValue(const FloatValue &min, const FloatValue &max, const FloatValue &value);

    virtual pString Name() const
    {
        return "";
    }

    E Type() const { return type; }

    FloatValue GetValue() const { return value; };

    pString GetStringValue(Language::E lang) const;

    bool SetAndLoadValue(float val);

private:
    E type;

    FloatValue value;

    pString MainUnits(Language::E lang) const;
    /// ���������� true, ���� �������� ����� ��������� �������� v
    bool InRange(float v) const;
};


class ParameterVoltage : public ParameterValue
{
public:
    ParameterVoltage(const FloatValue &min, const FloatValue &max, const FloatValue &value);
};


class ParameterAmplitude : public ParameterVoltage
{
public:
    ParameterAmplitude(const FloatValue &min = FloatValue(0, 0), const FloatValue &max = FloatValue(10, 0), const FloatValue &value = FloatValue(10, 0));
};


class ParameterOffset : public ParameterVoltage
{
public:
    ParameterOffset(const FloatValue &min = FloatValue(-5, 0), const FloatValue &max = FloatValue(5, 0), const FloatValue &value = FloatValue(0, 0));
};


class ParameterFrequency : public ParameterValue
{
public:
    ParameterFrequency(const FloatValue &min = FloatValue(0, 100), const FloatValue &max = FloatValue(100 * 1000 * 1000, 0), const FloatValue &value = FloatValue(1000, 0));
};


class ParameterTime : public ParameterValue
{
public:
    ParameterTime(const FloatValue &min, const FloatValue &max, const FloatValue &value);
};


class ParameterPhase : public ParameterValue
{
public:
    ParameterPhase();
};


class ParameterPacketPeriod : public ParameterTime
{
public:
    ParameterPacketPeriod(const FloatValue &min, const FloatValue &max, const FloatValue &value);
};


class ParameterPeriod : public ParameterTime
{
public:
    ParameterPeriod(const FloatValue &min, const FloatValue &max, const FloatValue &value);
};


class ParameterDuration : public ParameterTime
{
public:
    ParameterDuration(const FloatValue &min, const FloatValue &max, const FloatValue &value);
};


class ParameterManipulationDuration : public ParameterTime
{
public:
    ParameterManipulationDuration(const FloatValue &min, const FloatValue &max, const FloatValue &value);
};


class ParameterManipulationPeriod : public ParameterTime
{
public:
    ParameterManipulationPeriod(const FloatValue &min, const FloatValue &max, const FloatValue &value);
};


class ParameterChoice : public Parameter
{
public:
	enum E
	{
        Polarity,                   ///< ���������� ���������
        ModeStart,                  ///< ����� ������� �������� DDS � ����������
        deleted_ManipulationMode,   ///< ����� ����������� ����������� - �� ������������ ������ ��� ���
        ManipulationEnabled,        ///< ������� ��� �������� ����� �����������
        Count
	};

	E Type() { return type; }

    int GetChoice() const;

    virtual pString Name() const;

    virtual pString GetStringDigits() const;

    void NextChoice();

    bool SetAndLoadChoice(int ch);

    bool DrawChoice(int x, int y) const;

private:
	E type;
    /// ������� �����
    int choice;

    const char **names;
    /// ���������� ��������� ������
    int NumChoices() const;
};


class ParameterModeStart : public ParameterChoice
{
public:
    ParameterModeStart(pString choice0 = " ����", pString choice1 = " ������", pString choice2 = " ���� �", pString choice3 = " ���� B");
};


class ParameterManipulationEnabled : public ParameterChoice
{
public:
    ParameterManipulationEnabled(pString choice0, pString choice1);
    virtual pString Name() const { return "�����������"; }
};


class ParameterPolarity : public ParameterChoice
{
public:
    ParameterPolarity();
};


class ParameterComplex : public Parameter
{
public:
    enum E
    {
        Manipulation,       ///< ��������� �������� / �������� / ����������� �� ����� �����
        Count
    } value;

    virtual void SetForm(Form *form);

    virtual pString Name() const;

    int NumParams() const { return numParams; }
    Parameter **Params() { return params; }

    virtual pString GetStringDigits() const;

    ParameterValue *FindParameter(ParameterValue::E p);
    ParameterChoice *FindParameter(ParameterChoice::E p);
private:
    /// ����� ��������� �������������� ��������� � ������, ���� ��� ���������
    Parameter **params;
    /// ����� �������������� ���������� ��� 0, ���� ������� �� �������
    int numParams;

    E type;
};


class ParameterManipulation : public ParameterComplex
{
public:
    ParameterManipulation(Parameter **paramaters);
};
