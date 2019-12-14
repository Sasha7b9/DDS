#pragma once


#define ERROR_HANDLER() HAL::ErrorHandler()


struct CalibrationSettings;


struct HAL
{
	static void Init();

    static void ErrorHandler();
};


struct HAL_CRC32
{
    static uint Calculate(const void *address, uint size);

    static void Init();
};


struct HAL_DAC2
{
	static void Init();
	static void StartDMA(uint prescaler);
	static void StopDMA();
private:
	static void ConfigTIM7(uint prescaler);
};


struct HAL_EEPROM
{
    static void SaveSettings(CalibrationSettings *settings);

    static void LoadSettings(CalibrationSettings *settings);
};


// ���� ��� ����� � ����
struct HAL_FSMC
{
    static void Init();
};


struct HAL_GPIO
{
    static void WritePin(char port, uint16 maskPin, bool state);

    static bool ReadPin(char port, uint16 maskPin);
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


class HAL_TIM4
{
public:
    static void Init(void (*func)());
    /// ������� ������, ������� ����������� � timeStop ��
    static void Start(uint timeStopMS);

    static void Stop();

    static void ElapsedCallback();
};
