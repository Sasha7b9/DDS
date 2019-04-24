#pragma once


namespace SCPI
{
    namespace Runner
    {
        /// ��������� ������� �� SCPI::Parser::words
        bool Execute();

        struct Result
        {
            enum E
            {
                IsOk,               ///< �������� ���������� �������
                InvalidSyntax,      ///< ������������ ��������� �������
                UnknownCommand,     ///< ����������� ��������
                Count
            };
        };

        struct StructCommand
        {
            char      *symbols;
            Result::E(*func)();
        };

        void ProcessError(Result::E error);

        namespace Process
        {
            Result::E IDN();
            Result::E RST();
            Result::E Channel();
            Result::E Frequency();
            Result::E Form();
            Result::E Amplitude();
        }
    }
}
