#include "defines.h"
#include "Display/Display.h"
#include "Hardware/Beeper.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"
#include "Keyboard/Keyboard.h"
#include <stm32f4xx_hal.h>


static Key commands[10];
static int pointer = 0;
static GPIO_TypeDef * const ports[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE};


static void DetectRegulator();

#define SL0 (1 << 12)
#define SL1 (1 << 13)
#define SL2 (1 << 14)
#define SL3 (1 << 15)
#define SL4 (1 << 8)
#define SL5 (1 << 9)
#define NUM_SL 6

#define RL0 (1 << 8)
#define RL1 (1 << 9)
#define RL2 (1 << 10)
#define RL3 (1 << 13)
#define RL4 (1 << 12)
#define NUM_RL 5

#define BUTTON_IS_PRESS(state)  ((state) == 0)

/// ��� ����������� ������� ������ ���� ������������ ����� �������
static uint timePress[5][6];

//                                         SL0      SL1       SL2          SL3        S4          SL5
static const Key::E controls[5][6] = {{Key::_0, Key::_5, Key::Dot,   Key::Esc,   Key::F1,   Key::None},    // RL0
                                      {Key::_1, Key::_6, Key::Minus, Key::Right, Key::F2,   Key::None},    // RL1
                                      {Key::_2, Key::_7, Key::None,  Key::Left,  Key::F3,   Key::None},    // RL2
                                      {Key::_3, Key::_8, Key::On1,   Key::None,  Key::F4,   Key::None},    // RL3
                                      {Key::_4, Key::_9, Key::On2,   Key::None,  Key::None, Key::None}};   // RL4

static uint16 sls[] =             {SL0,   SL1,   SL2,   SL3,   SL4,   SL5};
static char slsAsciiPorts[] =     {'B',   'B',   'B',   'B',   'D',   'D'};

static uint16 rls[] =             {RL0,   RL1,   RL2,   RL3,   RL4};
static char rlsAsciiPorts[] =     {'A',   'A',   'A',   'D',   'D'};

#define SET_SL(n)       HAL_PIO::WritePin(slsAsciiPorts[n], sls[n], true)
#define SET_ALL_SL      HAL_PIO::WritePin('B', SL0 | SL1 | SL2 | SL3, true); HAL_PIO::WritePin('D', SL4 | SL5, true);
#define RESET_SL(n)     HAL_PIO::WritePin(slsAsciiPorts[n], sls[n], false)
#define READ_RL(n)      HAL_PIO::ReadPin(rlsAsciiPorts[n], rls[n])

static bool init = false;


void Keyboard::Init()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            timePress[i][j] = 0;
        }
    }

    pointer = 0;

    HAL_TIM4::Init(&Keyboard::Update);

    Keyboard::InitInputs(sls, slsAsciiPorts, 6, rls, rlsAsciiPorts, 5);

    init = true;
}


void Keyboard::Update()
{
    if(!init)
    {
        return;
    }
    
    uint time = TIME_MS;

    for (int sl = 0; sl < NUM_SL; sl++)
    {
        RESET_SL(sl);

        for (int rl = 0; rl < NUM_RL; rl++)
        {
            bool state = READ_RL(rl);

            Key::E control =  controls[rl][sl];

            if (control != Key::None)
            {
                if (timePress[rl][sl] && timePress[rl][sl] != MAX_UINT)         // ���� ������� ��������� � ������� ���������
                {
                    uint delta = time - timePress[rl][sl];
                    if(delta > 500)                                             // ���� ������ ����� 500 �� � ������� ������� -
                    {
                        timePress[rl][sl] = MAX_UINT;
                        AppendEvent(controls[rl][sl], Key::Action::Long);   // ��� ����� ������� �������
                    }
                    else if (delta > 100 &&                                     // ���� ������ ����� 100 �� � ������� �������
                        !BUTTON_IS_PRESS(state))                                // � ������ ������ ��������� � ������� ���������
                    {
                        timePress[rl][sl] = MAX_UINT;                           // �� ��������� ��� � �������
                        AppendEvent(controls[rl][sl], Key::Action::Up);     // � ��������� ���������� ������ � ������ ������
                    }
                    else
                    {
                        // ����� ������
                    }
                }
                else if (BUTTON_IS_PRESS(state) && timePress[rl][sl] != MAX_UINT)   // ���� ������ ������
                {
                    timePress[rl][sl] = time;                                       // �� ��������� ����� � �������
                    AppendEvent(controls[rl][sl], Key::Action::Down);
                }
                else if(!BUTTON_IS_PRESS(state) && timePress[rl][sl] == MAX_UINT)
                {
                    timePress[rl][sl] = 0;
                }
                else
                {
                    // ����� ������
                }
            }
        }
        
        SET_ALL_SL;
    }
    
    DetectRegulator();

    SET_ALL_SL;
}


