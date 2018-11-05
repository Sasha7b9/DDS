#pragma once


class FDrive
{
public:
    /// ��������� �������������
    static void Init();
    /// ���������� ���������� ������ � ��������� � �������� directory
    static void GetNumDirsAndFiles(pString directory, int *numDirs, int *numFiles);

    class Graphics
    {
    friend class FDrive;

    public:
        /// ��������� �����-���������
        static void Draw();

    private:

        static void Init();
    };
};
