#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "FDrivePanel.h"
#include "Display/Painter.h"
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

    FDrive::GetNumDirsAndFiles(directory, &numDirs, &numFiles);
}
