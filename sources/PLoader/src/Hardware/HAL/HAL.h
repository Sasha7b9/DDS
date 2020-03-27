#pragma once


#define ERROR_HANDLER() HAL::ErrorHandler()


struct CalibrationSettings;


struct HAL
{
	static void Init();

    static void ErrorHandler();
};


struct HAL_EEPROM
{
    static void SaveSettings();

    static void LoadSettings();
};


struct HAL_SPI4
{
    static void Init();
    /// ��������� ������ ������
    static bool Transmit(const void *buffer, uint size, uint timeout);

    static bool Transmit(uint value, uint timeout);
    /// ������� ������ ������
    static bool Receive(void *recv, uint size, uint timeout);
    /// ������� ��������� size ���� � ���������� �� � compared. ���������� ���������� ��������� ����
    static uint ReceiveAndCompare(const void *compared, uint size);
    /// ���������� true, ���� ������ ����� � ������
    static bool IsReady();
    /// ����� ���� ����������� ����������
    static void WaitFreedom();
    /// �������� �������� ������� ���������� �� ��������� "�����" � ��������� "��������"
    static void WaitFalling();
};


struct HAL_TIM
{
    static uint TimeMS();

    static void Delay(uint timeMS);
};


// ����������� ��� �����
struct HAL_TIM2
{
    static void Init();

    static void DeInit();

    static uint TimeUS();

    static uint GetTicks();
    /// ��������� ������� ��� ��������� ����� �������� �������
    static void StartMultiMeasurement();
};


// ��� ��������
struct HAL_TIM3
{
    static void Init();

    static void StartIT(uint period);

    static void StopIT();

    static void DeInit();
};


struct HAL_TIM4
{
    static void Init(void (*func)());
    /// ������� ������, ������� ����������� � timeStop ��
    static void Start(uint timeStopMS);

    static void Stop();

    static void ElapsedCallback();
};