#include "defines.h"
#include "common/Messages_pl.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Interface/Interface_pl.h"
#include "Keyboard/Keyboard.h"


// True ����� ��������, ��� ������ �� ���������� ��� ������
static bool alreadyRequest = false;


int main()
{
    CPU::Init();
    Timer::Init();
    Keyboard::Init();

    while(1)
    {
        if(!Keyboard::BufferIsEmpty() && !alreadyRequest)
        {
            alreadyRequest = true;
            Message::RequestUpdate().Transmit();
        }

        PInterface::Update();
    }
}
