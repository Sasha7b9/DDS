#pragma once


struct StructForReadDir;


struct DLDrive
{
    static void Init();

    static void Update();

    static bool IsConnected();

    static void *handleUSBH;

    struct File
    {
        // ��������� ���� ��� ������. ���������� ������ ����� ��� -1, ���� ���� �� ����������
        static int Open(const char *name);

        static int Read(int size, uint8 *buffer);

        static void Close();
    };
};
