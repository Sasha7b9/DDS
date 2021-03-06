#include "defines.h"
#include "common/Common.h"
#ifdef PANEL
#include "Display/Text.h"
#endif
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

// ����� ��� ���������� ���������� �������� �������
static Order::E stored = Order::Count;

// ������ ���� ����� �� buffer. ���������� ��������� �� ������ ������� ����� �����
static bool GetSign(int &sign, char *begin, char **end);

// ���������� �������� �� ������� (������� e)
static bool GetIntPart(Value &value, char *begin, char **end, int numDigitsAfterComma);

// ���������� ������� (��, ��� ����� ������� e)
static bool GetPower(int &power, char *begin, char **end);


Value::Value(const char *const buffer, Order::E order) //-V730
{
    FromString(buffer, Order::GetPow10(order));
}


Value::Value(double v)
{
    FromDouble(v);
}


Value::Value(int v)
{
    FromINT(v);
}


bool Value::FromString(const char *buffer, char **end, int numDigitsAfterComma) //-V2506
{
    char *begin = const_cast<char *>(buffer); //-V2567

    int sign = 0;

    if (!GetSign(sign, begin, end))
    {
        return false;
    }

    begin = *end;

    if (!GetIntPart(*this, begin, end, numDigitsAfterComma))
    {
        return false;
    }

    begin = *end;

    int pow = 0;
    
    if (!GetPower(pow, begin, end))
    {
        return false;
    }

    MulPow10(pow);

    SetSign(sign);

    return true;
}


static bool GetSign(int &sign, char *begin, char **end) //-V2506
{
    if (*begin == '-')
    {
        *end = begin + 1; //-V2563
        sign = -1;
        return true;
    }
    else if (*begin == '+') //-V2516
    {
        *end = begin + 1; //-V2563
        sign = 1;
        return true;
    }

    if (*begin >= '0' && *begin <= '9')
    {
        *end = begin;
        sign = 1;
        return true;
    }

    *end = begin;
    return false;
}


#ifdef PANEL
static bool GetIntPart(Value &value, char *begin, char **end, int numDigitsAfterComma) //-V2506
{
    *end = begin;

    if (*begin < '0' || *begin > '9')
    {
        return false;
    }

    String buffer;

    bool comma = false;         // true ����� ��������, ��� ����� ��� ����

    while ((**end >= '0' && **end <= '9') || **end == '.' || **end == ',')
    {
        if (**end == '.' || **end == ',')
        {
            comma = true;
        }
        else if(comma) //-V2516
        {
            numDigitsAfterComma--;
        }

        if (numDigitsAfterComma >= 0)
        {
            buffer.Append(**end);
        }
        
        *end = *end + 1; //-V2563
    }

    value = Value(buffer.c_str(), Order::One);

    return true;
}
#else
static bool GetIntPart(Value &, char *, char **, int)
{
    return true;
}
#endif


#ifdef PANEL
static bool GetPower(int &pow, char *begin, char **end) //-V2506
{
    if (*begin != 'e' && *begin != 'E')
    {
        *end = begin;
        pow = 0;
        return true; 
    }

    begin++;

    if ((*begin < '0' || *begin > '9') && (*begin != '-' && *begin != '+'))
    {
        *end = begin;
        pow = 0;
        return true;
    }

    String buffer;

    while ((*begin >= '0' && *begin <= '9') || *begin == '-' || *begin == '+')
    {
        buffer.Append(*begin);
        begin++;
    }

    *end = begin;

    pow = Value(buffer.c_str(), Order::One).Integer();

    return true;
}
#else
static bool GetPower(int &, char *, char **)
{
    return true;
}
#endif


void Value::FromString(const char *const buffer, int pow10)
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

    if (buffer[end] == '.' || buffer[end] == ',') //-V2563
    {
        mUnits = AssembleTriple(buffer, end + 1, &end);
        uUnits = AssembleTriple(buffer, end, &end);
        nUnits = AssembleTriple(buffer, end, &end);
    }

    FromUnits(units, mUnits, uUnits, nUnits, sign);

    if (pow10 > 0)
    {
        uint pow = Math::Pow10(pow10);
        Mul(pow);
    }
    else if (pow10 < 0) //-V2516
    {
        uint pow = Math::Pow10(-pow10);
        Div(pow);
    }
}


void Value::FromUnits(int units, uint mUnits, uint uUnits, uint nUnits, int sign)
{
    value = static_cast<uint>(units);
    value *= 1000 * 1000 * 1000;

    value += static_cast<uint>(nUnits + uUnits * 1000 + mUnits * 1000 * 1000);

    if (sign < 0)
    {
        SetSign(sign);
    }
}


