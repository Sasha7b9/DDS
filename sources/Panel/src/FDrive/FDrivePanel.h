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

    /// ��������� �����-���������
    static void Draw();
    /// ��������� ������� ������ "�����"
    static void PressUp();
    /// ��������� ������� ������ "����"
    static void PressDown();
    /// �������� ������ ���������
    static void DrawDirs();
    /// �������� ������ ������
    static void DrawFiles();
    /// ��������� ���������
    static void ProcessMessage();

private:
    friend class Graphics;
    friend class Interface;

    /// �������� ������ �� ���������� ������ � ��������� � �������� directory
    static void RequestNumDirsAndFiles(pString directory);

    static void RequestNameDir(uint numDir, pString directory);

    static void RequestNameFile(uint numFile, pString directory);

    static void HandlerInterface(uint8 *data);
};
