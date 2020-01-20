#pragma once
#include "common/Common.h"
#include "common/Command.h"


struct Settings
{
    FloatValue amplitude[Chan::Count];  ///< ������ ��� ����� �������
    FloatValue offset[Chan::Count];     ///< �������� ��� ����� �������
};


extern Settings set;
