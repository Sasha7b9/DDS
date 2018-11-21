#pragma once
#include "Command.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Console
{
public:
    static bool ExistString();
    /// ���������� ������������ ������
    static char *GetString();
    /// ������� ������������ ������ �� ���������
    static void DeleteString();

    static void AddString(char *format, ...);

private:
    static void AddConstString(char *buffer);
    static void AddConstString(pString buffer);
};
