#pragma once
#include "common/Common.h"


class Form;


class Parameter
{
public:
    virtual pString Name() const = 0;

    virtual void SetForm(Form *form);

private:
    /// �����, ��� ������� ���� ���� ��������
    Form *form;
};


class ParameterValue : public Parameter
{
public:
    virtual pString Name() const override
    {
        return "";
    }
};


class ParameterComplex : public Parameter
{
public:
    virtual void SetForm(Form *form) override;
};


class ParameterChoice : public Parameter
{

};
