#pragma once
#include "defines.h"
#include "Keyboard/Controls.h"
#include "Settings/SettingsTypes.h"


#define MAX_CHOICE_VARIANTS 10  ///< ������������ ���������� ��������� ��� Choice

/// ��������� ���������� ������������ ��������� ��� ����������� ����� �������
typedef struct
{
    bool allow[NumParameters];
} AllowableParameters;


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

#define COMMON_PART_ITEM        \
        Item    typeItem;       \
        pFuncVV funcOnPress;    \
        char    *title[2];


/// ������������� �������� ������
typedef struct
{
    COMMON_PART_ITEM
    char    *names[MAX_CHOICE_VARIANTS * 2];
    uint8   *cell;
} Choice;

/// ������� ��� ������ ��������� �������
typedef struct
{
    COMMON_PART_ITEM
    AllowableParameters     allowParameters;
    uint8                   *numParameter;
} ChoiceParameter;

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


char* ItemTitle(void* item);

void* ItemFromPage(int numItem);

char* Choice_CurrentName(Choice* choice);

char* ChoiceWaveParameter_CurrentName(ChoiceParameter *choice);

char* Choice_Name(Choice* choice, int num);

char* Page_Name(const Page* page);

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

