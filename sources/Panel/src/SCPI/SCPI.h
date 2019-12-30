#pragma once
#include "CommonTypes.h"
#include "Wave.h"
#include "SCPI/MacrosesSCPI.h"

/*
    ������ �������.
    1. ������� ������ ���������� � ������� ':'.
    2. ���� ����������� ��������� ':'.
    3. ������� ����������� ������ ����� ���������� � ���������� 1 ��.
    4. ������� ������ ������������� �������� � ����� 0x0D.
*/

class ParameterValue;
class String;
class SimpleMessage;

typedef const char *(*FuncSCPI)(pcChar);
typedef bool (*FuncTestSCPI)();
typedef void (*FuncHint)(String *);


/// ���������, �������������� ���� ������.
struct StructSCPI
{
    const char *key;            /// �������� ����� ���� (�������)

    const StructSCPI *strct;    /// ���� ��������� ����� ��� Node, �� ����� �������� ������ �������� - StructSCPI *structs.

    FuncSCPI  func;             /// ���� ��������� ����� ��� Leaf, �� ����� �������� ������� - ���������� ����� ���� FuncSCPI

    const char *hint;

    FuncHint funcHint;

    bool IsEmpty() const { return key[0] == '\0'; };
    bool IsNode() const { return strct != nullptr; };   /// ��������� �������� "�����" ������, ����� ���� ������ �� ������ ����� structs
    bool IsLeaf() const { return func != nullptr; };    /// ��������� �������� "������" ������, ����� ��������� ������� func
};


namespace SCPI
{
    /// ������-��������� ������ �������
    const char SEPARATOR = ':';

    const int SIZE_SEPARATOR = 1;

    void AppendNewData(pcChar buffer, uint length);

    void Update();
    /// ���������� true, ���� ��������� ��������� �� ����������� ������������������
    bool IsLineEnding(pcChar *bufer);
    /// ������� �����
    void SendAnswer(pcChar message);
    /// ���� ������ buffer ���������� � ������������������ �������� word, �� ���������� ��������� �� ������, ��������� �� ��������� �������� ������������������ word.
    /// ����� ���������� nullptr.
    const char *BeginWith(pcChar buffer, pcChar word);
    /// ������� ��������� �� ��������� ��������, ���� ������� �������
    void SendBadSymbols();

    void ProcessHint(String *message, pString names[]); //-V2504

    void ProcessRequestParameterValue(const ParameterValue *param);

    const char *ProcessParameterValue(pcChar buffer, ParameterValue::E value);

    const char *ProcessParameterChoice(pcChar buffer, ParameterChoice::E choice, pString *names);

    namespace Handler
    {
        bool Processing(SimpleMessage *message);
    }
};
