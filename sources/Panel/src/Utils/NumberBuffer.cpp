#include "stdafx.h"
#ifndef WIN32
#include "NumberBuffer.h"
#include "Utils/StringUtils.h"
#include <string.h>
#include <cstdlib>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char *NumberBuffer::buffer = 0;
int NumberBuffer::size = 0;
int NumberBuffer::position = 0;
int NumberBuffer::max = 0;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NumberBuffer::Set(char *buf, int s, int p, int maxValue)
{
    buffer = buf;
    size = s;
    position = p;
    max = maxValue;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void NumberBuffer::ProcessKey(KeyEvent &key)
{
    if (key == KeyEvent::RegRight || key == KeyEvent::RegLeft)
    {
        ProcessRegulator(key);
    }
    else if(key == KeyEvent::Left)
    {
        if(position > 0)
        {
            --position;
        }
    }
    else if(key == KeyEvent::Right)
    {
        if(position < NumSymbols())
        {
            ++position;
        }
    }
    else if(AllowableSymbol(key) && position < NumSymbols())                    // ���������� ������
    {
        buffer[position++] = key.ToChar();
    }
    else
    {
        // ����� ������
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool NumberBuffer::AllowableSymbol(KeyEvent &key)
{
    if(key.IsDigit() || key.Is(KeyEvent::Dot) || key.Is(KeyEvent::Minus))
    {
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void NumberBuffer::ProcessRegulator(KeyEvent &key)
{
    if(NumSymbols() == 0)                           // ���� ����� ���� -
    {
        return;                                     // ������ �������, ������ �� �����
    }

    // ��������� ������ ��������, ����� ������������ ��� � ������, ���� ��� ��������� ��� �������� ������������
    char temp[32];
    std::memcpy(temp, buffer, (uint)size);

    if (key.Is(KeyEvent::RegRight))
    {
        IncreaseDigit(PositionSymbolForChange());
    }
    else if(key.Is(KeyEvent::RegLeft))
    {
        DecreaseDigit(PositionSymbolForChange());
    }
    else
    {
        // ����� ������
    }

    // ��������������� ������ ��������, ���� ����� ����� �� �������
    if(max != 0 && ToUINT() > (uint)max)
    {
        std::memcpy(buffer, temp, (uint)size);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int NumberBuffer::PositionSymbolForChange()
{
    return (NumSymbols() == position) ? (position - 1) : position;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool NumberBuffer::IncreaseDigit(int pos)
{
    if(buffer[pos] < '9')
    {
        ++buffer[pos];
        return true;
    }
    else
    {
        if (pos > 0)
        {
            if (IncreaseDigit(pos - 1))
            {
                buffer[pos] = '0';
                return true;
            }
        }
        else 
        {
            if (position == NumSymbols() && All9())
            {
                buffer[0] = '1';
                position++;
                for (int i = 1; i < position; i++)
                {
                    buffer[i] = '0';
                }
                buffer[position + 1] = 0;
                return true;
            }
        }
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool NumberBuffer::All9()
{
    for(int i = 0; i < NumSymbols(); i++)
    {
        if(buffer[i] != '9')
        {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool NumberBuffer::DecreaseDigit(int pos)
{
    if(buffer[pos] > '0')
    {
        --buffer[pos];
        return true;
    }
    else if(pos > 0)
    {
        if(DecreaseDigit(pos - 1))
        {
            buffer[pos] = '9';
            return true;
        }
    }
    else
    {
        // ����� ������
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int NumberBuffer::NumSymbols()
{
    return (int)size;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void NumberBuffer::PressBackspace()
{
    if (position > 0)
    {
        position--;
        for (int i = position; i < size; i++)
        {
            buffer[i] = 0;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int NumberBuffer::PositionCursor()
{
    return position;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
uint NumberBuffer::ToUINT()
{
    uint result = (uint)-1;
    if(!String2UInt(buffer, &result))
    {
        return (uint)-1;
    }

    return result;
}
