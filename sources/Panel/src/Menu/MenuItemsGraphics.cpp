#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "Display/DisplayTypes.h"
#include "Display/Font/Font.h"
#include "Display/Painter.h"
#include "Display/Text.h"
#include "Settings/Settings.h"
#include "Utils/Debug.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Item::Draw(bool opened, int x, int y) const
{
    if (type == Item::Type::Choice)
    {
        ((Choice *)this)->Draw(opened, x, y);
    }
    else if (type == Item::Type::Button)
    {
        ((Button *)this)->Draw(x, y);
    }
    else if (type == Item::Type::ChoiceParameter)
    {
        ((ChoiceParameter *)this)->Draw(opened, x, y);
    }
    else if (type == Item::Type::SmallButton)
    {
        ((SButton *)this)->Draw(x, y);
    }
    else if(type == Item::Type::Page)
    {
        ((Page *)this)->DrawClosed(x, y);
    }
    else
    {
        Painter::FillRegion(x + 2, y + 2, Item::WIDTH - 5, Item::HEIGHT - 4, Menu::GetOpenedItem() ? Color::GRAY_10 : Color::GREEN_25);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SButton::Draw(int x, int y)
{
    if(Menu::pressedItem == this)
    {
        Painter::SetColor(Color::BLUE);
    }
    funcForDraw(x, y);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Button::Draw(int x, int y)
{
    bool isShade = IsShade();

    Painter::FillRegion(x + 2, y + 2, Item::WIDTH - 5, Item::HEIGHT - 4, isShade ? Color::GRAY_10 : Color::GREEN_10);
    Painter::SetColor(isShade ? Color::GRAY_25 : Color::FILL);
    Text::DrawTextInColumn(x + 5, y + 17, Item::WIDTH, Title());
    funcForDraw(x, y);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Page::DrawClosed(int x, int y) const
{
    Color color = Color::GREEN_25;
    if(IsShade())
    {
        color = Color::GRAY_10;
    }
    else if(IsPressed())
    {
        color = Color::GREEN_50;
    }

    Painter::FillRegion(x + 2, y + 2, Item::WIDTH - 5, Item::HEIGHT - 4, color);
    Painter::SetColor(IsShade() ? Color::GRAY_25 : Color::FILL);
    Text::DrawTextInColumn(x + 4, y + 17, Item::WIDTH, Title());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ChoiceParameter::Draw(bool opened, int x, int y)
{
    if(opened)
    {
    }
    else
    {
        bool pressed = IsPressed();
        bool isShade = IsShade();
        opened = IsOpened();

        Painter::FillRegion(x + 2, y + 2, Item::WIDTH - 5, 15, pressed || opened ? Color::GRAY_50 : (isShade ? Color::GRAY_10 : Color::GREEN_10));
        Text::DrawText(x + 5, y + 5, Title(), pressed || opened ? Color::BACK : (isShade ? Color::GRAY_25 : Color::FILL));
        Painter::FillRegion(x + 2, y + 19, Item::WIDTH - 5, 34, isShade ? Color::GRAY_10 : Color::GREEN_25);
        Text::DrawTextRelativelyRight(315, y + 30, NameCurrentSubItem(), Color::BACK);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Choice::Draw(bool opened, int x, int y)
{
    int step = (int)(Step() + 0.5f);

    if(opened)
    {
        int width = Item::WIDTH;
        int height = GetHeightOpened();
        
        if(x == -1)
        {
            y = MP_TITLE_HEIGHT + PositionOnPage() % Menu::NUM_ITEMS_ON_DISPLAY * Item::HEIGHT;
            if(y + GetHeightOpened() > SCREEN_HEIGHT)
            {
                y = SCREEN_HEIGHT - GetHeightOpened() - 2;
            }
            x = SCREEN_WIDTH - Item::WIDTH - 20;
        }

        Painter::FillRegion(x, y, width, MI_TITLE_HEIGHT, Color::GRAY_50);
        Painter::FillRegion(x, y + MI_TITLE_HEIGHT, width, height - MI_TITLE_HEIGHT, Color::BACK);
        Painter::DrawRectangle(x, y, width, height, Color::FILL);
        Painter::DrawHLine(y + 12, x, x + width);
        Painter::DrawRectangle(x - 1, y - 1, width + 2, height + 2, Color::BACK);
        Text::DrawTextRelativelyRight(x + width - 2, y + 2, Title());

        y += 14;

        for (int i = 0; i < NumSubItems(); i++)
        {
            if (CurrentIndex() == i)
            {
                Painter::FillRegion(x + 2, y, Item::WIDTH - 4, 8, Color::GREEN_50);
                Painter::DrawHLine(y - 1, x + 1, x - 1 + Item::WIDTH - 1, Color::GREEN_75);
                Painter::DrawVLine(x + 1, y - 1, y - 1 + 10);
                Painter::DrawHLine(y + 9, x + 1, x + Item::WIDTH - 1, Color::GREEN_25);
                Painter::DrawVLine(x - 1 + Item::WIDTH, y - 1, y + 9);
                Text::DrawText(x + 3, y, NameSubItem(i), Color::BACK);
            }
            else
            {
                Text::DrawText(x + 3, y, NameSubItem(i), Color::FILL);
            }
            y += 10;
        }
    }
    else
    {
        bool pressed = IsPressed();
        bool isShade = IsShade();
        opened = IsOpened();

        Painter::FillRegion(x + 2, y + 2, Item::WIDTH - 5, 15, pressed || opened ? Color::GRAY_50 : (isShade ? Color::GRAY_10 : Color::GREEN_10));
        Text::DrawText(x + 5, y + 5, Title(), pressed || opened? Color::BACK : (isShade ? Color::GRAY_25 : Color::FILL));
        Painter::FillRegion(x + 2, y + 19, Item::WIDTH - 5, 34, isShade ? Color::GRAY_10 : Color::GREEN_25);
        Painter::SetColor(Color::BACK);
        if (step == 0.0f)
        {
            Text::DrawTextRelativelyRight(315, y + 30, NameCurrentSubItem());
        }
        else
        {
            int x0 = 315 - step;

            Text::DrawTextRelativelyRight(x0, y + 30, NameCurrentSubItem());

            int length = Font::GetLengthText(NameNextSubItem());

            if (x0 + length > x + Item::WIDTH - 5)
            {
                Text::DrawText(x0, y + 30, NameNextSubItem());
            }
            else
            {
                Text::DrawTextRelativelyRight(315, y + 30, NameNextSubItem());
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Page::Draw() const
{
    int numPage = CurrentSubPage();
    for (int i = numPage * 4; i < numPage * 4 + 4; i++)
    {
        int x = SCREEN_WIDTH - Item::WIDTH - 1;
        int y = MP_TITLE_HEIGHT + (i % Menu::NUM_ITEMS_ON_DISPLAY) * Item::HEIGHT;
        Painter::DrawRectangle(x, y, Item::WIDTH, Item::HEIGHT, Color::FILL);
        if(i < num)
        {
            items[i]->Draw(false, x, y);
        }
    }
}
