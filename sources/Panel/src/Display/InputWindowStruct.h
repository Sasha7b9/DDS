#pragma once
#include "defines.h"
#include "Hardware/Controls.h"
#include "Menu/MenuItems.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_DIGITS          5


enum Order
{
    Nano,       // ����
    Micro,      // �����
    Milli,      // �����
    One,        // �������
    Kilo,       // ����
    Mega,       // ����
    NumOrders
};

enum SignValue
{
    Sign_None,
    Sign_Minus,
    Sign_Plus
};

class InputWindowStruct
{
public:

    void Fill(Channel ch, WaveForm form, WaveParameter param);

    char *StringValue();

    float Value();

    static void DrawInputField(int x, int y);

    static void KeyLeft();

    static void KeyRight();

    static void RegLeft();

    static void RegRight();

    static void PressKey(Control key);

    static void SaveValue();
    /// ��������� ��������� allowParameters ���������� � ������������ � ����������� ��� ������ ����� ������� � ������
    static void FillAllowParameters(Channel ch, WaveForm form, AllowableParameters *allowParameters);

	char          inputBuffer[NUM_DIGITS + 1];
    char          prevBuffer[NUM_DIGITS + 1];
    int8          posComma;                   ///< ����� ������ ���������� �������� �������
    int8          prevPosComma;
	int8          hightLightDigit;            ///< ������� ������������� ����������
	Order         order                 : 3;
    uint8         param                 : 4;  ///< ������������ ���� WaveParameter
    SignValue     sign                  : 2;  ///< ������������ ���� SignValue
    uint          allow                 : 1;  ///< ���� 1, �������� �������� ��� ������� �������
    uint          numLockMode           : 1;  ///< 1, ����� ���������� ��������� (0...9) ���� ��������
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *NameOrder(Order order);
const char *NameUnit(char buffer[10], Order order, WaveParameter parameter);

