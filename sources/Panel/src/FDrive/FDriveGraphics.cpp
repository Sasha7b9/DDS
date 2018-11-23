#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "structs.h"
#include "FDrivePanel.h"
#include "Display/Console.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Hardware/CPU.h"
#include "Utils/Debug.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RECS_ON_PAGE    10

/// ����� ������� ����������� ��������. ����� ����� ���� �������� RECS_ON_PAGE ����������
//static int firstDir = 0;
/// ����� ������������� ��������
//static int curDir = 0;
/// ����� ������� ����������� �����. ����� ����� ���� �������� RECS_ON_PAGE ������
//static int firstFile = 0;
/// ����� ������������� �����
static uint curItem = 0;

static uint numItems = 0;
/// ���� � �������� ��������
static char directory[255] = "\\";
/// ����� �������� ����� ��������� ��� ������
static const int NUM_ITEMS = 20;
static char names[NUM_ITEMS][50];



FDrive::View FDrive::view = FDrive::Files;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������� �������� �������� �������� � ����������� [left, top]
//static void DrawNameCurrentDir(int left, int top);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FDrive::Init()
{
    std::strcpy(directory, "\\");
    numItems = 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
static void DrawNameCurrentDir(int left, int top)
{
    Text::DrawText(left, top, directory, Color::FILL);
}
*/

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FDrive::DrawDirs()
{
    int x = Wave::Graphics::X() + 5;
    int y = Wave::Graphics::Y(Chan::A) + 15;
    int delta = 10;

    for(uint i = 0; i < numItems; i++)
    {
        Text::DrawText(x, y, names[i], Color::FILL);
        y += delta;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FDrive::DrawFiles()
{
    int x = Wave::Graphics::X() + 5;
    int y = Wave::Graphics::Y(Chan::A) + 15;
    int delta = 10;

    for(uint i = 0; i < numItems; i++)
    {
        if(names[i])
        {
            names[i][11] = '\0';
            bool selected = (i == curItem);                     // ������� ����, ��� ������ ���� �������� ������������
            if(selected)
            {
                Painter::FillRegion(x - 1, y, 100, 9, Color::FILL);
            }
            Text::DrawText(x, y, names[i], (selected) ? Color::BACK : Color::FILL);
        }
        y += delta;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FDrive::PressUp()
{
    if(curItem > 0)
    {
        curItem--;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FDrive::PressDown()
{
    if(curItem < numItems - 1)
    {
        curItem++;
    }
}
