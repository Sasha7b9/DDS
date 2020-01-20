#pragma once
#include "Common.h"
#include "Command.h"


struct Settings
{
    FloatValue amplitude[Chan::Count];  ///< ������ ��� ����� �������
    FloatValue offset[Chan::Count];     ///< �������� ��� ����� �������
};


extern Settings set;
