#pragma once
#include "common/stm32/stm32.h"


class STM429 : public STM32
{
protected:

    static void Config();

private:

    static void SystemClockConfig();
};
