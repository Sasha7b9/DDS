#pragma once
#include "defines.h"
#include "Keyboard/Controls.h"
#include "Settings/SettingsTypes.h"


#define MAX_CHOICE_VARIANTS 10  ///< ������������ ���������� ��������� ��� Choice

/// ��������� ���������� ������������ ��������� ��� ����������� ����� �������
struct AllowableParameters
{
    bool allow[NumParameters];
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    Item_None,
    Item_Choice,
    Item_Button,
    Item_Page,
    Item_SButton,
    Item_ChoiceParameter,
    Item_SB_Page
} Item;

#define COMMON_PART_ITEM            \
        Item       typeItem;        \
        uint8      notUsed0[3];     \
        pFuncVV    funcOnPress;     \
        const char *title[2];


/// ������������� �������� ������
struct Choice
{
    COMMON_PART_ITEM
    const char *names[MAX_CHOICE_VARIANTS * 2];
    uint8      *cell;
};

/// ������� ��� ������ ��������� �������
struct ChoiceParameter
{
    COMMON_PART_ITEM
    AllowableParameters     allowParameters;
    uint8                   *numParameter;
};

/// ������
typedef struct
{
    COMMON_PART_ITEM
} Button;

/// ������ � ������ �������������� ��������
struct SButton
{
    COMMON_PART_ITEM
    uint8       *cell;
    pFuncVII    funcDraw;
};

typedef struct
{
    COMMON_PART_ITEM
    void *items[NUM_ITEMS_ON_PAGE]; ///< ��������� �� �����, ������������ �� ��������
} Page;


const char* ItemTitle(void* item);

void* ItemFromPage(int numItem);

const char* Choice_CurrentName(Choice* choice);

char* ChoiceWaveParameter_CurrentName(ChoiceParameter *choice);

const char* Choice_Name(Choice* choice, int num);

const char* Page_Name(const Page* page);

bool ItemIsChoice(void* item);

bool ItemIsChoiceParameter(void *item);

bool ItemIsButton(void* item);

bool ItemIsSButton(void* item);

int Choice_NumChoices(Choice *choice);

Item TypeItem(void* address);
/// ���������� ���������� ����� ������ ���� �� ��������
int PositionOnPage(void *item);
/// ���������� �������������� �������, ����������� ������ ����
Control ButtonForItem(void *item);

int Choice_CurrentChoice(Choice *choice);
/// ���������� ����� ������� ��������
Page* CurrentPage();

char* NameParameter(WaveParameter parameter);

char* NameWaveForm(WaveForm form);

