#pragma once
#include "Message.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace SCPI
{
    struct StructCommand
    {
        char  *symbols;
        void (*func)();
    };

    void Init();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Handler
    {
    public:
        static bool Processing(SimpleMessage *msg);
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct Buffer
    {
        /// ������� ������ - ���������� � ������
        static void Clear();
        /// ��������� ������ �� ��������� � �����
        static void AddData(SimpleMessage *msg);
        /// ��������� �������, ���� ��� ���� � ������, � ������� �������������� � �������� ������
        static void RunAndCompress();
    private:
        static void AddByte(uint8 byte);
        static const int SIZE_BUFFER = 1024;
        static uint8 data[SIZE_BUFFER];
        static int   used;
    };

    extern Buffer buffer;

    /// ���������� �������. ���� ������� ���������, ����������� ����� ���������� ������� ������� (��� ������ ���������� ������ 0x0d)
    uint8 *ProcessingCommand(const StructCommand *commands, uint8 *data);

    namespace Process
    {
        void IDN();
        void RST();
        void Channel();
        void Frequency();
        void Form();
        void Amplitude();
    }
};
