#pragma once
#include "CommonTypes.h"
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

typedef const char *(*FuncSCPI)(const char *);
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

    void ProcessRequestParameterValue(ParameterValue *param);

    namespace Handler
    {
        bool Processing(SimpleMessage *message);
    }
};
