#pragma once
#include "Settings/SettingsTypes.h"
#include "Generator/Parameters.h"


struct FloatValue;
class Parameter;


/// ��������������� ����� ��� ��������� �������� ���������
class ParameterPainterSupporting
{
public:
    ParameterPainterSupporting();
    /// ���������� ���������������� ���������
    void SetParameter(Parameter *param);
    /// ��������� ���������� �������������� ��������
    uint NumSymbols() const;
    /// ���������� ������� X ������� � �������� pos
    int X(uint pos) const;
    /// ���������� ������ � ������� pos
    char Symbol(uint pos) const;
    /// ���������� � �������� ������ ���� �������� ������
    int X0() const;
    /// ���������� Y �������� ������ ���� ������� ������
    int Y0() const;
    /// ������ ������� ������
    int Width() const;
    /// �������������� ��������
    Parameter *parameter;
    /// ���������� ������� ��������� �������
    //uint GetPositionActive() const { return static_cast<uint>(positionActive); };
    /// ������ ���� �������
    int WidthDigit() const { return 11; };
    /// ������� ���� �������
    int HeightDigit() const { return 17; }

public:
    

    /// ������� ������� �������
    int x0;

    /// ���������� ������� ������� ������� ������ ���������
    uint PositionFirstUnit() const;
    /// ��������������� ������� ��������� �������
    void InitPositionActive();

};


/// ������������ ��� ��������� ��������� � ����������
class ParameterTuner
{
public:
    ParameterTuner() {}
    /// ���������� ��������, ���������� ���������
    void SetParameter(Parameter *param);
    /// ���������� �������� � ������ ���������
    void Draw();

    Parameter *GetParameter();

private:
    ParameterPainterSupporting support;
    /// ���������� ��� ���������
    void DrawNameParameter();
    /// ���������� ��������
    void DrawParameter();
    /// ���������� �������������� � �������������� �������
    void DrawHighlighter();
};



