#pragma once
#include "defines.h"
#include "Keyboard/Controls.h"
#include "Menu/MenuItems.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_DIGITS          5


typedef enum
{
    Nano,       // ����
    Micro,      // �����
    Milli,      // �����
    One,        // �������
    Kilo,       // ����
    Mega,       // ����
    NumOrders
} Order;

Order& operator++(Order& order);
Order& operator--(Order& order);

typedef enum
{
    Sign_None,
    Sign_Minus,
    Sign_Plus
} Sign;

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

    bool            allow;                      ///< ���� true, �������� �������� ��� ������� �������
    Sign            sign;
	char            inputBuffer[NUM_DIGITS + 1];
    char            prevBuffer[NUM_DIGITS + 1];
    int             posComma;                   ///< ����� ������ ���������� �������� �������
    int             prevPosComma;
	int	            hightLightDigit;            ///< ������� ������������� ����������
	Order           order;
    WaveParameter   param;
    bool            numLockMode;                ///< true, ����� ���������� ��������� (0...9) ���� ��������
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *NameOrder(Order order);
const char *NameUnit(char buffer[10], Order order, WaveParameter parameter);

