#include "PageRegisters.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Generator.h"
#include "Display/Symbols.h"
#include "Wave.h"
#include "Menu/Menu.h"
#include "Command.h"
#include "Utils/Math.h"
#include "Utils/StringUtils.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define X_INPUT      5
#define Y_INPUT      183
#define WIDTH_INPUT  240
#define HEIGHT_INPUT 52

/// ��� �������� ����� � ���� �����
enum TypeInput
{
    Uint32,         ///< ���������� �����. ����� ������ �������� �� 2^32.
    Binary,         ///< ������������������ ����� � ������
    Uint8_Uint8,      ///< ��� ������������ ����� � ���������� ����.
    Uint14_Uint14,    ///< ��� �����, �������� 2^14, � ���������� ����
};

extern PageBase pRegisters;
Page *PageRegisters::pointer = (Page *)&pRegisters;
/// �������, � ������� ����� ������������ ��������� �������� �� ������� ������ �������
Name_Register currentRegister = FreqMeterLevel;
/// ���� ������ ���� �����
static bool showInputWindow = false;
extern const ButtonBase bBackspace;
extern const ButtonBase bCancel;
extern const ButtonBase bSave;

#define MAX_SIZE_BUFFER 12
/// ����� �������� �������� �������
static char buffer[MAX_SIZE_BUFFER + 1];
/// ��� ��������� �� �������� ���������� - ���� ������ ����� �������� ������
static int position = 0;
/// true, ��������, ��� �������� � ���� ������� ��� ����������
static bool sending[NumRegisters] = {false};
/// ����� ��������� �������� ��� ������� ��������
static uint values[NumRegisters] = {0};

struct DescInput
{
    int size;
    TypeInput type;
};