static void ProcessSign(const char *const buffer, int *pos, int *sign)
{
    if (buffer[0] == '+') //-V2563
    {
        *sign = 1;
        *pos = *pos + 1;
    }
    else if (buffer[0] == '-') //-V2516 //-V2563
    {
        *sign = -1;
        *pos = *pos + 1;
    }
}


static int FindIntegerPart(const char *const buffer, int start)
{
    int pos = start;

    while (buffer[pos] >= '0' && buffer[pos] <= '9') //-V2563
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
        stack[posStack++] = buffer[i]; //-V2563
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

    while ((buffer[i] >= '0' && buffer[i] <= '9') && //-V2563
           (posStack < 3))
    {
        stack[posStack] = buffer[i]; //-V2563
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


void Value::FromDouble(double v)
{
    int sign = (v < 0.0) ? -1 : 1;

    value = static_cast<uint64>(std::fabs(v) * 1.E9);

    if (sign < 0)
    {
        SetSign(-1);
    }
}


void Value::FromINT(int v)
{
    FromUnits(v < 0 ? -v : v, 0, 0, 0, v < 0 ? -1 : 1);
}


double Value::ToDouble() const
{
    return static_cast<double>(Abs()) / 1E9 * static_cast<double>(Sign());
}


int Value::Sign() const
{
    //                fedcba9876543210
    return (value & 0x8000000000000000U) ? -1 : 1;
}


uint64 Value::Abs() const
{   //                fedcba9876543210
    return (value & 0x7fffffffffffffff);
}


void Value::Div(uint div)
{
    int sign = Sign();

    SetSign(1);

    value /= div;

    SetSign(sign);
}


void Value::Mul(uint mul)
{
    int sign = Sign();

    SetSign(1);

    value *= mul;

    SetSign(sign);
}


void Value::SetSign(int sign)
{
    if (sign >= 0)
    {
        //         fedcba9876543210
        value &= 0x7FFFFFFFFFFFFFFFU;       // \todo ��� ��� ����� ��������?
    }
    else
    {
        //         fedcba9876543210
        value |= 0x8000000000000000U;           // ������������� ������� �������������� �����
    }
}


int Value::Integer() const
{
    uint64 val = Abs();

    return static_cast<int>(val / (1000 * 1000 * 1000)) * Sign();
}


int Value::FractNano() const
{
    Value val = *this;
    val.SetSign(1);

    int whole = val.Integer();

    return static_cast<int>(val.value - static_cast<int>(whole * 1000 * 1000 * 1000));
}


void Value::Add(Value add)
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


void Value::Sub(Value val)
{
    val.SetSign(-val.Sign());

    Add(val);
}


void Value::MulPow10(int pow)
{
    while (pow > 0)
    {
        Mul(10);
        pow--;
    }

    while (pow < 0)
    {
        Div(10);
        pow++;
    }
}


bool Value::operator<(const Value &rhs)
{
    return ToDouble() < rhs.ToDouble();
}


bool Value::operator<=(const Value &rhs)
{
    return ToDouble() <= rhs.ToDouble();
}


bool Value::operator>(const Value &rhs)
{
    return ToDouble() > rhs.ToDouble();
}


bool Value::operator>=(const Value &rhs)
{
    return ToDouble() >= rhs.ToDouble();
}


bool Value::operator==(const Value &rhs)
{
    return (value == rhs.value);
}


bool Value::operator!=(const Value &rhs)
{
    return (value != rhs.value);
}


Order::E Value::GetOrder() const //-V2506
{
    Value temp = *this;
    temp.SetSign(1);

    int integer = temp.Integer();

    if      (integer >= 1000 * 1000) { return Order::Mega;  }
    else if (integer >= 1000)        { return Order::Kilo;  }
    else if (integer > 0)            { return Order::One;   } //-V2516

    int fract = temp.FractNano();

    if      (fract >= 1000 * 1000)   { return Order::Milli; }
    else if (fract >= 1000)          { return Order::Micro; }
    else if (fract > 0)              { return Order::Nano;  } //-V2516

    return Order::One;
}


void Order::Store(Order::E order)
{
    stored = order;
}


Order::E Order::Restore()
{
    return stored;
}


int Order::GetPow10(Order::E order)
{
    static const int pows[Count] =
    {
        6,  // Mega
        3,  // Kilo
        0,  // One
        -3, // Milli
        -6, // Micro
        -9  // Nano
    };

    return pows[order];
}
