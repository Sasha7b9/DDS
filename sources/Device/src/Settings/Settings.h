#pragma once
#include "Command.h"


struct Settings
{
    ParamValue amplitude[Chan::Count];  ///< ������ ��� ����� �������
    ParamValue offset[Chan::Count];     ///< �������� ��� ����� �������
};


extern Settings set;
