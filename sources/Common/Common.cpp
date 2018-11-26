#include "Common.h"
#include <cmath>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParamValue::ParamValue(float v)
{
    FromFloat(v);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ParamValue::FromFloat(float v)
{
    int sign = (v < 0.0f) ? -1 : 1;

    value = (uint64)(std::fabsf(v) * 1.e9f);

    if (sign < 0)
    {
        SetSign(-1);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float ParamValue::ToFloat() const
{
    return Abs() / 1e9f * (float)Sign();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int ParamValue::Sign() const
{
    //    fedcba9876543210
    return (value & 0x8000000000000000) ? -1 : 1;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint64 ParamValue::Abs() const
{               //    fedcba9876543210
    return (value & 0x7fffffffffffffff);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ParamValue::Divide(uint div)
{
    value /= div;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ParamValue::Multiplie(uint mul)
{
    value *= mul;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ParamValue::SetSign(int sign)
{
    if (sign > 0)
    {
        value &= 0x8000000000000000;
    }
    else
    {
        //         fedcba9876543210
        value |= 0x8000000000000000;           // ������������� ������� �������������� �����
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ParamValue::Add(float v)
{
    FromFloat(ToFloat() + v);
}
