#pragma once
#include "defines.h"


struct TypeForm
{
    enum E
    {
        Sine,           ///< �����
        RampPlus,       ///< ����+
        RampMinus,      ///< ����-
        Triangle,       ///< �����������
        Meander,        ///< ������
        Impulse,        ///< ��������
        PacketImpuls,   ///< ����� ���������
        Free,           ///< ������������ ������
        Count
    };
};


struct FloatValue
{
    explicit FloatValue(int units, uint mUnits, uint uUnits = 0, uint nUnits = 0);

    explicit FloatValue(float v);

    float ToFloat() const;

    void FromFloat(float v);

    void FromUINT64(uint64 v) { value = v; }

    uint64 ToUINT64() const { return value; }

    int Sign() const;

    uint64 Abs() const;

    void Divide(uint div);

    void Multiplie(uint mul);
    /// ��������� �� �������� ��������
    void Add(float v);

    void SetSign(int sign);
    /// ���������� ����� ����� �����
    int Integer() const;
    /// ���������� ������� ����� �����. numDigits - ��������� ���������� ��������� ����� �������
    int Fract(int numDigits) const;
    /// ���������� ���������� ���������� � ������� �����
    int FractNano() const;

    pString GetStringDigits() const;

    struct Math
    {
        /// ���������� ������� ������� ���������� �������
        /// "1" - ������� (1e1), "0" - ������� (1e0), "-1" - ������� (1e-1), "-2" - ����� (1e-2)
        static int GetPositionFirstDigit(const FloatValue &value);
        /// ���������� ����� � ������� position
        static int GetDigit(const FloatValue &value, int position);
    };

private:

    uint64 value;       // �������� ��������� � �������� ��������� "����". ������������� � "1" ������� ��� ��������, ��� ����� �������������
};
