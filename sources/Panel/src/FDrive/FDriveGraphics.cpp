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

static int numDirs = 0;

static int numFiles = 0;
/// ���� � �������� ��������
static char directory[255] = "\\";

/// � ����� ��������� ��������� ����� � �������
struct State
{
    enum E
    {
        None,               ///< ��������� ��������� ����� �������
        WaitNumDirsAndFiles ///< �������� ������ �� ������ � ���������� ��������� � ������ � directory
    } value;
};

static State::E state = State::None;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������� �������� �������� �������� � ����������� [left, top]
static void DrawNameCurrentDir(int left, int top);


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

    if(state == State::None)
    {
        FDrive::RequestNumDirsAndFiles(directory);
        state = State::WaitNumDirsAndFiles;
    }
    else
    {
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawNameCurrentDir(int left, int top)
{
    Text::DrawText(left, top, directory, Color::FILL);
}
