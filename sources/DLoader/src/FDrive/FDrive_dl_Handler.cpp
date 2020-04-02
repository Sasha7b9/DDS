#include "defines.h"
#include "libs/FatFS/ffconf.h"
#include "libs/FatFS/FatFS.h"
#include "FDrive/FDrive_dl.h"
#include "Generator/Generator_d.h"
#include "Utils/Buffer.h"
#include "Utils/Math.h"
#include "Utils/String.h"
#include <ff.h>
#include <cstdio>
#include <cmath>


struct StructForReadDir
{
    char nameDir[_MAX_LFN + 1];
    FILINFO fno;
    DIR dir;
};


struct FileSystem
{
    static uint GetFileSize(const char *fullPath);
    /// �������� ���������� ��������� � ������ � ������ ����������
    static void GetNumDirsAndFiles(const char *fullPath, uint *numDirs, uint *numFiles);
    /// �������� ��� numFile-�� ����� �� �������� fullPath
    static bool GetNameFile(const char *fullPath, int numFile, char *nameFileOut);
    /// ������ �������� �������� ������� �� ����� name
    static bool ReadFloats(float values[4096], char *name);
};


void DLDrive::GetNumDirsAndFiles(char *fullPath)
{
    uint numDirs = 0;
    uint numFiles = 0;

    FileSystem::GetNumDirsAndFiles(fullPath, &numDirs, &numFiles);
}


void DLDrive::RequestFile(int num, char *fullPath)
{
    char name[255];

    FileSystem::GetNameFile(fullPath, num, name);
}


void DLDrive::RequestFileSize(int num, char *path)
{
    char name[255];

    if (FileSystem::GetNameFile(path, num, name))           // �������� ��� �����
    {
        String fullPath("%s\\%s", path, name);

        FileSystem::GetFileSize(fullPath.CString());
    }
}


void FileSystem::GetNumDirsAndFiles(const char *fullPath, uint *numDirs, uint *numFiles)
{
    FILINFO fno;
    DIR dir;

    *numDirs = 0;
    *numFiles = 0;

    char nameDir[_MAX_LFN + 1];
    std::memcpy(nameDir, const_cast<char *>(fullPath), std::strlen(fullPath));
    nameDir[std::strlen(fullPath)] = '\0';

    if (f_opendir(&dir, nameDir) == FR_OK)
    {
        int numReadingElements = 0;
        bool alreadyNull = false;

        while (true) //-V2530
        {
            if (f_readdir(&dir, &fno) != FR_OK)
            {
                break;
            }
            if (fno.fname[0] == 0)
            {
                if (alreadyNull)
                {
                    break;
                }
                alreadyNull = true;
                continue;
            }
            numReadingElements++;
            if (fno.fname[0] != '.')
            {
                if (fno.fattrib & AM_DIR)
                {
                    (*numDirs)++;
                }
                else
                {
                    (*numFiles)++;
                }
            }
        }

        f_closedir(&dir);
    }
}


bool FileSystem::GetNameFile(const char *fullPath, int numFile, char *nameFileOut)
{
    StructForReadDir srd;

    std::memcpy(srd.nameDir, const_cast<char *>(fullPath), std::strlen(fullPath));
    srd.nameDir[std::strlen(fullPath)] = '\0';

    DIR *pDir = &srd.dir;
    FILINFO *pFNO = &srd.fno;
    if (f_opendir(pDir, srd.nameDir) == FR_OK)
    {
        int numFiles = 0;
        bool alreadyNull = false;
        while (true)
        {
            if (f_readdir(pDir, pFNO) != FR_OK)
            {
                *nameFileOut = '\0';
                f_closedir(pDir);
                return false;
            }
            if (pFNO->fname[0] == 0)
            {
                if (alreadyNull)
                {
                    *nameFileOut = '\0';
                    f_closedir(pDir);
                    return false;
                }
                alreadyNull = true;
            }
            if (numFile == numFiles && (pFNO->fattrib & AM_DIR) == 0)
            {
                std::strcpy(nameFileOut, pFNO->fname);
                return true;
            }
            if ((pFNO->fattrib & AM_DIR) == 0 && (pFNO->fname[0] != '.'))
            {
                numFiles++;
            }
        }
    }
    return false;
}


uint FileSystem::GetFileSize(const char *fullPath)
{
    FIL fp;
    if (f_open(&fp, fullPath, FA_READ) == FR_OK)
    {
        uint size = f_size(&fp);
        f_close(&fp);
        return size;
    }

    return static_cast<uint>(-1);
}


bool FileSystem::ReadFloats(float values[4096], char *name)
{
    bool result = false;

    FIL fp;
    FRESULT res = f_open(&fp, name, FA_READ);
    if (res == FR_OK)
    {
        char buffer[255];
        f_gets(buffer, 255, &fp);
        if (std::strcmp(buffer, "Rigol Technologies,Inc. Save analog waveform to text files.\r\n") == 0)
        {
            char *pointer = 0;
            int counter = 0;
            do
            {
                pointer = f_gets(buffer, 255, &fp);
                counter++;
            } while ((std::strcmp(buffer, " 0 \r\n") != 0) && (pointer[0] == buffer[0]));

            if (pointer[0] == buffer[0])
            {
                for (int i = 0; i < 4096; i++)
                {
                    f_gets(buffer, 255, &fp);

                    char *ptr = std::strchr(buffer, ',');
                    if (ptr != 0)
                    {
                        *ptr = '.';
                    }

                    std::sscanf(buffer, "%e", &values[i]);

                    f_gets(buffer, 255, &fp);
                }

                result = true;
            }
        }
        f_close(&fp);
    }

    return result;
}