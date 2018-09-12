#include "Command.h"
#include "defines.h"
#include "Log.h"
#include "Settings/Settings.h"
#include "Display/InputWindow.h"
#include "Generator.h"
#include <stdio.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct StructName
{
    pString nameRU;
    pString nameEN;
    StructName(pString nRU, pString nEN) : nameRU(nRU), nameEN(nEN) {};
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
    return MinValue() == -1.0f && MaxValue() == -1.0f;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString Parameter::Name() const
{
    return LANG_RU ? (char *)nameParameter[value].nameRU : (char *)nameParameter[value].nameEN;
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
    for(int i = 0; i < Form::Number; i++)
    {
        if(forms[i].value == Form::Number)
        {
            return i;
        }
    }

    return Form::Number;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Wave::Wave(Chan ch, Form form[Form::Number]) : channel(ch)
{
    currentForm = 0;

    for(int i = 0; i < Form::Number; i++)
    {
        forms[i] = form[i];
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Form::Form(E v, Parameter param[Parameter::Number]) : value(v), currentParam(0)
{
    for(int i = 0; i < Parameter::Number; i++)
    {
        params[i] = param[i];
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
    for(int i = 0; i < Parameter::Number; i++)
    {
        if(params[i].Is(Parameter::Number))
        {
            return i;
        }
    }

    return Parameter::Number - 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Parameter *Form::GetParameter(int i)
{
    return &params[i];
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
    for(int i = 0; i < Parameter::Number; i++)
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
        InputWindow::Struct input(this, param);
        Generator::SetParameter(ch, p, input.Value());
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Form::OpenCurrentParameter()
{
    if(!CurrentParameter()->IsComplexParameter())
    {
        return;
    }


}
