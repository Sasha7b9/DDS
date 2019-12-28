#include "defines.h"
#include "Display/Painter.h"
#include "Menu/Pages/PageDebug/PageDebug.h"
#include "Settings/Settings.h"


static int16 redChanA = 0;
static int16 greenChanA = 0;
static int16 blueChanA = 0;

static int16 redChanB = 0;
static int16 greenChanB = 0;
static int16 blueChanB = 0;

static int16 redMenu = 0;
static int16 greenMenu = 0;
static int16 blueMenu = 0;


void PageDebug::Colors::Init()
{
    redChanA = static_cast<int16>(R_FROM_COLOR(Color::CHAN_A.GetRGB()));
    greenChanA = static_cast<int16>(G_FROM_COLOR(Color::CHAN_A.GetRGB()));
    blueChanA = static_cast<int16>(B_FROM_COLOR(Color::CHAN_A.GetRGB()));

    redChanB = static_cast<int16>(R_FROM_COLOR(Color::CHAN_B.GetRGB()));
    greenChanB = static_cast<int16>(G_FROM_COLOR(Color::CHAN_B.GetRGB()));
    blueChanB = static_cast<int16>(B_FROM_COLOR(Color::CHAN_B.GetRGB()));

    redMenu = static_cast<int16>(R_FROM_COLOR(Color::MENU_ITEM.GetRGB()));
    greenMenu = static_cast<int16>(G_FROM_COLOR(Color::MENU_ITEM.GetRGB()));
    blueMenu = static_cast<int16>(B_FROM_COLOR(Color::MENU_ITEM.GetRGB()));
}


static void OnChanged()
{
    COLOR(Color::CHAN_A.value) = MAKE_COLOR(redChanA, greenChanA, blueChanA);
    COLOR(Color::CHAN_B.value) = MAKE_COLOR(redChanB, greenChanB, blueChanB);
    COLOR(Color::MENU_ITEM.value) = MAKE_COLOR(redMenu, greenMenu, blueMenu);

    Painter::LoadPalette();
}


DEF_GOVERNOR( gRedChanA,
    "�������",
    "",
    redChanA, 0, 255, *PageDebug::Colors::ChanA::self, Item::FuncActive, OnChanged, EmptyFuncVV, EmptyFuncVB);


DEF_GOVERNOR(gGreenChanA,
    "������",
    "",
    greenChanA, 0, 255, *PageDebug::Colors::ChanA::self, Item::FuncActive, OnChanged, EmptyFuncVV, EmptyFuncVB);

DEF_GOVERNOR(gBlueChanA,
    "�����",
    "",
    blueChanA, 0, 255, *PageDebug::Colors::ChanA::self, Item::FuncActive, OnChanged, EmptyFuncVV, EmptyFuncVB);


DEF_PAGE_3( pChanA,
    "����� 1",
    "",
    &gRedChanA,
    &gGreenChanA,
    &gBlueChanA,
    Page::Color_ChanA, PageDebug::Colors::self, Item::FuncActive, FuncPress, FuncOnKey, Page::FuncDraw
)



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_GOVERNOR(gRedChanB,
    "�������",
    "",
    redChanB, 0, 255, *PageDebug::Colors::ChanB::self, Item::FuncActive, OnChanged, EmptyFuncVV, EmptyFuncVB);


DEF_GOVERNOR(gGreenChanB,
    "������",
    "",
    greenChanB, 0, 255, *PageDebug::Colors::ChanB::self, Item::FuncActive, OnChanged, EmptyFuncVV, EmptyFuncVB);

DEF_GOVERNOR(gBlueChanB,
    "�����",
    "",
    blueChanB, 0, 255, *PageDebug::Colors::ChanB::self, Item::FuncActive, OnChanged, EmptyFuncVV, EmptyFuncVB);


DEF_PAGE_3(pChanB,
    "����� 2",
    "",
    &gRedChanB,
    &gGreenChanB,
    &gBlueChanB,
    Page::Color_ChanA, PageDebug::Colors::self, Item::FuncActive, FuncPress, FuncOnKey, Page::FuncDraw
)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_GOVERNOR(gRedMenu,
    "�������",
    "",
    redMenu, 0, 255, *PageDebug::Colors::Menu::self, Item::FuncActive, OnChanged, EmptyFuncVV, EmptyFuncVB);


DEF_GOVERNOR(gGreenMenu,
    "������",
    "",
    greenMenu, 0, 255, *PageDebug::Colors::Menu::self, Item::FuncActive, OnChanged, EmptyFuncVV, EmptyFuncVB);

DEF_GOVERNOR(gBlueMenu,
    "�����",
    "",
    blueMenu, 0, 255, *PageDebug::Colors::Menu::self, Item::FuncActive, OnChanged, EmptyFuncVV, EmptyFuncVB);


DEF_PAGE_3(pMenu,
    "����",
    "",
    &gRedMenu,
    &gGreenMenu,
    &gBlueMenu,
    Page::Color_ChanA, PageDebug::Colors::self, Item::FuncActive, FuncPress, FuncOnKey, Page::FuncDraw
)


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEF_PAGE_3(pColors,
    "�����",
    "",
    PageDebug::Colors::ChanA::self,
    PageDebug::Colors::ChanB::self,
    PageDebug::Colors::Menu::self,
    Page::Colors, PageDebug::self, Item::FuncActive, FuncPress, FuncOnKey, Page::FuncDraw
)


Page *PageDebug::Colors::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pColors));
Page *PageDebug::Colors::ChanA::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pChanA));
Page *PageDebug::Colors::ChanB::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pChanB));
Page *PageDebug::Colors::Menu::self = reinterpret_cast<Page *>(const_cast<PageBase *>(&pMenu));
