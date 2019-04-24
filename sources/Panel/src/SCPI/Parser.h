#pragma once
#include "Utils/String.h"
#include "Utils/List.h"


namespace SCPI
{
    class Parser
    {
    public:
        /// ������� ��������� ������ ������� �� SCPI::Buffer �� ������������. ����� ������ � words �������� ������������
        static void Parse();
        static void ClearList();
        static List<String> words;
    private:
        static void ParseStar();
        static void ParseColon();
    };
}
