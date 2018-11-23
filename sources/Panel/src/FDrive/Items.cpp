#include "stdafx.h"
#ifndef WIN32
#include "defines.h"
#include "FDrivePanel.h"
#include "Items.h"
#include "Interface/InterfacePanel.h"
#include <cstring>
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  Items::numDirs = -1;
int  Items::numFiles = -1;
bool Items::requestIsSend = false;


struct StructFile
{
    pString name;
    StructFile(pString n = 0) : name(n) {}
}
names[25] =
{
    0
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Items::Init()
{
    numDirs = numFiles = -1;
    requestIsSend = false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Items::SendRequest()
{
    uint size = std::strlen(FDrive::directory) + 1 + 1;

    Message message(size, Command::FDrive_NumDirsAndFiles);
    std::strcpy((char *)message.Data() + 1, FDrive::directory);
    Interface::Send(&message);
    requestIsSend = true;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Items::Handler::Processing(Message *msg)
{
    msg->ResetPointer();

    uint8 command = msg->TakeByte();

    if (command == Command::FDrive_NumDirsAndFiles)
    {
        numDirs = (int)msg->TakeWord();
        numFiles = (int)msg->TakeWord();
        requestIsSend = false;
        return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
pString Items::GetNameItem(int i)
{
    if (names[i].name)
    {
        return names[i].name;
    }
    else if (i < numFiles)
    {
        //          ������� | �����_����� | ���_��������                     | �����������_����
        uint size = 1 +       1 +           std::strlen(FDrive::directory) +   1;
        Message message(size, Command::FDrive_RequestFile, (uint8)i);
        Interface::Send(&message);
    }

    return 0;
}
