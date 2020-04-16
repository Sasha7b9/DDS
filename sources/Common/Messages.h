#pragma once
#include "Command.h"

#ifdef PANEL
#include "Generator/Generator_p.h"
#else
#ifdef PLOADER
#include "Generator/Generator_p.h"
#else
#include "Generator/Generator_d.h"
#endif
#endif


class SimpleMessage  // -V690
{
public:
    explicit SimpleMessage();
    explicit SimpleMessage(int size, uint8);
 
    ~SimpleMessage();

    void Create(int size, uint8);
    /// ���������� ��������� �� ��������� �����
    SimpleMessage *Clone();
    /// ���������� ��������� ����������� ����������.
    void ResetPointer() { taken = 0; };

    bool CreateFromMessage(const SimpleMessage *message);
    /// ������� ��������� � ���������� ������
    bool CreateAllocate(const uint8 *buffer, int size);
    /// �������� ����������� ���������� ������
    bool AllocateMemory(int size);
    /// ����� ����
    uint8 TakeUINT8();
    /// ����� ���������
    uint16 TakeUINT16();
    int16 TakeINT16();
    /// ����� �����
    uint TakeUINT();
    int TakeINT();

    uint64 TakeUINT64();

    float TakeFLOAT();
    /// ����� ���������� ������. ����� ������ ���� ������� �������� �� ��������� ������ ������
    void TakeRemainigData(uint8 *data);
    /// ���������� ��������� �� ���������� ������. ������ ����� ������� �����
    uint8 *RemainingData() const;
    /// ���������� ������
    void FreeMemory();
    /// ���������� ��������� �� ������
    uint8 *Data(int pos = 0);
    /// ���������� ������ ������
    int Size() const;
    /// ���������� true, ���� ��� null-����� (������ �� ��������)
    bool IsEmpty() const;
    /// ���������� true, ���� ��������� ���������
    bool IsEquals(const SimpleMessage *message) const;
    /// ���������� ��������� �� pos-� �������. ������ ��� ����������� �����
    char *String(int pos);

    /// �������� �����
    void PutUINT(uint data);
    void PutINT(int data);

    /// �������� �������� �����
    void PutINT16(int16 data);
  
    // �������� ��������� ����������
    void Transmit();
    // �������� ��������� ���������� � ���������, ���� ��� ������� ������������ �����
    void TransmitAndSend();
    /// �������� ������
    void PutData(const uint8 *data, int length);
protected:
    /// �������� ����
    void PutByte(uint8 data);

    void PutDoubleWord(uint64 data);

    void PutHalfWord(uint16 data);
    /// �������� float
    void PutFloat(float data);
    /// ������ ���������� ������
    int allocated;
    /// ����� ������ ������, ���� 0, ���� ������ �� ��������
    uint8 *buffer;
    /// ������� ������ ������ ��������� �������. ������������ ��� Put
    int used;
    /// �� ����� ������� ���������. ������������ ��� Take
    int taken;

    SimpleMessage(const SimpleMessage &) : allocated(0), buffer(0), used(0), taken(0) {};

public:
    static int created;
    static int destroed;
    static int createdSize;
    static int destroedSize;
};


namespace Message
{

    /// ��������� ��������� - ��� ������ ����� ������������
    class RequestData : public SimpleMessage
    {
    public:
        RequestData();
    };


    /// ��������� � �������
    class Log : public SimpleMessage
    {
    public:
        Log(char *string);
    };


    /// ��������� ������ �������
    class StartMode : public SimpleMessage
    {
    public:
        StartMode(uint8 ch, uint8 mode);
    };


    /// ������ � �������
    class WriteRegister : public SimpleMessage
    {
    public:
        WriteRegister(uint8 reg, uint64 data);
    };


    /// ��������� ����������� ������
    class DebugMode : public SimpleMessage
    {
    public:
        /// mode == 1/0 - ��������/��������� ����� �������
        DebugMode(uint8 mode);
    };


    /// ��������/��������� �����
    class EnableChannel : public SimpleMessage
    {
    public:
        /// ch : 0 - A, 1 - B
        /// enable : 0 - ���������, 1 - ��������
        EnableChannel(uint8 ch, uint8 enable);
    };

    /// ��������� ���� ��������
    class RegCPU : public SimpleMessage
    {
    public:
        RegCPU(uint8 port, uint8 pin, uint8 state);
    };


    namespace FDrive
    {

        /// ��������� ��������� ���� � FPGA
        class LoadFromExtStorage : public SimpleMessage
        {
        public:
            LoadFromExtStorage(uint8 ch, uint8 numFile, char *directory);
        };


        /// ������ ����� �����
        class FileName : public SimpleMessage
        {
        public:
            FileName(uint8 numFile, char *name);
        };


        class FileString : public SimpleMessage
        {
        public:
            FileString(uint numString, char *nameFile);
        };


        /// ����� ��������� � ������ � ������� ��������
        class NumDirsAndFiles : public SimpleMessage
        {
        public:
            NumDirsAndFiles(uint numDirs, uint numFiles);
            NumDirsAndFiles(char *directory);
        };


        /// ��������� � ���������������/�������������� �����
        class Mount : public SimpleMessage
        {
        public:
            /// mount :
            /// 0 - ������ �������������;
            /// 1 - ������ ������ ��������������
            /// 2 - ������ ������������� �� �������
            Mount(uint8 mount);
        };


        /// ������ ������� �����
        class FileSize : public SimpleMessage
        {
        public:
            FileSize(uint8 numFile, uint size);
        };


        class PictureDDS : public SimpleMessage
        {
        public:
            /// ������
            PictureDDS(uint8 numFile);
            /// �����
            PictureDDS(uint8 numFile, uint8 *data);
        };
    }

    namespace Set
    {

        /// ��������� ����� �������
        class FormWave : public SimpleMessage
        {
        public:
            FormWave(uint8 ch, uint8 form);
        };


        /// ��������� ���������
        class Amplitude : public SimpleMessage
        {
        public:
            Amplitude(uint8 ch, uint64 amplitude);
        };


        /// ��������� �������� ������� �� ������
        class Offset : public SimpleMessage
        {
        public:
            Offset(uint8 ch, uint64 offset);
        };


        /// ������������� ���������� ��� ������� ���������
        class Parameter : public SimpleMessage
        {
        public:
            Parameter(Command::E param, uint8 ch, uint64 value);
            Parameter(Command::E param, uint8 ch, uint8 choice);
        };
    }

    namespace FreqMeter
    {

        /// ��������� ��������� �����������
        class Measure : public SimpleMessage
        {
        public:
            Measure(uint frequency);
        };
    }

    namespace SCPI
    {
        /// ������ SCPI
        class Data : public SimpleMessage
        {
        public:
            Data(uint8 *data, int length);
        };
    }

    /// ������� �������������� ������������ � ��������� �������������� �������� ����������
    class CalibrateSet : public SimpleMessage
    {
    public:
        CalibrateSet(uint8 ch, uint8 signal, uint8 range, uint8 parameter);
    };

    /// ������� �������������� ������������
    class CalibrateLoad : public SimpleMessage
    {
    public:
        CalibrateLoad(uint8 ch, uint8 signal, uint8 range, uint8 parameter);
    };
}
