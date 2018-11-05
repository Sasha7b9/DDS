#pragma once


class FDrive
{
public:
    /// ��������� �������������
    static void Init();

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
    /// �������� ������ �� ���������� ������ � ��������� � �������� directory
    static void RequestNumDirsAndFiles(pString directory);
};
