#include "Timer.h"
#include "Hardware/CPU.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    pFuncVV func;       // ������� �������
    uint dTms;          // ������ ������������, ��
    uint timeFirstMS;   // ����� ������� ������������
    uint timeNextMS;    // ����� ���������� ������������. ���� == 0xffffffff, �� ������ ���������
    bool repeat;        // ���� true, ����� �����������, ���� �� ����� ������� ������� Timer_Disable()
} TimerStruct;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static TimerStruct timers[NumTimers];
static TIM_HandleTypeDef handleTIM3;
static uint timeStartLogging = 0;
static uint timePrevPoint = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef TIME_NEXT
#define TIME_NEXT(type) (timers[type].timeNextMS)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void StartTIM(uint timeStop);    // ������� �����, ������� ����������� � timeStop ��
static void StopTIM();
static uint NearestTime();          // ���������� ����� ������������ ���������� �������, ���� 0, ���� �������� ���
static void TuneTIM(TypeTimer2 type);   // ��������� ������� �� ������


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Timer_IsRun(TypeTimer2 type)
{
    return TIME_NEXT(type) != MAX_UINT;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Init(void)
{
    for(uint i = 0; i < NumTimers; i++)
    {
        timers[i].timeNextMS = MAX_UINT;
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Set(TypeTimer2 type, pFuncVV func, uint dTms)
{
    TimerStruct *timer = &timers[type];
    timer->func = func;
    timer->dTms = dTms;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_SetAndStartOnce(TypeTimer2 type, pFuncVV func, uint dTms)
{
    Timer_Set(type, func, dTms);
    Timer_StartOnce(type);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_SetAndEnable(TypeTimer2 type, pFuncVV func, uint dTms)
{
    Timer_Set(type, func, dTms);
    Timer_Enable(type);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_StartOnce(TypeTimer2 type)
{
    timers[type].repeat = false;
    TuneTIM(type);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Enable(TypeTimer2 type)
{
    timers[type].repeat = true;
    TuneTIM(type);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void TuneTIM(TypeTimer2 type)
{
    TimerStruct *timer = &timers[type];
    timer->timeFirstMS = TIME_MS;

    uint timeNearest = NearestTime();

    uint timeNext = timer->timeFirstMS + timer->dTms;
    timer->timeNextMS = timeNext;

    if(timeNext < timeNearest)      // ���� ������ ������ ��������� ������ ��������
    {
        StartTIM(timeNext);         // �� ������� ������ �� ���� �����
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_Disable(TypeTimer2 type)
{
    timers[type].timeNextMS = MAX_UINT;
    timers[type].repeat = false;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static uint NearestTime(void)
{
    uint time = MAX_UINT;

    for(uint type = 0; type < NumTimers; type++)
    {
        if(TIME_NEXT(type) < time)
        {
            time = TIME_NEXT(type);
        }
    }
    
    return time;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void StartTIM(uint timeStopMS)
{
    StopTIM();

    if(timeStopMS == MAX_UINT)
    {
        return;
    }

    uint dT = timeStopMS - TIME_MS;

    handleTIM3.Init.Period = (dT * 2) - 1;      // 10 ������������� 0.1��. �.�. ���� ��� ����� 1��, ����� �������� (100 - 1)

    HAL_TIM_Base_Init(&handleTIM3);
    HAL_TIM_Base_Start_IT(&handleTIM3);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void StopTIM(void)
{
    HAL_TIM_Base_Stop_IT(&handleTIM3);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_PauseOnTime(uint timeMS)
{
    uint time = TIME_MS;
    while (TIME_MS - time < timeMS)
    {
    };
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_PauseOnTicks(uint numTicks)
{
    uint startTicks = TIME_TICS;
    while (TIME_TICS - startTicks < numTicks)
    {
    };
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Timer_StartLogging(void)
{
    timeStartLogging = TIME_TICS;
    timePrevPoint = timeStartLogging;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
uint Timer_LogPointUS(char *)
{
    uint interval = TIME_TICS - timePrevPoint;
    timePrevPoint = TIME_TICS;
    return interval;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
uint Timer_LogPointMS(char *)
{
    uint interval = TIME_TICS - timePrevPoint;
    timePrevPoint = TIME_TICS;
    return interval;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef TIME_NEXT
