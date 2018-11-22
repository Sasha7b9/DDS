#pragma once
#include "Command.h"
#include "Message.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Interface
{
public:

    /// ��������� ��� ������ � �����������
    struct Data
    {
    public:

        Data(uint size, uint8 command = 0);

        ~Data();
        /// ���������������� ��������� ��� �������� size ���� ������
        bool Init(uint size);
        /// ���������� ������, �������������� ����������. ����������� ����� �� ����� �������������
        void Release();
        /// ���������� true, ���� ����� ���� - ������� ������
        bool IsEmpty() const;
        /// ���������� ��������� �� ������
        uint8 *GetData();
        /// ���������� ������ ������ ������
        uint GetSize() const;
    private:
        uint8 *data;
        uint size;
    };

    static void Update();
    /// ������� ����������� ����� ���������, ������� ����� �������� � ������� ��� ��������. ���������� ������� ����� � ����� ������ ��������� ��� �����������
    static void AddMessageInQueue(Message *message);

    static void SendData(Message *);

    static void Empty(Message *);

    static void SetFormWave(Message *);

    static void SetFrequency(Message *);

    static void SetPeriod(Message *);

    static void SetAmplitude(Message *);

    static void SetOffset(Message *);

    static void SetDuration(Message *);

    static void SetDutyRatio(Message *);

    static void SetPhase(Message *);

    static void SetDelay(Message *);

    static void SetManipulationDuration(Message *);

    static void SetManipulationPeriod(Message *);

    static void SetPacketPeriod(Message *);

    static void SetPacketNumber(Message *);

    static void EnableChannel(Message *);

    static void RunReset(Message *);

    static void ModeDebug(Message *);

    static void WriteRegister(Message *);

    static void SetManipulation(Message *);

    static void SetManipulationMode(Message *);

    static void SetStartMode(Message *);

    static void LoadFormDDS(Message *);
    
    static void Test(Message *);

    static void SetKoeffCalibration(Message *);

    static void GetKoeffCalibration(Message *);

    static void SetPolarity(Message *);

private:

    static uint timeLastReceive;
};
