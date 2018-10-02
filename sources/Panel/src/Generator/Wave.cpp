#include "Command.h"
#include "defines.h"
#include "Log.h"
#include "Settings/Settings.h"
#include "Display/InputWindow.h"
#include "Display/Symbols.h"
#include "Generator.h"
#include "Signals.h"
#include "Utils/Debug.h"
#include <stdio.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pString Form::Name(Language lang) const
{
    static const struct StructName
    {
        pString name;
        StructName(pString n) : name(n) { };
    }
    names[Form::Number][2] =
    {
        {"�����",    "SINE"},
        {"����+",    "RAMP+"},
        {"����-",    "RAMP-"},
        {"������",   "MEANDER"},
        {"�������",  "IMPULSE"},
        {"�����",    "PACKET"}
    };

    return names[value][lang].name;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString Register::Name() const
{
    static const struct StrName
    {
        pString name;
        StrName(pString n) : name(n) {};
    }
    names[Register::Number] =
    {
        "������������� 1",
        "������������� 2",
        "5697 �������� 1",
        "5697 �������� 2",
        "5697 ���� �������",
        "5697 ���� ����������",
        "RG0 ����������",
        "RG1 �������",
        "RG2 ����������",
        "RG3 ������� �",
        "RG4 ������� B",
        "RG5 ������ ��������� �",
        "RG6 ����. ��������� �",
        "RG7 ������ ��������� B",
        "RG8 ����. ��������� B",
        "RG9 �����. �����������",
        "RG10 ��������",
        "������������� 3",
        "���������� - �������������",
        "���������� - �����",
        "���������� - ������"
    };

    return names[value].name;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ParameterValue::IsComplexParameter() const
{
    return value == Manipulation;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterValue::Name() const
{
    static const struct StructName
    {
        pString name;
        StructName(pString n) : name(n) { };
    }
    nameParameter[ParameterValue::Number][2] =
    {
        {"�������",        "Frequency"},
        {"������",         "Period"},
        {"������",         "Amplitude"},
        {"��������",       "Offset"},
        {"������������",   "Duration"},
        {"����������",     "Duty ratio"},
        {"����",           "Phapse"},
        {"��������",       "Delay"},
        {"�� ����������",  "Build-up time"},
        {"�� �����",       "Release time"},
        {"�� ����",        "Peak time"},
        {"����� ������",   "Duty factor"},
        {"�����������",    "Manipulation"},
        {"������������",   "Duration"},
        {"������",         "Period"},
        {"������ ������",  "Packet period"},
        {"���-�� ���",     "Num of puls"},
        {"     ����� ( ESC )", "     Exit ( ESC )"}
    };

    return nameParameter[value][LANG].name;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Form *Wave::GetCurrentForm()
{
    return &forms[currentForm];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Wave::SetNextForm()
{
    currentForm++;
    if(currentForm >= NumberOfForms())
    {
        currentForm = 0;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Wave::NumberOfForms() const
{
    return numForms;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Wave::Wave(Chan ch, Form *f, int num) : channel(ch), forms(f), numForms(num)
{
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Form::Form(E v, ParameterBase *parameters[], int num, Wave *w) : value(v), wave(w), params(parameters), numParams(num), currentParam(0)
{
    for(int i = 0; i < numParams; i++)
    {
        params[i]->form = this;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
ParameterBase *Form::CurrentParameter()
{
    return params[currentParam];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Form::NumParameters() const 
{
    return numParams;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
ParameterBase *Form::GetParameter(int i)
{
    if(i < numParams)
    {
        return params[i];
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Form *Wave::GetForm(int i)
{
    return &forms[i];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Form::SetNextParameter()
{
    currentParam++;
    if(currentParam >= NumParameters())
    {
        currentParam = 0;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Form::TuneGenerator(Chan ch)
{
    Generator::SetFormWave(GetWave());

    if(value == Form::Sine)
    {
        if(set.sineManipulation[ch])
        {
            int current = currentParam;
            ParameterBase **param = params;
            int numPar = numParams;

            currentParam = oldCurrentParams;
            params = oldParams;
            numParams = oldNumParams;

            if(PARAM_CURRENT_IS_MANIPULATION)
            {
                SendParameterToGenerator(ParameterValue::Frequency);
                SendParameterToGenerator(ParameterValue::Amplitude);
                SendParameterToGenerator(ParameterValue::Offset);
                SendParameterToGenerator(ParameterValue::Manipulation);
            }

            currentParam = current;
            params = param;
            numParams = numPar;

            SendParameterToGenerator(ParameterValue::ManipulationDuration);
            SendParameterToGenerator(ParameterValue::ManipulationPeriod);
        }
        else
        {
            SendParameterToGenerator(ParameterValue::Manipulation);
            SendParameterToGenerator(ParameterValue::Frequency);
            SendParameterToGenerator(ParameterValue::Amplitude);
            SendParameterToGenerator(ParameterValue::Offset);
        }
        if(!ch.IsA())
        {
            SendParameterToGenerator(ParameterValue::Phase);
        }
    }
    else
    {
        SendParameterToGenerator(ParameterValue::Frequency);
        SendParameterToGenerator(ParameterValue::Amplitude);
        SendParameterToGenerator(ParameterValue::Offset);
        SendParameterToGenerator(ParameterValue::Period);
        SendParameterToGenerator(ParameterValue::Duration);
        SendParameterToGenerator(ParameterValue::PacketNumber);
        SendParameterToGenerator(ParameterValue::PacketPeriod);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
ParameterValue *Form::FindParameter(ParameterValue::E p)
{
    for(int i = 0; i < numParams; i++)
    {
        ParameterValue *param = (ParameterValue *)params[i];

        if(param->value == p)
        {
            return param;
        }
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Form::SendParameterToGenerator(ParameterValue::E p)
{
    ParameterValue *param = FindParameter(p);
    if (param)
    {
        Generator::SetParameter(param);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Form::OpenCurrentParameter()
{
    if(!PARAM_CURRENT_IS_COMPLEX)
    {
        return;
    }

    if(PARAM_CURRENT_IS_MANIPULATION)
    {
        /// ���� � ����� ��������� ���� ��������, ������, ���� �������� ��������� ����������/����������� �����������
        if(PARAM_CURRENT_PARENT)
        {
            set.sineManipulation[CURRENT_CHANNEL] = !set.sineManipulation[CURRENT_CHANNEL];
            Generator::TuneChannel(GetWave()->GetChannel());
        }
        else
       {
            oldParams = params;
            oldNumParams = numParams;
            oldCurrentParams = currentParam;

            ParameterValue *parent = PARAM_VALUE(CurrentParameter());

            numParams = parent->numParams;
            params = parent->params;
            currentParam = 0;

            for (int i = 0; i < numParams; i++)
            {
                params[i]->form = this;
                params[i]->parent = parent;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Form::CloseOpenedParameter()
{
    if (ParameterIsOpened())
    {
        params = oldParams;
        numParams = oldNumParams;
        currentParam = oldCurrentParams;
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Form::ParameterIsOpened() const
{
    return params[0]->parent != 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float ParameterValue::GetValue() const
{
    if(Is(Manipulation))
    {
        ParameterValue *pointer = (ParameterValue *)this;
        return set.sineManipulation[pointer->GetForm()->GetWave()->GetChannel()] ? 1.0f : 0.0f;
    }
    StructValue input((ParameterValue *)this);
    return input.Value();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterValue::GetStringValue() const
{
    if(Is(Manipulation))
    {
        static const char *values[2][2] =
        {
            {" ����", " ���"},
            {" Off",  " On"}
        };

        ParameterValue *pointer = (ParameterValue *)this;
        return values[LANG][set.sineManipulation[pointer->GetForm()->GetWave()->GetChannel()] ? 1 : 0];
    }
    StructValue input((ParameterValue *)this);
    return input.StringValue();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString ParameterValue::NameUnit(char buf[10])
{
    static const struct StructName
    {
        pString name;
        StructName(pString n) : name(n) {};
    }
    names[ParameterValue::Number][2] =
    {
        {"��",  "Hz"},
        {"�",   "s"},
        {"�",   "V"},
        {"�",   "V"},
        {"�",   "s"},
        {"",    ""},
        {"\x7b","\x7b"},
        {"�",   "s"},
        {"",    ""},
        {"",    ""},
        {"",    ""},
        {"",    ""},
        {"",    ""},
        {"c",   "s"},
        {"c",   "s"},
        {"c",   "s"},
        {"",    ""},
        {"",    ""}
    };

    sprintf(buf, "%s%s", order.Name(), names[value][LANG].name);
    return buf;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ParameterValue::IsOpened()
{
    return IsComplexParameter() && GetForm()->ParameterIsOpened();
}
