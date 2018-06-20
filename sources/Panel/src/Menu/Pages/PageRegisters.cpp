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
    Int8_Int8,      ///< ��� ������������ ����� � ���������� ����.
    Int14_Int14,    ///< ��� �����, �������� 2^14, � ���������� ����
};

extern PageBase pRegisters;
Page *PageRegisters::pointer = (Page *)&pRegisters;
Name_Register currentRegister = FreqMeterLevel;
bool showInputWindow = false;
extern const ButtonBase bBackspace;
extern const ButtonBase bCancel;
extern const ButtonBase bSave;

#define MAX_SIZE_BUFFER 12
/// ����� �������� �������� �������
static char buffer[MAX_SIZE_BUFFER + 1];
/// ��� ��������� �� ������ �������� ������
static int pos = 0;
/// true, ��������, ��� �������� � ���� ������� ��� ����������
static bool sending[NumRegisters] = {false, false, false, false, false, false};
/// ����� ��������� �������� ��� ������� ��������
static uint values[NumRegisters];

struct DescInput
{
    int size;
    TypeInput type;
};

static DescInput desc[NumRegisters] =
{
    {10, Uint32      }, // Multiplexor1,
    {10, Uint32      }, // Multiplexor2,
    {10, Uint32      }, // OffsetA,
    {10, Uint32      }, // OffsetB,
    {10, Uint32      }, // FreqMeterLevel,
    {10, Uint32      }, // FreqMeterHYS,
    {7,  Binary      }, // FPGA_RG0_Control,
    {10, Uint32      }, // FPGA_RG1_Freq,
    {7,  Int8_Int8   }, // FPGA_RG2_Mul,
    {11, Int14_Int14 }, // FPGA_RG3_RectA,
    {11, Int14_Int14 }, // FPGA_RG4_RectB,
    {10, Uint32      }, // FPGA_RG5_PeriodImpulseA,
    {10, Uint32      }, // FPGA_RG6_DurationImpulseA,
    {10, Uint32      }, // FPGA_RG7_PeriodImpulseB,
    {10, Uint32      }, // FPGA_RG8_DurationImpulseB,
    {12, Binary      }  // FPGA_RG9_FreqMeter
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���������� ������ ������ ��� �������� i
static int SizeBuffer(Name_Register name);
/// ���������� ��� ����� ��� �������� i
static TypeInput TypeBuffer(Name_Register name);
/// ��������� true, ���� ������ �������� ���������� ��� ������� ���� �����
static bool AllowableSymbol(Control key);
/// ������� �������� �������� i
static void DrawValue(int x, int y, uint8 i);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int SizeBuffer(Name_Register name)
{
    return desc[name].size;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static TypeInput TypeBuffer(Name_Register name)
{
    return desc[name].type;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool AllowableSymbol(Control key)
{
    TypeInput type = TypeBuffer(currentRegister);

    if(pos == SizeBuffer(currentRegister))
    {
        return false;
    }

    if(type == Uint32)
    {
        return KeyIsDigit(key);
    }
    else if(type == Binary)
    {
        return key == B_0 || key == B_1;
    }
    else if(type == Int8_Int8)
    {

    }
    else if(type == Int14_Int14)
    {
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

    if(TypeBuffer(name) == Uint32)
    {
        Text::DrawFormatText(x, y, UInt2String(values[i]));
    }
    else if(TypeBuffer(name) == Binary)
    {
        char buf[33];

        Text::DrawFormatText(x, y, Bin2StringN(values[i], buf, SizeBuffer(name)));
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
    Register reg(currentRegister);
    Text::DrawBigText(X_INPUT + 3, Y_INPUT + 2, 2, reg.Name());

    int x = X_INPUT + 5;

    for(int i = 0; i < pos; i++)
    {
        x = Text::DrawBigChar(x, Y_INPUT + 20, 4, buffer[i]) + 3;
    }

    Painter::DrawFilledRectangle(x - 1, Y_INPUT + 20, 20, 29, Color::GRAY_10, Color::BLUE);
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

    pRegisters.items[0] = (Item *)&bBackspace;
    pRegisters.items[1] = (Item *)&bCancel;
    pRegisters.items[2] = (Item *)&bSave;

    if(sending[currentRegister])
    {
        UInt2String(values[currentRegister], buffer);
        pos = (int)strlen(buffer);
    }
    else
    {
        pos = 0;

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
    if(pos > 0)
    {
        pos--;
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

void LoadRegister()
{
    buffer[pos] = '\0';

    uint value = 0;

    TypeInput type = TypeBuffer(currentRegister);

    if (type == Uint32)
    {
        if (String2UInt(buffer, &value))
        {
            Generator::LoadRegister(currentRegister, value);
            values[currentRegister] = value;
            sending[currentRegister] = true;
        }
    }
    else if(type == Binary)
    {
        values[currentRegister] = StringToBin32(buffer);
        sending[currentRegister] = true;
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

    if(!showInputWindow && AllowableSymbol(key))
    {
        sending[currentRegister] = false;
        OnPress_Send();
        buffer[0] = KeyToChar(key);
        pos = 1;
    }
    else if(showInputWindow && strCntrl.typePress == Down && AllowableSymbol(key))
    {
        if(pos < SizeBuffer(currentRegister))
        {
            buffer[pos++] = KeyToChar(key);
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
