#pragma once


class PageService
{
public:
    static Page *pointer;

    class PageRegisters
    {
    public:

        static void Draw();

    private:
        /// �������� ��������
        static void DrawRegisters(int x, int y);

        static void DrawInputWindow();
    };
};
