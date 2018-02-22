#include "defines.h"
#include "Display/DisplayTypes.h"
#include "Font.h"

//#include "font5display.inc"

#include "font8.inc"
#include "font5.inc"
#include "fontUGO.inc"
#include "fontUGO2.inc"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Font *fonts[TypeFont_Number] = {&font5, &font8, &fontUGO, &fontUGO2};
const Font *font = &font8;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Font::GetSize(void)
{
    return font->height;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Font::GetLengthText(const char *text)
{
    int retValue = 0;
    while (*text)
    {
        retValue += GetLengthSymbol(*text);
        text++;
    }
    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Font::GetHeightSymbol(char)
{
    return 9;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Font::GetLengthSymbol(uchar symbol)
{
    return font->symbol[symbol].width + 1;
}
