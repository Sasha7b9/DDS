#pragma once
#include "Hardware/Controls.h"
#include "Command.h"
#include "Menu/MenuItems.h"
#include <string.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// �������� ��� ��������� ������� ������ � ���� ����� ��������� ��������
class StructValue
{
public:

    StructValue(ParameterValue *p = 0) : param(p)  { };

    void Set(ParameterValue *param);

    char *StringValue();

    ParamValue ValueNano();

    void KeyLeft();

    void KeyRight();

    void RegLeft();

    void RegRight();

    void PressKey(Control &key);

    void SaveValue();

    ParameterValue *param;

private:
    /// ����������� �������� � �������� �������. ���������� false, ���� �������� �������� �� ����������.
    bool IncreaseDigit(int num);
    /// ��������� �������� � �������� �������. ���������� false, ���� �������� �������� �� ����������
    bool DecreaseDigit(int num);
    /// ���������� true, ���� ��� ����� ����� �� num ����� ����. � num ����
    bool All0LeftWithThis(int num);
    /// ���������� true, ���� ��� ����� ����� � ��� �������� ���������
    bool All9LeftWithThis(int num);
    /// �������� ��� ������� ������
    void ShiftToRight();
    /// ����� ���� �������� �����
    void ShiftToLeft();
    /// ���������� true, ���� ���� ������ ���� ������� ������ �����
    bool OnlyOneRigthDigit();
    /// ���������� ����� �� �������
    int ValueBeforeComma();
    /// ���������� ����� �� �������, ���������� � ����-��������
    uint64 ValueBeforeCommaInNano();
    /// ���������� ����� ����� �������, ���������� � �������� ����-�����������
    uint64 ValueAfterCommaInNano();
    /// ����������� ������� �� ��������� �� �����������
    void IncreaseOrder();
    /// ������� ������� �������� � ���������
    void SendToGenerator();
    /// ������������ �������� ���������, ���� ���������� offset + amplitude
    void SetParameterIfUnderLimit(ParameterValue &param);
};



/// ���� �������������� ���������� �������� ���������
namespace InputWindow
{
    void Init();

    void DeInit();

    void Draw();

    void OrderUp();

    void OrderDown();

    void KeyEnter();

    void ProcessContorl(Control &control);
};
