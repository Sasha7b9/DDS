#pragma once
#include "defines.h"
#include "Hardware/Controls.h"
#include "Menu/MenuItems.h"
#include "Settings/SettingsTypes.h"


#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4514)
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_DIGITS          5


struct Order
{
    enum
    {
        Nano,       // ����
        Micro,      // �����
        Milli,      // �����
        One,        // �������
        Kilo,       // ����
        Mega,       // ����
        Number
    };
    uint8 value;
    Order(uint8 v) : value(v) {};
    operator uint8() const { return value; };
};

struct SignValue
{
    enum
    {
        None,
        Minus,
        Plus
    };
    uint8 value;
    SignValue(uint8 v) : value(v) {};
    operator uint8() const { return value; };
};

class InputWindowStruct
{
public:

    void Fill(Chan ch, WaveForm form, WaveParameter param);

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
    static void FillAllowParameters(Chan ch, WaveForm form, AllowableParameters *allowParameters);

	char          inputBuffer[NUM_DIGITS + 1];
    char          prevBuffer[NUM_DIGITS + 1];
    int8          posComma;                   ///< ����� ������ ���������� �������� �������
    int8          prevPosComma;
	int8          hightLightDigit;            ///< ������� ������������� ����������
	uint8         order                 : 3;
    uint8         param                 : 4;  ///< ������������ ���� WaveParameter
    uint8         sign                  : 2;  ///< ������������ ���� SignValue
    uint          allow                 : 1;  ///< ���� 1, �������� �������� ��� ������� �������
    uint          numLockMode           : 1;  ///< 1, ����� ���������� ��������� (0...9) ���� ��������
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *NameOrder(Order order);
const char *NameUnit(char buffer[10], Order order, WaveParameter parameter);


#ifdef WIN32
#pragma warning(pop)
#endif
