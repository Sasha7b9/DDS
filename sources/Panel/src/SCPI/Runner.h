#pragma once


namespace SCPI
{
    namespace Runner
    {
        /// ��������� ������� �� SCPI::Parser::words
        bool Execute();

        namespace Process
        {
            void IDN();
            void RST();
            void Channel();
            void Frequency();
            void Form();
            void Amplitude();
        }
    }
}