static DescInput desc[NumRegisters] =
{
    {2,  Uint32         }, // Multiplexor1,
    {2,  Uint32         }, // Multiplexor2,
    {10, Uint32         }, // OffsetA,
    {10, Uint32         }, // OffsetB,
    {10, Uint32         }, // FreqMeterLevel,
    {10, Uint32         }, // FreqMeterHYS,
    {7,  Binary         }, // FPGA_RG0_Control,
    {10, Uint32         }, // FPGA_RG1_Freq,
    {7,  Uint8_Uint8    }, // FPGA_RG2_Mul,
    {11, Uint14_Uint14  }, // FPGA_RG3_RectA,
    {11, Uint14_Uint14  }, // FPGA_RG4_RectB,
    {10, Uint32         }, // FPGA_RG5_PeriodImpulseA,
    {10, Uint32         }, // FPGA_RG6_DurationImpulseA,
    {10, Uint32         }, // FPGA_RG7_PeriodImpulseB,
    {10, Uint32         }, // FPGA_RG8_DurationImpulseB,
    {12, Binary         }, // FPGA_RG9_FreqMeter
    {2,  Uint32         }  // Multiplexor3
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���������� ������ ������ ��� �������� i
static int SizeBuffer(Name_Register name = NumRegisters);
/// ���������� ��� ����� ��� �������� i
static TypeInput TypeBuffer(Name_Register name = NumRegisters);
/// ��������� true, ���� ������ �������� ���������� ��� ������� ���� �����
static bool AllowableSymbol(Control key);
/// ������� �������� �������� i
static void DrawValue(int x, int y, uint8 i);
/// ���������� �� ������ ��������, �������������� �����
static uint FirstValue();
/// ���������� �� ������ ��������, ��������� �� ������
static uint SecondValue();


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int SizeBuffer(Name_Register name)
{
    name = (name == NumRegisters) ? currentRegister : name;

    return desc[name].size;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static TypeInput TypeBuffer(Name_Register name)
{
    name = (name == NumRegisters) ? currentRegister : name;

    return desc[name].type;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool AllowableSymbol(Control key)
{
    TypeInput type = TypeBuffer(currentRegister);

    if(type == Uint32)
    {
        return KeyIsDigit(key);
    }
    else if(type == Binary)
    {
        return key == B_0 || key == B_1;
    }
    else if(type == Uint8_Uint8 || type == Uint14_Uint14)
    {
        if(KeyIsDigit(key))
        {
            return true;
        }

        if (key == B_Dot)
        {
            for (int i = 0; i < sizeof(buffer); i++)
            {
                if (buffer[i] == '.')
                {
                    return false;
                }
            }
            return true;
        }
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageRegisters::Draw()
{
    if(Menu::CurrentPage() != pointer)
    {
        return;
    }

    Painter::FillRegion(Wave::X(), Wave::Y(A) + 1, Wave::Width() - 1, Wave::Height() * 2, Color::BACK);

    DrawRegisters(Wave::X() + 4, Wave::Y(A) + 3);

    DrawInputWindow();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageRegisters::DrawRegisters(int x, int y)
{
    for(uint8 i = 0; i < NumRegisters; i++)
    {
        Register reg(i);
        Color color = Color::FILL;
        if(i == currentRegister)
        {
            Painter::FillRegion(x - 1, y + i * 10, 132, 8, Color::FILL);
            color = Color::BACK;
        }
        Text::DrawText(x, y + i * 10, reg.Name(), color);
        DrawValue(x + 135, y + i * 10, i);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawValue(int x, int y, uint8 i)
{
    if(!sending[i])
    {
        return;
    }

    Painter::SetColor(Color::FILL);

    Name_Register name = (Name_Register)i;

    TypeInput type = TypeBuffer(name);

    if(type == Uint32)
    {
        Text::DrawFormatText(x, y, UInt2String(values[i]));
    }
    else if(type == Binary)
    {
        char buf[33];

        Text::DrawFormatText(x, y, Bin2StringN(values[i], buf, SizeBuffer(name)));
    }
    else if(type == Uint8_Uint8 || type == Uint14_Uint14)
    {
        uint mask = type == Uint8_Uint8 ? 0xffU : 0x3fffU;
        int numBits = type == Uint8_Uint8 ? 8 : 14;

        uint first = values[i] & mask;
        uint second = (values[i] >> numBits) & mask;
        x = Text::DrawFormatText(x, y, UInt2String(first));
        x = Text::DrawFormatText(x, y, ".");
        Text::DrawFormatText(x, y, UInt2String(second));
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PageRegisters::DrawInputWindow()
{
    if(!showInputWindow)
    {
        return;
    }

    Painter::DrawRectangle(X_INPUT, Y_INPUT, WIDTH_INPUT, HEIGHT_INPUT, Color::FILL);
    Painter::FillRegion(X_INPUT + 1, Y_INPUT + 1, WIDTH_INPUT - 2, HEIGHT_INPUT - 2, Color::BACK);
    Register reg(currentRegister);
    Text::DrawBigText(X_INPUT + 3, Y_INPUT + 2, 2, reg.Name(), Color::FILL);

    int x = X_INPUT + 5;

    for(uint i = 0; i < strlen(buffer); i++)
    {
        if(i == (uint)position)
        {
            Painter::DrawFilledRectangle(x - 2, Y_INPUT + 19, 19, 31, Color::GRAY_10, Color::BLUE);
            Painter::SetColor(Color::FILL);
        }
        x = Text::DrawBigChar(x, Y_INPUT + 20, 4, buffer[i]) + 3;
    }
    if (position == (int)strlen(buffer) && position < SizeBuffer())
    {
        Painter::DrawFilledRectangle(x - 2, Y_INPUT + 19, 19, 31, Color::GRAY_10, Color::BLUE);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void OnPress_Prev()
{
    CircleDecrease<uint8>((uint8 *)&currentRegister, 0, NumRegisters - 1);
}

DEF_BUTTON( bPrev,                                                                                                     //--- �������� - ���������� ---
    "����������", "Previous",
    "������� � ����������� ��������",
    "Go to the previous register",
    pRegisters, FuncActive, OnPress_Prev, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Next()
{
    CircleIncrease<uint8>((uint8 *)&currentRegister, 0, NumRegisters - 1);
}

DEF_BUTTON(bNext,                                                                                                       //--- �������� - ��������� ---
    "���������", "Next",
    "������� � ���������� ��������",
    "Go to the next register",
    pRegisters, FuncActive, OnPress_Next, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Send()
{
    showInputWindow = true;
    memset(buffer, 0, MAX_SIZE_BUFFER);

    pRegisters.items[0] = (Item *)&bBackspace;
    pRegisters.items[1] = (Item *)&bCancel;
    pRegisters.items[2] = (Item *)&bSave;

    if(sending[currentRegister])
    {
        TypeInput type = TypeBuffer();

        if (type == Uint32)
        {
            UInt2String(values[currentRegister], buffer);
            position = (int)strlen(buffer);
        }
        else if(type == Binary)
        {
            Bin2StringN(values[currentRegister], buffer, SizeBuffer(currentRegister));
            position = (int)strlen(buffer);
        }
        else if(type == Uint8_Uint8 || type == Uint14_Uint14)
        {
            uint mask = type == Uint8_Uint8 ? 0xffU : 0x3fffU;
            int numBits = type == Uint8_Uint8 ? 8 : 14;

            uint first = values[currentRegister] & mask;
            uint second = (values[currentRegister] >> numBits) & mask;
            
            strcpy(buffer, UInt2String(first));
            strcat(buffer, ".");
            strcat(buffer, UInt2String(second));
        }
    }
    else
    {
        position = 0;
        memset(buffer, 0, MAX_SIZE_BUFFER);
        values[position] = 0;
    }
}

DEF_BUTTON(bSend,                                                                                                         //--- �������� - ������� ---
    "�������", "Send",
    "��������� ���� ����� �������� ��������",
    "Opens the register value entry window",
    pRegisters, FuncActive, OnPress_Send, FuncDraw
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Backspace()
{
    if(position > 0)
    {
        position--;
        for(int i = position; i < MAX_SIZE_BUFFER; i++)
        {
            buffer[i] = 0;
        }
    }
}

static void OnDraw_Backspace(int x, int y)
{
    Text::SetFont(TypeFont_UGO2);
    Text::Draw4SymbolsInRect(x + 15, y + 30, SYMBOL_LEFT, Color::FILL);
    Text::SetFont(TypeFont_8);
}

DEF_BUTTON(bBackspace,                                                                                   //--- �������� - Input window - Backspace ---
    "Backspace", "Backspace",
    "������� ��������� �������� ������",
    "Deletes the last character you typed",
    pRegisters, FuncActive, OnPress_Backspace, OnDraw_Backspace
)

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Cancel()
{
    showInputWindow = false;
    memset(buffer, 0, MAX_SIZE_BUFFER);
    pRegisters.items[0] = (Item *)&bPrev;
    pRegisters.items[1] = (Item *)&bNext;
    pRegisters.items[2] = (Item *)&bSend;
}

static void OnDraw_Cancel(int x, int y)
{
    Text::SetFont(TypeFont_UGO2);
    Text::Draw4SymbolsInRect(x + 15, y + 30, SYMBOL_DELETE, Color::FILL);
    Text::SetFont(TypeFont_8);
}

DEF_BUTTON(bCancel,                                                                                         //--- �������� - Input window - ������ ---
    "������", "Cancel",
    "�������� ������� �������� � ������� � ��������� ���� �����",
    "Cancels the sending of values into the register and closes the input window",
    pRegisters, FuncActive, OnPress_Cancel, OnDraw_Cancel
)

uint FirstValue()
{
    char buff[20];

    for(uint i = 0; i < sizeof(buffer); i++)
    {
        if(buffer[i] == '.')
        {
            for(uint j = 0; j < i; j++)
            {
                buff[j] = buffer[j];
            }
            buff[i] = 0;

            uint result = 0;

            if(String2UInt(buff, &result))
            {
                return result;
            }
            break;
        }
    }

    return 0;
}

uint SecondValue()
{
    for(uint i = 0; i < sizeof(buffer); i++)
    {
        if(buffer[i] == '.')
        {
            uint result = 0;

            if(String2UInt(&buffer[i + 1], &result))
            {
                return result;
            }
            break;
        }
    }

    return 0;
}

void LoadRegister()
{
    uint value = 0;

    TypeInput type = TypeBuffer(currentRegister);

    if (type == Uint32)
    {
        if (String2UInt(buffer, &value))
        {
            values[currentRegister] = value;
            sending[currentRegister] = true;
            Generator::LoadRegister(currentRegister, value);
        }
    }
    else if(type == Binary)
    {
        values[currentRegister] = StringToBin32(buffer);
        sending[currentRegister] = true;
        Generator::LoadRegister(currentRegister, values[currentRegister]);
    }
    else if(type == Uint8_Uint8 || type == Uint14_Uint14)
    {
        int numBits = type == Uint8_Uint8 ? 8 : 14;

        uint first = FirstValue();
        uint second = SecondValue();

        values[currentRegister] = first + (second << numBits);
        sending[currentRegister] = true;
        Generator::LoadRegister(currentRegister, values[currentRegister]);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Save()
{
    LoadRegister();
    OnPress_Cancel();
}

static void OnDraw_Save(int x, int y)
{
    Text::SetFont(TypeFont_UGO2);
    Text::Draw4SymbolsInRect(x + 15, y + 30, SYMBOL_SAVE, Color::FILL);
    Text::SetFont(TypeFont_8);
}

DEF_BUTTON(bSave,                                                                                          //--- �������� - ���� ����� --- ������� ---
    "�������", "Send",
    "���������� �������� � ��������� �������",
    "Writes a value to the selected register",
    pRegisters, FuncActive, OnPress_Save, OnDraw_Save
)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool OnKey(StructControl strCntrl)
{
    Control key = strCntrl.key;

    if(!showInputWindow)
    {
        if (AllowableSymbol(key))
        {
            sending[currentRegister] = false;
            OnPress_Send();
            memset(buffer, 0, MAX_SIZE_BUFFER);
            buffer[0] = KeyToChar(key);
            position = 1;
            return true;
        }
    }
    else if(strCntrl.typePress == Down)
    {
        if (AllowableSymbol(key))
        {
            if (position < SizeBuffer(currentRegister))
            {
                buffer[position++] = KeyToChar(key);
            }
            return true;
        }
        else if(key == B_LEFT)
        {
            if(position > 0)
            {
                --position;
            }
            return true;
        }
        else if(key == B_RIGHT)
        {
            if(position < (int)strlen(buffer))
            {
                ++position;
            }
            return true;
        }
        else if(key == B_ESC)
        {
            OnPress_Cancel();
            return true;
        }
    }

    return false;
}

static Item emptyItem = {Item_None};

DEF_PAGE_4_VAR(pRegisters,                                                                                                          //--- �������� ---
    "��������", "REGISTERS",
    "",
    "",
    bPrev,
    bNext,
    bSend,
    emptyItem,
    Page_Registers, 0, FuncActive, FuncPress, OnKey
)
