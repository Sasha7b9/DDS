#pragma once


class FDrive
{
public:
    /// ��������� �������������
    static void Init();

    /// ��� ���������� - �������� ��� �����
    enum View
    {
        Dirs,
        Files
    };
    
    static View view;

    class Graphics
    {
    friend class FDrive;

    public:
        /// ��������� �����-���������
        static void Draw();

    private:

        static void Init();
    };

private:
    friend class Graphics;
    friend class Interface;

    /// �������� ������ �� ���������� ������ � ��������� � �������� directory
    static void RequestNumDirsAndFiles(pString directory);

    static void RequestNameDir(uint numDir, pString directory);

    static void RequestNameFile(uint numFile, pString directory);

    static void HandlerInterface(uint8 *data);

    /// �������� ������ ���������
    static void DrawDirs();
    /// �������� ������ ������
    static void DrawFiles();
};
