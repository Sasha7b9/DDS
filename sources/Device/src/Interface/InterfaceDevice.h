#pragma once
#include "Command.h"


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
    
    static void UpdateOld();
    /// ������� � ������ ���������� �������� �������
    static void SendFrequency(uint frequency);

    static void Empty(uint8 *);

    static void SetFormWave(uint8 *);

    static void ParameterValue(uint8 *);

    static void EnableChannel(uint8 *);

    static void RunReset(uint8 *);

    static void ModeDebug(uint8 *);

    static void WriteRegister(uint8 *);

    static void SetManipulation(uint8 *);

    static void SetManipulationMode(uint8 *);

    static void SetStartMode(uint8 *);

    static void LoadFormDDS(uint8 *);
    
    static void Test(uint8 *);

    static void SetKoeffCalibration(uint8 *);

    static void SetPolarity(uint8 *);

    static void Send(void *data, uint size);

private:

    static uint timeLastReceive;
};
