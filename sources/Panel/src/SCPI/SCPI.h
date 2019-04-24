#pragma once
#include "Message.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace SCPI
{
    struct Result
    {
        enum E
        {
            Done,               ///< ������� ���������
            IncompleteCommand,  ///< ������� �� ������� ���������
            InvalidParameter,   ///< ������������ ��������
            Count
        };
    };

    struct StructCommand
    {
        char       *symbols;
        Result::E (*func)();
    };

    void Init();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Handler
    {
    public:
        static bool Processing(SimpleMessage *msg);
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct Buffer
    {
        /// ������� ������ - ���������� � ������
        static void Clear();
        /// ��������� ������ �� ��������� � �����
        static void AddData(SimpleMessage *msg);
        /// ��������� �������, ���� ��� ���� � ������, � ������� �������������� � �������� ������
        static bool RunAndCompress();
    private:
        static void AddByte(uint8 byte);
        /// ������������ ������ ������� commands. ���������� true, ���� ���� �� �������� ���������� - ������� ���������, ���� ��������� ��������
        static bool ProcessStructs(const StructCommand *commands);

        static const int SIZE_BUFFER = 1024;
        static uint8 data[SIZE_BUFFER];
        static int   used;
    };

    extern Buffer buffer;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    namespace Process
    {
        Result::E IDN();
        Result::E RST();
        Result::E Channel();
        Result::E Frequency();
        Result::E Form();
        Result::E Amplitude();
    }
};
