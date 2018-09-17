#include "Command.h"
#include "defines.h"
#include "Log.h"
#include "Settings/Settings.h"
#include "Display/InputWindow.h"
#include "Generator.h"
#include "Signals.h"
#include "Utils/Debug.h"
#include <stdio.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pString Form::Name(Language lang) const
{
    struct StructName
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
    struct StrName
    {
        pString name;
        StrName(pString n) : name(n) {};
    };

    static const StrName names[Register::Number] =
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
bool Parameter::IsComplexParameter() const
{
    return numParams != 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString Parameter::Name() const
{
    static const struct StructName
    {
        pString name;
        StructName(pString n) : name(n) { };
    }
    nameParameter[Parameter::Number][2] =
    {
        {"�������",        "FREQUENCY"},
        {"������",         "PERIOD"},
        {"������",         "AMPLITUDE"},
        {"��������",       "OFFSET"},
        {"����.",          "DURATION"},
        {"����������",     "DUTY RATIO"},
        {"����",           "PHASE"},
        {"��������",       "DELAY"},
        {"�����. ���.",    "MOD. INDEX"},
        {"����������",     "POLARITY"},
        {"��. ����������", "BUILD-UP TIME"},
        {"��. �����",      "RELEASING TIME"},
        {"��. ����",       "PEAK TIME"},
        {"�����. ������.", "DUTY FACTOR"},
        {"�����������",    "Manipulation"},
        {"������",         "Period"},
        {"������������",   "Duration"},
        {"������ ������",  "Packet period"},
        {"N",              "N"}
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
Form::Form(E v, Parameter *parameters, int num, Wave *w) : value(v), wave(w), params(parameters), numParams(num), currentParam(0)
{
    for(int i = 0; i < numParams; i++)
    {
        params[i].form = this;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Parameter *Form::CurrentParameter()
{
    return &params[currentParam];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Form::NumParameters() const 
{
    if(PARAM_CURRENT->GetParent())
    {
        return numParams + 2;
    }
    return numParams;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Parameter *Form::GetParameter(int i)
{
    if(i < numParams)
    {
        return &params[i];
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
    Generator::SetFormWave(ch, *this);

    if(value == Form::Sine)
    {
        if(ParameterIsOpened())
        {
            int current = currentParam;
            Parameter *param = params;
            int numPar = numParams;

            currentParam = oldCurrentParams;
            params = oldParams;
            numParams = oldNumParams;

            if(CurrentParameter()->value == Parameter::Manipulation)
            {
                SendParameterToGenerator(ch, Parameter::Frequency);
                SendParameterToGenerator(ch, Parameter::Amplitude);
                SendParameterToGenerator(ch, Parameter::Offset);
                SendParameterToGenerator(ch, Parameter::Manipulation);
            }

            currentParam = current;
            params = param;
            numParams = numPar;

            SendParameterToGenerator(ch, Parameter::ManipulationDuration);
            SendParameterToGenerator(ch, Parameter::ManipulationPeriod);
        }
        else
        {
            SendParameterToGenerator(ch, Parameter::Manipulation);
            SendParameterToGenerator(ch, Parameter::Frequency);
            SendParameterToGenerator(ch, Parameter::Amplitude);
            SendParameterToGenerator(ch, Parameter::Offset);
        }
    }
    else
    {
        SendParameterToGenerator(ch, Parameter::Frequency);
        SendParameterToGenerator(ch, Parameter::Amplitude);
        SendParameterToGenerator(ch, Parameter::Offset);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Parameter *Form::FindParameter(Parameter::E p)
{
    for(int i = 0; i < numParams; i++)
    {
        if(params[i].value == p)
        {
            return &params[i];
        }
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Form::SendParameterToGenerator(Chan ch, Parameter::E p)
{
    Parameter *param = FindParameter(p);
    if (param)
    {
        Generator::SetParameter(ch, p, param->GetValue());
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Form::OpenCurrentParameter()
{
    if(!CurrentParameter()->IsComplexParameter())
    {
        return;
    }

    if(CurrentParameter()->Is(Parameter::Manipulation))
    {
        set.sineManipulation = true;
    }

    oldParams = params;
    oldNumParams = numParams;
    oldCurrentParams = currentParam;

    Parameter *parent = CurrentParameter();

    numParams = CurrentParameter()->numParams;
    params = CurrentParameter()->params;
    currentParam = 0;

    for(int i = 0; i < numParams; i++)
    {
        params[i].form = this;
        params[i].parent = parent;
    }

    if(parent->Is(Parameter::Manipulation))
    {
        Generator::TuneChannel(wave->GetChannel());
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
        if(CurrentParameter()->Is(Parameter::Manipulation))
        {
            set.sineManipulation = false;
        }
        Generator::TuneChannel(wave->GetChannel());
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Form::ParameterIsOpened() const
{
    return params[0].parent != 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float Parameter::GetValue() const
{
    if(Is(Manipulation))
    {
        return set.sineManipulation ? 1.0f : 0.0f;
    }
    StructValue input((Parameter *)this);
    return input.Value();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString Parameter::GetStringValue() const
{
    if(Is(Manipulation))
    {
        static const char *values[2][2] =
        {
            {" ����", " ���"},
            {" Off",  " On"}
        };

        return values[LANG][set.sineManipulation ? 1 : 0];
    }
    StructValue input((Parameter *)this);
    return input.StringValue();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString Parameter::NameUnit(char buf[10])
{
    struct StructName
    {
        pString name;
        StructName(pString n) : name(n) {};
    }
    names[Parameter::Number][2] =
    {
        {"��",  "Hz"},
        {"�",   "s"},
        {"�",   "V"},
        {"�",   "V"},
        {"�",   "s"},
        {"",    ""},
        {"o",   "o"},
        {"�",   "s"},
        {"",    ""},
        {"",    ""},
        {"",    ""},
        {"",    ""},
        {"",    ""},
        {"",    ""},
        {"",    ""},
        {"c",   "s"},
        {"c",   "s"},
        {"c",   "s"},
        {"",    ""}
    };
    sprintf(buf, "%s%s", order.Name(), names[value][LANG].name);
    return buf;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Parameter::IsOpened()
{
    return IsComplexParameter() && GetForm()->ParameterIsOpened();
}
