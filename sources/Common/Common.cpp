#include "defines.h"
#include "Common.h"
#include "Utils/Math.h"
#include <cmath>


// ������� ����, ���� ������ ������� buffer - ����. � pos ������������ ������� �������� �� ������ � ���� ������
static void ProcessSign(const char *const buffer, int *pos, int *sign);

// ������� ������ �� ��������� ��������� ����� ����� �����
static int FindIntegerPart(const char *const buffer, int start);

// ������� ����� ����� �� ������ ��������
static uint AssembleInteger(const char *const buffer, int start, int end);

// ������� ����� �� ���� ��� ����� ��������. � end ������������ ������� ���������� �������
static uint AssembleTriple(const char *const buffer, int start, int *end);


//FloatValue::FloatValue(int units, uint mUnits, uint uUnits, uint nUnits)
//{
//    FromUnits(units, mUnits, uUnits, nUnits);
//}


FloatValue::FloatValue(const char *const buffer, int order) //-V730
{
    FromString(buffer, order);
}


FloatValue::FloatValue(float v)
{
    FromFloat(v);
}


void FloatValue::FromUnits(int units, uint mUnits, uint uUnits, uint nUnits)
{
    int sign = 1;

    if (units < 0)
    {
        sign = -1;
        units = -units;
    }

    value = static_cast<uint>(units);
    value *= 1000 * 1000 * 1000;

    value += nUnits + uUnits * 1000 + mUnits * 1000 * 1000;

    if (sign < 0)
    {
        SetSign(sign);
    }
}


void FloatValue::FromString(const char * const buffer, int order)
{
    int pos = 0;                                    // ������� �������������� ������� � buffer
    int sign = 1;                                   // ������������� �������� �������� ������������� ����

    ProcessSign(buffer, &pos, &sign);               // ������������ ���������� � �����

    int units = 0;
    uint mUnits = 0;
    uint uUnits = 0;
    uint nUnits = 0;

    int end = FindIntegerPart(buffer, pos);         // ������� ��������� ����� �����

    units = static_cast<int>(AssembleInteger(buffer, pos, end));    // ������� ����� �����

    if (buffer[end] == '.')
    {
        mUnits = AssembleTriple(buffer, end + 1, &end);
        uUnits = AssembleTriple(buffer, end, &end);
        nUnits = AssembleTriple(buffer, end, &end);
    }

    FromUnits(units * sign, mUnits, uUnits, nUnits);

    if (order > 0)
    {
        uint pow = Math::Pow10(order);
        Multiplie(pow);
    }
    else if (order < 0)
    {
        uint pow = Math::Pow10(-order);
        Divide(pow);
    }
}


static void ProcessSign(const char *const buffer, int *pos, int *sign)
{
    if (buffer[0] == '+')
    {
        *sign = 1;
        *pos = *pos + 1;
    }
    else if (buffer[0] == '-')
    {
        *sign = -1;
        *pos = *pos + 1;
    }
}


static int FindIntegerPart(const char *const buffer, int start)
{
    int pos = start;

    while (buffer[pos] >= '0' && buffer[pos] <= '9')
    {
        pos++;
    }

    return pos;
}


static uint AssembleInteger(const char *const buffer, int start, int end)
{
    char stack[20];

    int posStack = 0;

    for (int i = start; i < end; i++)
    {
        stack[posStack++] = buffer[i];
    }

    uint result = 0;

    uint pow = 1;

    while (posStack > 0)
    {
        char value = stack[(posStack--) - 1];

        result += (value & 0x0F) * pow;

        pow *= 10;
    }

    return result;
}


static uint AssembleTriple(const char *const buffer, int start, int *end)
{
    char stack[3];
    int posStack = 0;

    uint result = 0;

    int i = start;

    while ((buffer[i] >= '0' && buffer[i] <= '9') &&
           (posStack < 3))
    {
        stack[posStack] = buffer[i];
        posStack++;
        i++;
    }

    while (posStack < 3)                    // �������� �� 3 ��������
    {
        stack[posStack++] = '0';
    }

    *end = i;

    uint pow = 1;

    while (posStack > 0)
    {
        char value = stack[(posStack--) - 1];

        result += (value & 0x0F) * pow;

        pow *= 10;
    }

    return result;
}


void FloatValue::FromFloat(float v)
{
    int sign = (v < 0.0F) ? -1 : 1;

    value = static_cast<uint64>(std::fabsf(v) * 1.E9F);

    if (sign < 0)
    {
        SetSign(-1);
    }
}


float FloatValue::ToFloat() const
{
    return static_cast<float>(Abs()) / 1E9F * static_cast<float>(Sign());
}


int FloatValue::Sign() const
{
    //    fedcba9876543210
    return (value & 0x8000000000000000U) ? -1 : 1;
}


uint64 FloatValue::Abs() const
{               //    fedcba9876543210
    return (value & 0x7fffffffffffffff);
}


void FloatValue::Divide(uint div)
{
    int sign = Sign();

    SetSign(1);

    value /= div;

    SetSign(sign);
}


void FloatValue::Multiplie(uint mul)
{
    int sign = Sign();

    SetSign(1);

    value *= mul;

    SetSign(sign);
}


void FloatValue::SetSign(int sign)
{
    if (sign > 0)
    {
        value &= 0x7FFFFFFFFFFFFFFFU;       // \todo ��� ��� ����� ��������?
    }
    else
    {
        //         fedcba9876543210
        value |= 0x8000000000000000U;           // ������������� ������� �������������� �����
    }
}


void FloatValue::Add(float v)
{
    FromFloat(ToFloat() + v);
}


int FloatValue::Integer() const
{
    uint64 val = Abs();

    return static_cast<int>(val / (1000 * 1000 * 1000)) * Sign();
}


int FloatValue::Fract(int numDigits) const
{
    float fract = ToFloat() - static_cast<float>(Integer());

    return static_cast<int>(fract * static_cast<float>(::Math::Pow10(numDigits)));
}


int FloatValue::FractNano() const
{
    FloatValue val = *this;
    val.SetSign(1);

    int whole = val.Integer();

    return static_cast<int>(val.value - whole * 1000 * 1000 * 1000);
}


void FloatValue::Add(FloatValue add)
{
    int sign = Sign();
    int signAdd = add.Sign();

    SetSign(1);
    add.SetSign(1);

    if(sign > 0 && signAdd > 0)
    {
        value += add.value;
    }
    else if(sign < 0 && signAdd < 0)
    {
        value += add.value;
        SetSign(-1);
    }
    else if(sign > 0 && signAdd < 0)
    {
        if(value >= add.value)
        {
            value -= add.value;
        }
        else
        {
            value = add.value - value;
            SetSign(-1);
        }
    }
    else
    {
        if(add.value >= value)
        {
            value = add.value - value;
        }
        else
        {
            value -= add.value;
            SetSign(-1);
        }
    }
}


bool FloatValue::operator<(const FloatValue &rhs)
{
    return ToFloat() < rhs.ToFloat();
}


bool FloatValue::operator<=(const FloatValue &rhs)
{
    return ToFloat() <= rhs.ToFloat();
}


bool FloatValue::operator>(const FloatValue &rhs)
{
    return ToFloat() > rhs.ToFloat();
}


bool FloatValue::operator>=(const FloatValue &rhs)
{
    return ToFloat() >= rhs.ToFloat();
}
