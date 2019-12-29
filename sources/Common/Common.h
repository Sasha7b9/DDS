#pragma once
#include "defines.h"
#include "structs.h"


class ParameterValue;


struct Order
{
    enum E
    {
        Nano,       // ����
        Micro,      // �����
        Milli,      // �����
        One,        // �������
        Kilo,       // ����
        Mega,       // ����
        Count
    } value;
    Order(E v = Count) : value(v) { };
    operator uint8() const { return static_cast<uint8>(value); };
    pString Name() const;
    Order &operator++(int);
    Order &operator--(int);
    static Order::E Min(const ParameterValue *param);
    static Order::E Max(const ParameterValue *param);
};


struct FloatValue
{
    /// ���������� ��������� ���������� ����������
    explicit FloatValue(uint64 v)
    {
        FromUINT64(v);
    }

    explicit FloatValue(float v);

    float ToFloat() const;

    void FromFloat(float v);

    void FromUINT64(uint64 v);
    /// ���������� ���������� ����������
    uint64 ToUINT64() const;

    int Sign() const;
    /// ���������� �������� � ������������
    uint64 Abs() const;

    void DividePow10(uint pow);

    void MultipliePow10(uint pow);
    /// ��������� �� �������� ��������
    void Add(float v);

    void SetSign(int sign);

    uint Integer() const;

    uint Fract() const;

    pString ToStringDigits(Order order, int numDigits) const;

private:
    static const int SIZE_BUFFER = 25;
    /// ����� �������� ����� � ������� ����� �����, ���������� �������� ','
    uint8 buffer[SIZE_BUFFER];
    // ���� ����� �������������, ����� ����
    int8 sign;
    /// ��������� ����� ���������� �� ����������
    void FillBufferFromNano(uint64 value, bool negative);
};
