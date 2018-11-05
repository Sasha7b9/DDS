#pragma once


class FDrive
{
public:
    /// ��������� �������������
    static void Init();
    /// true, ���� ������ ����������
    static bool Connected();

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