static void DetectRegulator()
{
    // ����������� ������
    static bool prevPressButton = false;
    static uint timePrevPress = 0;
    static bool needDetectButton = true;
    
    bool press = HAL_PIO::ReadPin('C', GPIO_PIN_2) ? false : true;

    if(!press)
    {
        needDetectButton = true;
    }

    if(needDetectButton)
    {
        uint time = TIME_MS;

        if(press && prevPressButton && time - timePrevPress > 500)          // ���� ������� ������ ����� 0.5 ���
        {
            Keyboard::AppendEvent(Key::RegButton, Key::Action::Long);                                     // �������� ������� �������
            needDetectButton = false;
            prevPressButton = false;
            timePrevPress = 0;
        }

        if(timePrevPress == 0)                                              // ���� ������ ���������� ����� � ������� ���������
        {
            if(press)                                                       // � ������ ������
            {
                timePrevPress = time;
                prevPressButton = true;
                Keyboard::AppendEvent(Key::RegButton, Key::Action::Down);
            }
        }
        else                                                                // ����� ����� ���� ������ �����
        {
            if(time - timePrevPress > 50)                                   // �� ��������� � ��������� ��� ����� �� ����� ��� ����� 50 ��
            {                                                               // �� ��������� �������� ���������
                if(!press)
                {
                    Keyboard::AppendEvent(Key::RegButton, Key::Action::Up);
                    timePrevPress = 0;
                    prevPressButton = false;
                }
            }
        }
    }


    // ����������� �������
    static bool prevStatesIsOne = false;

    bool stateLeft = HAL_PIO::ReadPin('C', GPIO_PIN_0);
    bool stateRight = HAL_PIO::ReadPin('C', GPIO_PIN_1);

    if (stateLeft && stateRight)
    {
        prevStatesIsOne = true;
    }
    else if (prevStatesIsOne && stateLeft && !stateRight)
    {
        Keyboard::AppendEvent(Key::RegLeft, Key::Action::Down);
        prevStatesIsOne = false;
    }
    else if (prevStatesIsOne && !stateLeft && stateRight)
    {
        Keyboard::AppendEvent(Key::RegRight, Key::Action::Down);
        prevStatesIsOne = false;
    }
    else
    {
        // ����� ������
    }
}


void Keyboard::AppendEvent(Key::E key, Key::Action::E action)
{
    commands[pointer++] = Key(key, action);

    Beeper::Beep(action);
}


bool Keyboard::BufferIsEmpty()
{
    return pointer == 0;
}


Key Keyboard::GetNextControl()
{
    Key retValue;

    if (BufferIsEmpty())
    {
        retValue.value = Key::None;
    }
    else
    {
        retValue = commands[0];
        for (int i = 1; i < pointer; i++)
        {
            commands[i - 1] = commands[i];
        }
        --pointer;
    }

    return retValue;
}

#ifdef WIN32
void Keyboard::InitInputs(const uint16 *, const char *, int, const uint16 *, const char *, int) {}
#else
void Keyboard::InitInputs(const uint16 *sl, const char *portSL, int numSL, const uint16 *rl, const char *portRL, int numRL)
{
    GPIO_InitTypeDef isGPIO;

    for (int i = 0; i < numRL; i++)
    {
        isGPIO.Pin = rl[i];
        isGPIO.Mode = GPIO_MODE_INPUT;
        HAL_GPIO_Init(ports[portRL[i] - 'A'], &isGPIO);
    }

    for (int i = 0; i < numSL; i++)
    {
        isGPIO.Pin = sl[i];
        isGPIO.Mode = GPIO_MODE_OUTPUT_PP;
        HAL_GPIO_Init(ports[portSL[i] - 'A'], &isGPIO);
    }

    // �������������� �����
    isGPIO.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
    isGPIO.Mode = GPIO_MODE_INPUT;
    isGPIO.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC, &isGPIO);
}
#endif


const char *PanelControlName(const Key &control)
{
    static const char *names[] =
    {
        "None",
        "F1",
        "F2",
        "F3",
        "F4",
        "F5",
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        ".",
        "-",
        "Esc",
        "left",
        "right",
        "Ch",
        "WF",
        "M",
        "U",
        "ON1",
        "ON2",
        "Reg Left",
        "Reg right",
        "Reg ������"
    };

    return names[control];
}


void Keyboard::Draw()
{
} 

#ifdef __cplusplus
extern "C" {
#endif

    
    void TIM4_IRQHandler()
    {
        if ((TIM4->SR & TIM_SR_UIF) == TIM_SR_UIF)
        {
            if ((TIM4->DIER & TIM_DIER_UIE) == TIM_DIER_UIE)
            {
                TIM4->SR = ~TIM_DIER_UIE;
                HAL_TIM4::ElapsedCallback();
            }
        }
    }

#ifdef __cplusplus
}
#endif