#pragma once
#include "Utils/String.h"


struct Word
{
    char   *address;
    int8    numSymbols;
    uint8   notUsed0;
    uint8   notUsed1;
    uint8   notUsed2;
};

/// \brief ��������� ����� � ��������� ������ � ��������� ���. numDigits - ����� �������� ���������
/// \attention ������ ����� ��������� �� ���������� ������ �������. ���� ��������� ����� ������� ���������� �������, �� ��� ����� ������������ ����.
/// \retval ��������� �� ������ � ������.
char *Float2String(float value, bool alwaysSign, int numDigits, char bufferOut[20]);

float Buffer2Float(const uint8 *buffer);

String Int2String(int value, bool alwaysSign, int numMinFields);

char* UInt64_2String(uint64 value, char bufferOut[20] = 0);

char* UInt2String(uint value,                     ///< ��������
                 char bufferOut[20] = 0         ///< ���� ������������ ������������ ��������
);
/// ��������� ���������� ����� � ���������� ������ ������ allDigits. ����� ����� ������� �� forFract �������� �� �����
char* UInt2StringThisPoint(uint value, char bufferOut[20], int allDigits, int forFract);
/// ����������� �������� ����� ,�������������� ������� �� ����� � ������, � uint
uint StringToBin32(char buffer[33]);


struct SU
{
    static char *Buffer2FloatString(const uint8 *buffer);
    /// ���������� ����� ���� � ������ string
    static int NumWords(const char *string);
    /// ���������� ��������� �� n ����� � ������. ���� char == 0 - ����� ���, ���� ret value == 0xffffffff - �������� ����� ������� ���
    static char *GetWord(char *string, int n, char *out, int size);
    /// ��������� ����� �������� � ����� ���� int.
    static int NumDigitsInNumber(int value);
    /// ��� ������� ����� ����������� � �������� �������� �����.
    static bool GetWord(const char *string, Word *word, const int numWord);

    static bool WordEqualZeroString(Word *word, char* string);

    static int FindSymbol(const char *string, char symbol);

    static char ToUpper(char symbol);

    static char *ToUpper(void *_str, uint size);

    static void ConcatenateSymbol(char *str, char symbol);

    static char *ToUpper(char *str);

    static char ToLower(char symbol);
private:
    /// ���������� false, ���� ����� ���������� - ������ ���������.
    static bool ChooseSymbols(const char **string);
    /// ���������� false, ���� ����� ���������� - ������ ���������.
    static bool ChooseSpaces(const char **string);
};

bool String2UInt64(const char *str, uint64 *value);

bool String2UInt(const char *str, uint *value);
/// ��������� ������ � �������� ��� � �������� ����������� ��������
char *Bin2StringN(uint value, char buffer[33], int n);
