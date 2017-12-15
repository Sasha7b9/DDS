#pragma once
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LIMITATION(var, value, min, max)    var = (value); if(var < (min)) { (var) = (min); } else if(var > (max)) { var = (max); };
#define LIMIT_BELOW(var, min)               if((var) < (min)) (var) = (min);
#define LIMIT_ABOVE(var, max)               if((var) > (max)) (var) = (max);

#define CIRCLE_DECREASE(x, min, max)    if((--(x)) < (min)) x = (max);
#define CIRCLE_INCREASE(x, min, max)    if((++(x)) > (max)) x = (min);

/// ���������� ������������ �������� �� ���
float MaxFloat(float val1, float val2, float val3);

int Math_Sign(int vlaue);
/// ��������� � �������� �� ������ val delta. ���� ��������� �� ����������� � �������� [min; max], ����������
void AddLimitationFloat(float *val,             ///< �� ����� ������ �������� ��������.
                        float delta,            ///< � ��� ������.
                        float min,              ///< ������ ������� ���������.
                        float max               ///< ������� ������� ���������.
);
/// ���������� ������� ������� symbol � ������ string. ���� ������ �� ���������, ���������� -1
int FindSymbol(char *string, char symbol);
/// ���������� ���������� ���������� �������� � �����
int NumDigitsInUInt(uint value);
