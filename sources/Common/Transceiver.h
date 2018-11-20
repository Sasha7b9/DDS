#pragma once
#include "Packet.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Transceiver
{
public:
    static void Send(uint8 *buffer, uint size);

private:
    static bool Send(Packet *packet);
};
