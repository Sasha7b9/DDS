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
        static String *GetWord();
        static void RemoveWord(String *string);
        static List<String> words;
    private:
        static void ParseStar();
        static void ParseColon();
        /// ������ ������, ��� first - ������ ������� �������, � last - ������ ���������� ������� � ���������� ��������� �� ��
        static String *CreateString(uint first, uint last);
    };
}
