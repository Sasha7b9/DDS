#pragma once


class FDrive
{
friend class Interface;

public:
    /// ��������� �������������
    static void Init();
    /// true, ���� ������ ����������
    static bool IsConnected();

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
    /// ������������� ������� ������������� ������
    static void SetConnected(bool connected);
};
