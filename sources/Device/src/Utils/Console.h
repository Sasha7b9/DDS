#pragma once
#include "Command.h"




class Console
{
public:
    static void AddString(char *buffer);
    //static void AddFormatString(char *format, ...);
    static void AddString(pString buffer);
    //static void AddFloat(float value);
    static void AddInt(int value);
    static bool ExistString();
    /// ���������� ������������ ������
    static char *GetString();
    /// ������� ������������ ������ �� ���������
    static void DeleteString();
};
