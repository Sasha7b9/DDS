#pragma once
#include "Message.h"



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
        /// ���������� ���� � ������� i
        static uint8 GetByte(uint i);

        static uint Size() { return static_cast<uint>(used); };
        /// ������� ����������� ������� �� ������ ������
        static void RemoveBadSymbols();

        static void MarkFirstSymbolAsBad() { data[0] = '\0'; };

    private:
        static void AddByte(uint8 byte);
        /// �������� ���������� ������ �� ���� ���� �����. ����� ������ ���� ��� ���� ��������
        static bool ShiftToLeft();

        static const int SIZE_BUFFER = 1024;
        static uint8 data[SIZE_BUFFER]; ///< ����� �������� ������ ��������
        static int   used;              ///< ���������� ������� � ��������� ���� - ������ �������������� ���� ����� ������ 0, ��������� = used - 1
        static int   start;             ///< ������ ������� ����� ��������������� ����. ���� ������ ���� ������� ������ ����� ������ 0, �� 
    };
};
