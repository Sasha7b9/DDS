#include "defines.h"
#include "Generator/Generator_p.h"
#include "Generator/MathSupport.h"
#include "Generator/Parameters.h"
#include "Menu/Menu.h"
#include "Menu/Pages/Addition/PageTuneParameter.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"
#include <cstdio>


void Parameter::SetForm(Form *f)
{
    form = f;
}


bool Parameter::IsValue() const
{
    return (kind == Value);
}


bool Parameter::IsComplex() const
{
    return (kind == Complex);
}


bool Parameter::IsChoice() const
{
    return (kind == Choice);
}


pString Parameter::Name(uint lang) const
{
    return name[lang];
}


void Parameter::SetParent(Parameter *p)
{
    parent = p;
}


Parameter *Parameter::GetParent()
{
    return parent;
}

bool Parameter::IsOpened() const
{
    return (parent != nullptr);
}


Form *Parameter::GetForm()
{
    return form;
}


void ParameterComplex::SetForm(Form *f)
{
    Parameter::SetForm(f);

    for (int i = 0; i < numParams; i++)
    {
        params[i]->SetForm(f);
    }
}


ParameterChoice *ParameterComplex::FindParameter(ParameterChoice::E p)
{
    for(int i = 0; i < numParams; i++)
    {
        Parameter *param = params[i];

        if(param->IsChoice())
        {
            ParameterChoice *parameter = static_cast<ParameterChoice *>(param);

            if(parameter->Type() == p)
            {
                return parameter;
            }
        }
    }

    return nullptr;
}


ParameterValue *ParameterComplex::FindParameter(ParameterValueType::E p)
{
    for(int i = 0; i < numParams; i++)
    {
        Parameter *param = params[i];

        if(param->IsValue())
        {
            ParameterValue *parameter = static_cast<ParameterValue *>(param);

            if(parameter->GetType() == p)
            {
                return parameter;
            }
        }
    }

    return nullptr;
}


pString ParameterValue::GetMainUnits(uint lang) const
{
    static const pString units[ParameterValueType::Count][2] =
    {
        {"��", "Hz"},   // Frequency
        {"�",  "s"},    // Period
        {"�",  "V"},    // Amplitude
        {"�",  "V"},    // Offset
        {"�",  "s"},    // Duration
        {"",   ""},     // DutyRatio
        {"",   ""},     // Phase
        {"�",  "s"},    // Delay
        {"�",  "s"},    // DurationRise
        {"�",  "s"},    // DurationFall
        {"�",  "s"},    // DurationStady
        {"",   ""},     // DutyFactor
        {"",   ""},     // ManipulationDuration
        {"",   ""},     // ManipulationPeriod
        {"",   ""},     // PacketPeriod
        {"",   ""},     // PacketNumber
        {"",   ""}      // Exit
    };

    return units[GetType()][lang];
}


pString ParameterValue::GetUnits(uint lang, Order::E order) const
{
    if (order == Order::Count)
    {
        order = MathFloatValue::GetOrder(value);
    }

    static char units[10];

    std::strcpy(units, Order::Suffix(order, lang));
    std::strcat(units, GetMainUnits(lang));

    return units;
}


bool ParameterValue::SetAndLoadValue(float val)
{
    if(!InRange(val))
    {
        return false;
    }

    value.FromFloat(val);

    PGenerator::SetParameter(this);

    return true;
}


bool ParameterValue::SetAndLoadValue(FloatValue val)
{
    if (!InRange(val))
    {
        return false;
    }

    value = val;

    PGenerator::SetParameter(this);

    return true;
}


pString ParameterComplex::GetStringValue() const
{
    if(type == Manipulation)
    {
        static pCHAR valuesRU[2] =
        {
            " ����", " ���"
        };

        static pCHAR valuesEN[2] =
        {
            " Off", " On"
        };

        ParameterChoice *enabled = const_cast<ParameterComplex *>(this)->FindParameter(ParameterChoice::ManipulationEnabled);

        if(LANGUAGE)
        {
            return valuesEN[enabled->GetChoice()];
        }

        return valuesRU[enabled->GetChoice()];
    }

    return "";
}


pString ParameterChoice::GetStringValue() const
{
    return names[choice];
}


void ParameterChoice::NextChoice()
{
    Math::CircleIncrease(&choice, 0, NumChoices() - 1);

    Chan::E ch = form->GetWave()->GetChannel();

    if(type == ModeStart)
    {
        PGenerator::LoadStartMode(ch, choice);
    }
    else
    {
        PGenerator::TuneChannel(ch);
    }
}


bool ParameterChoice::SetAndLoadChoice(int ch)
{
    if(ch < 0 || ch >= NumChoices())
    {
        return false;
    }

    choice = ch;

    PGenerator::SetParameter(this);

    return true;
}


int ParameterChoice::GetChoice() const
{
    return 0;
}


bool ParameterChoice::DrawChoice(int, int) const
{
    return true;
}


ParameterManipulation::ParameterManipulation(Parameter **parameters) : ParameterComplex(ParameterComplex::Manipulation, "�����������", "Manipulation", parameters)
{

}


bool ParameterValue::InRange(float val) const
{
    return (val >= min.ToFloat()) && (val <= max.ToFloat());
}


bool ParameterValue::InRange(FloatValue val) const
{
    return (val >= min && val <= max);
}


int ParameterChoice::NumChoices() const
{
    return 1;
}


ParameterValue::ParameterValue(ParameterValueType::E t, const char *nameRU, const char *nameEN, const FloatValue &_min, const FloatValue &_max, const FloatValue &_value) :
    Parameter(Parameter::Value, nameRU, nameEN), tuner(this), type(t), min(_min), max(_max), value(_value)
{
    tuner.Init();
}


pString ParameterValue::GetStringValue() const
{
    static char buffer[30];
    std::strcpy(buffer, MathFloatValue::GetIndicatedValue(this, IsSigned()));
    std::strcat(buffer, " ");
    std::strcat(buffer, GetUnits(LANGUAGE, MathFloatValue::GetOrder(value)));

    return buffer;
}


pString Order::Suffix(Order::E order, uint lang)
{
    static const pString suf[Count][2] =
    {
        {"�", "M"},
        {"�",  "k"},
        {"",   ""},
        {"�",  "m"},
        {"��", "u"},
        {"�",  "n"}
    };

    return suf[order][lang];
}


void ParameterChoice::OnPressButtonTune()
{
    NextChoice();
}


void ParameterValue::OnPressButtonTune()
{
    PageTuneParameter::SetParameter(this);
    Menu::SetAdditionPage(PageTuneParameter::self);
}


void ParameterComplex::OnPressButtonTune()
{
    form->OpenComplexParameter();
}


void Parameter::OnPressButtonTune()
{
    switch (kind)
    {
    case Value:   reinterpret_cast<ParameterValue *>(this)->OnPressButtonTune();   break;
    case Complex: reinterpret_cast<ParameterComplex *>(this)->OnPressButtonTune(); break;
    case Choice:  reinterpret_cast<ParameterChoice *>(this)->OnPressButtonTune();  break;

    case Exit:
    case Page:
        break;
    }
}
