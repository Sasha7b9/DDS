#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "Command.h"
#include "structs.h"
#include "Utils/StringUtils.h"
#include "log.h"
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pString Command::Name() const
{
    static const struct StructName
    {
        pString name;
        StructName(pString n) : name(n) {};
    }
    names[Number] =
    {
        "RequestData",
        "EnableChannel",
        "SetFormWave",
        "SetFrequency",
        "SetAmplitude",
        "SetOffset",
        "SetDuration",
        "SetDutyRatio",
        "SetPhase",
        "RunReset",
        "ModeDebug",
        "SetDelay",
        "WriteRegister",
        "SetDurationRise",
        "SetDurationFall",
        "SetDurationStady",
        "SetDutyFactor",
        "SetManipulation",
        "SetManipulationDuration",
        "SetManipulationPeriod",
        "SetPacketPeriod",
        "SetPacketNumber",
        "SetStartMode",
        "SetPeriod",
        "SetPolarity",
        "SetModeManipulation",
        "LoadFormDDS",
        "FreqMeasure",
        "Log",
        "FDrive_NumDirsAndFiles",
        "FDrive_Mount",
        "FDrive_RequestDir",
        "FDrive_RequestFile",
        "Test"
    };
    if(value < Number)
    {
        return names[value].name;
    }
    
    /// \todo ����� �������� ��� - ��� ����������� ������ �������� SIZE ��������� ������, ���� �� ������ � ������� Command::Trace()
    /// ��������, ��� ���������� ��-�� ������������� CCM RAM
    const int SIZE = 23;
    static char buffer[SIZE + 1];
    snprintf(buffer, SIZE, "������������ �������� %d", value);

    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
pString Command::Trace(const uint8 *buffer) const
{
    /// \todo ����� �������� ��� - ��� ����������� ������ �������� SIZE ��������� ������, ���� �� ������ � ������� Command::Trace()
    static const int SIZE = 28;
    static char result[SIZE];
  
    snprintf(result, SIZE - 1, "%s %d ", Name(), buffer[1] + 1);
   
    switch(value)
    {
        case RequestData:
            break;
        case EnableChannel:
            strcat(result, buffer[2] ? "true" : "false");
            break;
        case SetFormWave:
            {
                Form form((Form::E)buffer[2]);
                strcat(result, form.Name(Language::RU));
            }
            break;
        case SetFrequency:
            strcat(result, Buffer2FloatString(buffer + 2));
            break;
        case SetAmplitude:
            strcat(result, Buffer2FloatString(buffer + 2));
            break;
        case SetOffset:
            strcat(result, Buffer2FloatString(buffer + 2));
            break;
        case SetDuration:
            break;
        case SetDutyRatio:
            break;
        case SetPhase:
            strcat(result, Buffer2FloatString(buffer + 2));
            break;
        case RunReset:
            break;
        case ModeDebug:
            break;
        case SetDelay:
            break;
        case WriteRegister:
            break;
        case SetDurationFall:
            break;
        case SetDurationRise:
            break;
        case SetDurationStady:
            break;
        case SetDutyFactor:
            break;
        case SetManipulation:
            strcat(result, buffer[2] == 0 ? "false" : "true");
            break;
        case SetManipulationDuration:
            strcat(result, Buffer2FloatString(buffer + 2));
            break;
        case SetManipulationPeriod:
            strcat(result, Buffer2FloatString(buffer + 2));
            break;
        case SetPacketPeriod:
            strcat(result, Buffer2FloatString(buffer + 2));
            break;
        case SetPacketNumber:
            break;
        case SetStartMode:
            break;
        case SetPeriod:
            break;
        case SetPolarity:
            break;
        case SetManipulationMode:
            strcat(result, buffer[2] ? "1" : "0");
            break;
        case LoadFormDDS:
            strcat(result, "�����");
            break;
        case FreqMeasure:
            break;
        case Log:
            break;
        case FDrive_NumDirsAndFiles:
            break;
        case FDrive_Mount:
            break;
        case FDrive_RequestDir:
            break;
        case FDrive_RequestFile:
            break;
        case Test:
            break;
        case Number:
            break;
    }

    return result;
}
