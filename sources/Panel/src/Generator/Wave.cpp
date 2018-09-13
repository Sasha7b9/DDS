#include "Command.h"
#include "defines.h"
#include "Log.h"
#include "Settings/Settings.h"
#include "Display/InputWindow.h"
#include "Generator.h"
#include <stdio.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pString Form::Name(Language lang) const
{
    struct StrName
    {
        pString nameRu;
        pString nameEn;
        StrName(pString nRu, pString nEn) : nameRu(nRu), nameEn(nEn) { };
        pString Name(Language lang) { return lang == Language::RU ? nameRu : nameEn; }
    };

    static StrName names[Form::Number] =
    {
        StrName("�����",    "SINE"),
        StrName("����+",    "RAMP+"),
        StrName("����-",    "RAMP-"),
        StrName("������",   "MEANDER"),
        StrName("�������",  "IMPULSE")
    };

    return names[value].Name(lang);
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
        pString nameRU;
        pString nameEN;
        StructName(pString nRU, pString nEN) : nameRU(nRU), nameEN(nEN) { };
    }
    nameParameter[Parameter::Number] =
    {
        StructName("�������",        "FREQUENCY"),
        StructName("������",         "PERIOD"),
        StructName("������",         "AMPLITUDE"),
        StructName("��������",       "OFFSET"),
        StructName("����.",          "DURATION"),
        StructName("����������",     "DUTY RATIO"),
        StructName("����",           "PHASE"),
        StructName("��������",       "DELAY"),
        StructName("�����. ���.",    "MOD. INDEX"),
        StructName("����������",     "POLARITY"),
        StructName("��. ����������", "BUILD-UP TIME"),
        StructName("��. �����",      "RELEASING TIME"),
        StructName("��. ����",       "PEAK TIME"),
        StructName("�����. ������.", "DUTY FACTOR"),
        StructName("���������",      "Modulation")
    };

    return LANG_RU ? nameParameter[value].nameRU : nameParameter[value].nameEN;
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
Form::Form(E v, Parameter *parameters, int num) : value(v), params(parameters), numParams(num), currentParam(0)
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

    SendParameterToGenerator(ch, Parameter::Frequency);
    SendParameterToGenerator(ch, Parameter::Amplitude);
    SendParameterToGenerator(ch, Parameter::Offset);
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

    if(parent->value == Parameter::ModulationRampSine)
    {
        //Generator::Ty
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Form::CloseOpenedParameter()
{
    if (params[0].parent)
    {
        params = oldParams;
        numParams = oldNumParams;
        currentParam = oldCurrentParams;
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float Parameter::GetValue() const
{
    StructValue input((Parameter *)this);
    return input.Value();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char *Parameter::GetStringValue() const
{
    StructValue input((Parameter *)this);
    return input.StringValue();
}
