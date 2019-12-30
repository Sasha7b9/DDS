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

    void AppendNewData(const char *buffer, uint length);

    void Update();
    /// ���������� true, ���� ��������� ��������� �� ����������� ������������������
    bool IsLineEnding(const char **bufer);
    /// ������� �����
    void SendAnswer(const char *message);
    /// ���� ������ buffer ���������� � ������������������ �������� word, �� ���������� ��������� �� ������, ��������� �� ��������� �������� ������������������ word.
    /// ����� ���������� nullptr.
    const char *BeginWith(const char *buffer, const char *word);
    /// ������� ��������� �� ��������� ��������, ���� ������� �������
    void SendBadSymbols();

    void ProcessHint(String *message, const char *const names[]); //-V2504

    void ProcessRequestParameterValue(const ParameterValue *param);

    const char *ProcessParameterValue(const char *buffer, ParameterValue::E value);

    const char *ProcessParameterChoice(const char *buffer, ParameterChoice::E choice, const char *const* names);

    namespace Handler
    {
        bool Processing(SimpleMessage *message);
    }
};
