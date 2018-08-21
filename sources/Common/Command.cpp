#include "Command.h"
#include "defines.h"
#include "Log.h"
#include <Settings/Settings.h>
#include <stdio.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char * namesWaveForm[WaveForm::Number][2] =
{
    { "�����",        "SINE" },
    { "�������",      "COSINE" },
    { "������",       "MEANDER"},
    { "����+",        "RAMP+" },
    { "����-",        "RAMP-"},
    { "�����������",  "TRIANGLE"},
    { "��������",     "TRAPEZE"},
    { "�������",      "IMPULSE" },
    { "����������+",  "EXPONENT+"},
    { "����������-",  "EXPONENT-"},
    { "���",          "NOISE"},
    { "������������", "FREE"}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *Command_Name(CommandPanel command)
{
    static const char *names[CommandPanel::Number] =
    {
        "SERVICE",
        "ENABLE",
        "SET FORM",
        "SET FREQUENCY",
        "SET AMPLITUDE",
        "SET OFFSET",
        "SET DURATION",
        "SET DUTYRATIO",
        "SET PHASE",
        "RUN RESET",
        "MODE DEBUG"
    };

    if (command >= CommandPanel::Number)
    {
        static char buffer[10] = {0};
        sprintf(buffer, "%x", static_cast<uint8>(command));
        LOG_WRITE("������ - ������� %s", buffer);
    }
    return const_cast<char *>(names[command]);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString WaveForm::Name() const
{
    return NAME_FORM(type, LANG);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString Register::Name() const
{
    static pString names[Register::Number] =
    {
        "������������� 1",
        "������������� 2",
        "5697 �������� 1",
        "5697 �������� 2",
        "5697 ���� �������",
        "5697 ���� ����������",
        "RG0 ����������",
        "RG1 �������",
        "RG2 ����������",
        "RG3 ������� �",
        "RG4 ������� B",
        "RG5 ������ ��������� �",
        "RG6 ����. ��������� �",
        "RG7 ������ ��������� B",
        "RG8 ����. ��������� B",
        "RG9 �����. �����������",
        "RG10 ��������",
        "������������� 3"
    };

    return names[name];
}
