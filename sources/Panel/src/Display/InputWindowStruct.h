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
void IWS_Fill(InputWindowStruct *iws, Channel ch, WaveForm form, WaveParameter param);
void IWS_DrawInputField(int x, int y);
void IWS_KeyLeft();
void IWS_KeyRight();
void IWS_RegLeft();
void IWS_RegRight();
void IWS_PressKey(Control key);
char *IWS_StringValue(InputWindowStruct *iws);
float IWS_Value(InputWindowStruct *iws);
void IWS_SaveValue();
/// ��������� ��������� allowParameters ���������� � ������������ � ����������� ��� ������ ����� ������� � ������
void IWS_FillAllowParameters(Channel ch, WaveForm form, AllowableParameters *allowParameters);

const char *NameOrder(Order order);
const char *NameUnit(char buffer[10], Order order, WaveParameter parameter);

