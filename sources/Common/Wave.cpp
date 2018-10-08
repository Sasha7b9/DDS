#include "CommonTypes.h"
#include "defines.h"
#include "Wave.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pString Form::Name(Language lang) const
{
    static const struct StructName
    {
        pString name;
        StructName(pString n) : name(n)
        {
        };
    }
    names[Form::Number][2] =
    {
        {"�����",    "Sine"},
        {"����+",    "Ramp+"},
        {"����-",    "Ramp-"},
        {"������",   "Meander"},
        {"�������",  "Impulse"},
        {"�����",    "Packet"}
    };

    return names[value][lang].name;
}
