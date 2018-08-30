#include "BigNumber.h"
#include "Utils/StringUtils.h"
#include "Utils/Math.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BigNumber::Number BigNumber::integer;
BigNumber::Number BigNumber::fract;
char BigNumber::sign = ' ';



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BigNumber::Set(char integer_[SIZE], char fract_[SIZE], char sign_)
{
    FillValue(integer_, integer);
    integer.numSymbols++;           // ��������� ���� ������, ����� ���� ����� ��� ���������� ������������
    FillValue(fract_, fract);
    sign = sign_;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::FillValue(char buffer[SIZE], Number &number)
{
    number.Clear();

    char *pos = &buffer[SU::FindSymbol(buffer, '\0') - 1];  // ������� ����� ���������� ������� � ������

    int pow = 1;

    while (pos >= buffer)
    {
        number.AddValue(*pos, pow);
        pow *= 10;
        pos--;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::ChangeDigit(int position, Step step)
{
    if (position < 0)
    {
        position = -position - 1;                       // ������������� ������� ��� ������� �������������� ������� � �����
        ChangeInteger(position, step);
    }
    else
    {
        position = fract.numSymbols - position;         // ������������� ������� ��� ������� �������������� ������� � �����
        ChangeFract(position, step);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::ChangeInteger(int position, Step step)
{
    if (sign == '-')
    {
        ChangeIntegerNegative(position, step);
    }
    else
    {
        ChangeIntegerPositive(position, step);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::ChangeFract(int position, Step step)
{
    if (sign == '-')
    {
        ChangeFractNegative(position, step);
    }
    else
    {
        ChangeFractPositive(position, step);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::ChangeIntegerPositive(int position, Step step)
{
    if (step.IsPlus())
    {
        ChangeIntegerPositivePlus(position);
    }
    else
    {
        ChangeIntegerPositiveMinus(position);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::ChangeIntegerPositivePlus(int position)
{
    integer.value += Pow10(position);                       // ������ ���������� ���� ��������, ��������������� ������� �������
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::ChangeIntegerPositiveMinus(int position)
{
    if (integer.value == 0 && fract.value == 0)             // ���� ������� ��������, �� ���������� ��������, ��������������� ������� �������.
    {                                                       // � ������ ���� �� �����. ��� ����� �������� ����������
        integer.value = Pow10(position);
        sign = '-';
    }
    else if (integer.value >= Pow10(position))          // ���� ����� �������� ������
    {
        integer.value -= Pow10(position);               // �������� ��������
    }
    else                                                    // ��� ����������, ����� ������ ����������� � ������ ����
    {
        integer.value = fract.value = 0;                    // � ���� ������ ������ �������� �����
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::ChangeIntegerNegative(int position, Step step)
{
    if (step.IsPlus())
    {
        ChangeIntegerNegativePlus(position);
    }
    else
    {
        ChangeIntegerNegativeMinus(position);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::ChangeIntegerNegativePlus(int position)
{
    if (integer.value == 0 && fract.value == 0)
    {
        integer.value = Pow10(position);
        sign = '+';
    }
    else if (integer.value >= Pow10(position))
    {
        integer.value -= Pow10(position);
    }
    else
    {
        integer.value = fract.value = 0;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::ChangeIntegerNegativeMinus(int position)
{
    integer.value += Pow10(position);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::ChangeFractPositive(int position, Step step)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void BigNumber::ChangeFractNegative(int position, Step step)
{

}
