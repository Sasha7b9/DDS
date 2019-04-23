#pragma once
#include "Message.h"


struct StructCommand
{
    char *symbols;
    bool (*func)(uint8 *);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace SCPI
{
    class Handler
    {
    public:
        static bool Processing(SimpleMessage *msg);
    };

    /// ���������� �������. ���� ������� ���������, ����������� ����� ���������� ������� ������� (��� ������ ���������� ������ 0x0d)
    uint8 *ProcessingCommand(const StructCommand *commands, uint8 *data);

    bool ProcessIDN(uint8 *data);
};
