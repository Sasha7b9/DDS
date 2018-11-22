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
    /// ������ ��������� ��� �������� � ������ ������� ������ ��� ��������
    static bool CreateMessageForSend(Message *message);

    static void Empty(Message *);

    static void SetFormWave(Message *);

    static void ParameterValue(Message *);

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

    static void Send(void *data, uint size);

private:

    static uint timeLastReceive;
};
