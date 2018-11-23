#pragma once
#include <ff.h>
#include "Message.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FDrive
{
public:

    static void Init();

    static void Update();
    /// Interface �������� ��� ������� ��� ��������� �������� �������
    static void HandlerInterface(uint8 *);

    static USBH_HandleTypeDef hUSB_Host;

    class Handler
    {
        friend class Handlers;
        static void Processing(Message *msg);
    };
};
