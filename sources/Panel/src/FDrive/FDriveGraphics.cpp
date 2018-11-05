#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "FDrivePanel.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Wave.h"
#include "Hardware/CPU.h"
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RECS_ON_PAGE    10

/// ����� ������� ����������� ��������. ����� ����� ���� �������� RECS_ON_PAGE ����������
static int firstDir = 0;
/// ����� ������������� ��������
static int curDir = 0;
/// ����� ������� ����������� �����. ����� ����� ���� �������� RECS_ON_PAGE ������
static int firstFile = 0;
/// ����� ������������� �����
static int curFile = 0;

static uint numDirs = 0;

static uint numFiles = 0;
/// ���� � �������� ��������
static char directory[255] = "\\";
/// ����� �������� ����� ��������� ��� ������
static const int NUM_ITEMS = 20;
static char names[NUM_ITEMS][50];

/// � ����� ��������� ��������� ����� � �������
struct State
{
    enum E
    {
        NeedRepaint,            ///< ����� �����������
        Idle                    ///< ������ ������ �� �����
    } value;
};

static State::E state = State::NeedRepaint;

FDrive::View FDrive::view = FDrive::Dirs;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������� �������� �������� �������� � ����������� [left, top]
static void DrawNameCurrentDir(int left, int top);
/// �������� ������ ���������
static void DrawDirs();
/// �������� ������ ������
static void DrawFiles();


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FDrive::Graphics::Init()
{
    strcpy(directory, "\\");
    firstDir = firstFile = curDir = curFile = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FDrive::Graphics::Draw()
{
    int x = Wave::Graphics::X();
    int y = Wave::Graphics::Y(Chan::A) + 1;
    int width = Wave::Graphics::Width() - 2;
    int height = Wave::Graphics::Height() * 2;
    Painter::FillRegion(x, y, width, height, Color::BACK);

    if(!FDrive::IsConnected())
    {
        Text::DrawBigText(30, 110, 2, "���������� ������", Color::FILL);
        return;
    }

    DrawNameCurrentDir(x + 3, y + 1);

    if(state == State::NeedRepaint)
    {
        for(int i = 0; i < NUM_ITEMS; i++)
        {
            names[i][0] = '\0';
        }

        numDirs = numFiles = 0;

        FDrive::RequestNumDirsAndFiles(directory);
        state = State::Idle;
    }

    if(view == Dirs)
    {
        DrawDirs();
    }
    else
    {
        DrawFiles();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawNameCurrentDir(int left, int top)
{
    Text::DrawText(left, top, directory, Color::FILL);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FDrive::HandlerSetNumDirsAndFiles(uint _numDirs, uint _numFiles)
{
    numDirs = _numDirs;
    numFiles = _numFiles;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawDirs()
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawFiles()
{

}
