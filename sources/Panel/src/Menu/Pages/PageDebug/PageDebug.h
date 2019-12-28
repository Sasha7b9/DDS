#pragma once
#include "Menu/MenuItems.h"


struct PageDebug
{
    static Page *self;

    struct PageRegisters
    {
        static void Draw();

    private:
        /// �������� ��������
        static void DrawRegisters(int x, int y);

        static void DrawInputWindow();
    };

    struct SubRange
    {
        static Page *self;
    };

    struct Colors
    {
        static Page *self;

        struct ChanA
        {
            static Page *self;
        };

        struct ChanB
        {
            static Page *self;
        };

        struct Menu
        {
            static Page *self;
        };
    };
};
