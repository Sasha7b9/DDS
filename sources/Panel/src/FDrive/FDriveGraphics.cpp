#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "log.h"
#include "structs.h"
#include "FDrivePanel.h"
#include "Display/Console.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Wave.h"
#include "Hardware/CPU.h"
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RECS_ON_PAGE    10

/// ����� ������� ����������� ��������. ����� ����� ���� �������� RECS_ON_PAGE ����������
//static int firstDir = 0;
/// ����� ������������� ��������
//static int curDir = 0;
/// ����� ������� ����������� �����. ����� ����� ���� �������� RECS_ON_PAGE ������
//static int firstFile = 0;
/// ����� ������������� �����
//static int curFile = 0;
/// true, ���� ������ ����������
static bool isConnected = false;

static uint numDirs = 0;

static uint numFiles = 0;
/// ���� � �������� ��������
static char directory[255] = "\\";
/// ����� �������� ����� ��������� ��� ������
static const int NUM_ITEMS = 20;
static char names[NUM_ITEMS][50];

static bool isBusy = false;

/// � ����� ��������� ��������� ����� � �������
struct State
{
    enum E
    {
        NeedRepaint,            ///< ����� �����������
        Idle,                   ///< ������ ������ �� �����
        Wait                    ///< �������� ������ Interface
    } value;
};

static State::E state = State::NeedRepaint;

FDrive::View FDrive::view = FDrive::Files;
/// ����� �������� ��������� �� ����������
static uint8 message[300] = {0};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������� �������� �������� �������� � ����������� [left, top]
static void DrawNameCurrentDir(int left, int top);
/// ��������� ���������
static void ProcessMessage();


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FDrive::Graphics::Init()
{
    strcpy(directory, "\\");
    //firstDir = firstFile = curDir = curFile = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FDrive::Graphics::Draw()
{
    ProcessMessage();

    int x = Wave::Graphics::X();
    int y = Wave::Graphics::Y(Chan::A) + 1;
    int width = Wave::Graphics::Width() - 2;
    int height = Wave::Graphics::Height() * 2;
    Painter::FillRegion(x, y, width, height, Color::BACK);

    if(!isConnected)
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
        state = State::Wait;
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
void FDrive::HandlerInterface(uint8 *data)
{
    if(message[0])
    {
        LOG_WRITE("�� ���������� ���������� ���������");
        Console::Draw();
        Painter::EndScene();
        return;
    }

    if(isBusy)
    {
        LOG_WRITE("� ����� %d", *data);
        return;
    }

    memcpy(message, data, 300);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void ProcessMessage()
{
    isBusy = true;

    uint8 *data = &message[0];

    if(*data == 0)
    {
        isBusy = false;
        return;
    }

    if(*data == Command::FDrive_Mount)
    {
        isConnected = *(data + 1) != 0;
        if(!isConnected)
        {
            state = State::NeedRepaint;
        }
    }
    else if(*data == Command::FDrive_NumDirsAndFiles)
    {
        BitSet32 dirs(data + 1);
        BitSet32 files(data + 5);

        numDirs = dirs.word;
        numFiles = files.word;

        state = State::Idle;
    }
    else if(*data == Command::FDrive_RequestDir || *data == Command::FDrive_RequestFile)
    {
        BitSet32 num(data + 1);

        char *src = (char *)(data + 5);
        char *dest = &names[num.word][0];

        while(*src)
        {
            *dest++ = *src++;
        }

        *dest = '\0';

        state = State::Idle;
    }
    else
    {
        LOG_WRITE("�� ������� ���������");
    }

    message[0] = 0;

    isBusy = false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FDrive::DrawDirs()
{
    int x = Wave::Graphics::X() + 5;
    int y = Wave::Graphics::Y(Chan::A) + 15;
    int delta = 10;

    for(uint i = 0; i < numDirs; i++)
    {
        Text::DrawText(x, y, names[i], Color::FILL);
        y += delta;
    }

    if(state == State::Idle)
    {
        for(uint i = 0; i < numDirs; i++)
        {
            if(names[i][0] == 0)
            {
                FDrive::RequestNameDir(i, directory);
                state = State::Wait;
                break;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FDrive::DrawFiles()
{
    int x = Wave::Graphics::X() + 5;
    int y = Wave::Graphics::Y(Chan::A) + 15;
    int delta = 10;

    for(uint i = 0; i < numFiles; i++)
    {
        Text::DrawText(x, y, names[i], Color::FILL);
        y += delta;
    }

    if(state == State::Idle)
    {
        for(uint i = 0; i < numFiles; i++)
        {
            if(names[i][0] == 0)
            {
                FDrive::RequestNameFile(i, directory);
                state = State::Wait;
                break;
            }
        }
    }
}
