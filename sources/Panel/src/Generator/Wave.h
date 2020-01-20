#pragma once
#include "defines.h"
#include "common/Common.h"
#include "Generator/Parameters.h"
#include "Settings/SettingsTypes.h"
#include <cstring>
#include <limits>


class Form
{
    friend class Wave;

public:
    TypeForm::E value;

    Form(TypeForm::E v = TypeForm::Count)
    {
        Init(v);
    };

    Form(uint8 v)
    {
        Init(static_cast<TypeForm::E>(v));
    };

    Form(TypeForm::E v, Parameter **param, Wave *w);

    void Init(TypeForm::E v)
    {
        value = v;
        wave = 0;
        params = nullptr;
        numParams = 0;
        currentParam = 0;
        oldParams = 0;
        oldNumParams = 0;
        oldCurrentParams = 0;
    };

    /// ���������� ������������ �������� ����� �������
    pString Name() const;
    /// ���������� ������ �� ������� ��������
    Parameter *CurrentParameter() const;
    /// ���������� ���������� ��������� ����������
    int NumParameters() const;
    /// ���������� ������ �� i-�� �������� �� ������� params
    Parameter *GetParameter(int i);
    /// ���������� ������� �������� ��������
    void SetNextParameter();
    /// ����������� ��������� � ������������ � �������������� �����������
    void TuneGenerator(Chan::E ch);
    /// ���������� true, ���� ��� ����� ������� ������������� e
    bool Is(TypeForm::E e) const { return e == value; };
    /// ���������� true, ���� ����� ������� ����������� � ������� ����
    bool IsDDS() const;
    /// ���������� ��������� �� ������������ Wave
    Wave *GetWave() { return wave; };
    /// ������� ���������� ��� ������� ������ "�������� ��������". ���������� ������������ ������� ��������
    void ChangeParameter();
    /// ��������� �������� ��������, ���� ������� ������� � ���������� true � ���� ������
    bool CloseOpenedParameter();
    /// ���������� ����������� �������
    void DrawUGO(Chan::E ch, int y0);
    /// ���������� ������ ������������� ������� ��� ���������
    static void SetFormFlash(Chan::E ch, const uint8 data[300]);
    /// ���������� ��������� �� ������ ������������� ������� ��� ���������
    static uint8 *GetFormFlash(Chan::E ch);
    /// �������� �������� �������
    float GetOffset();
    /// �������� ������ �������
    float GetAmplitude();

    operator TypeForm::E() { return value; }
    /// ������� ��������� ��������. ���������� 0, ���� ������ ��������� ���
    Parameter *FindParameter(ParameterValue::E p);
    Parameter *FindParameter(ParameterChoice::E p);
    /// �������� �������� � ���������
    void SendParameterToGenerator(ParameterValue::E p);
    void SendParameterToGenerator(ParameterChoice::E p);

private:
    /// ���������� �������� �������� ���������
    void OpenCurrentParameter();
    /// Wave, � �������� ��������� ������ Form
    Wave *wave;
    /// ����� �������� ���������
    Parameter **params;
    /// ������� ����� ����������
    int numParams;
    /// ����� �������� ��������� � ������� params
    int currentParam;

    /// ����� ����������� ��������� �� �������� ��������� � ������ ��������� �������� ���������
    Parameter **oldParams;
    /// ��������� � oldParams
    int oldNumParams;
    /// ��������� � oldParams
    int oldCurrentParams;

    static void DrawSine(Chan::E ch, int x, int y, int width, int height);

    static void DrawRampPlus(Chan::E ch, int x, int y, int width, int height);

    static void DrawRampMinus(Chan::E ch, int x, int y, int width, int height);

    static void DrawTriangle(Chan::E ch, int x, int y, int width, int height);

    static void DrawMeander(Chan::E ch, int x, int y, int width, int height);

    static void DrawImpulse(Chan::E ch, int x, int y, int width, int height);

    static void DrawPacketImpulse(Chan::E ch, int x, int y, int width, int height);

    static void DrawDDS(Chan::E ch, int x, int y, int width, int height);


};



class Wave
{
public:

    Wave(Chan::E ch, Form **forms);
    /// ���������� ������������� �����
    Form *GetCurrentForm();
    /// ���������� ������ ������� ����� �������.
    void SetIndexForm(int8 num);

    int NumberOfForms() const;

    Form *GetForm(int i);

    Form *GetForm(TypeForm::E form);

    Chan::E GetChannel() const { return channel; };
    /// ���������� true, ���� ���������� ������ ����� �������
    bool StartModeIsSingle();

private:
    /// ������ ������ ����������� ������
    Chan::E channel;
    /// ������� ����� ������� - ��������� �� ����� ������� � �������
    int indexCurrentForm;
    /// ������ ����, ������� ����� ���� ���������
    Form **forms;
    /// ���������� ��������� ����
    int numForms;

public:

    class Graphics
    {
    public:
        /// ���������� ���������� � ���������� ������� �� ������
        static void Draw(Chan::E ch);
        /// ������� x ������� ��������� �������
        static int X();
        /// ������� y ������� ��������� �������
        static int Y(Chan::E ch);
        /// ������ ������� ��������� �������
        static int Width();
        /// ������ ������� ��������� �������
        static int Height();
    private:

        static void DrawParameters(Chan::E chan, int y0);

        static void DrawParameterValue(Parameter *parameter, int x, int y);
    };
};
