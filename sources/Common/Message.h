#pragma once
#include "Command.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SimpleMessage  // -V690
{
    friend class Transceiver;
public:
    explicit SimpleMessage();
    explicit SimpleMessage(uint size, uint8);
    explicit SimpleMessage(uint size, uint8, uint8);
    explicit SimpleMessage(uint size, uint8, uint8, uint);
    explicit SimpleMessage(uint size, uint8, uint, uint);
    explicit SimpleMessage(uint size, uint8, uint8, uint8);
    explicit SimpleMessage(uint size, uint8, uint8, float);
    explicit SimpleMessage(uint size, uint8, uint8, uint64);
    explicit SimpleMessage(uint8, char*);
    explicit SimpleMessage(uint8, uint8, char *);
    explicit SimpleMessage(uint8, uint8, uint8, char *);
    explicit SimpleMessage(uint8, uint, char*);

    ~SimpleMessage();

    void Create(uint size, uint8);
    void Create(uint size, uint8, uint8);
    void Create(uint size, uint8, uint, uint);
    void Create(uint size, uint8, uint8, uint8);
    void Create(uint size, uint8, uint8, float);
    void Create(uint size, uint8, uint8, uint8, uint16);
    void Create(uint8, uint8, uint8, char *string);
    void Create(uint8, uint8, char *string);
    void Create(uint8, uint, char *);
    void Create(uint size, uint8 com, uint8 d0, uint d1);
    /// ���������� ��������� �� ��������� �����
    SimpleMessage *Clone();
    /// ���������� ��������� ����������� ����������.
    void ResetPointer() { taken = 0; };

    bool CreateFromMessage(SimpleMessage *message);
    /// ������� ��������� � ���������� ������
    bool CreateAllocate(uint8 *buffer, uint size);
    /// �������� ����������� ���������� ������
    bool AllocateMemory(uint size);
    /// ����� ����
    uint8 TakeByte();
    /// ����� ���������
    uint16 TakeHalfWord();
    /// ����� �����
    uint TakeWord();

    uint64 TakeDoubleWord();

    float TakeFloat();
    /// ����� ���������� ������. ����� ������ ���� ������� �������� �� ��������� ������ ������
    void TakeRemainigData(uint8 *data);
    /// ���������� ��������� �� ���������� ������. ������ ����� ������� �����
    uint8 *RemainingData() const;
    /// ���������� ������
    void FreeMemory();
    /// ���������� ��������� �� ������
    uint8 *Data(int pos = 0);
    /// ���������� ������ ������
    uint Size() const;
    /// ���������� true, ���� ��� null-����� (������ �� ��������)
    bool IsEmpty() const;
    /// ���������� true, ���� ��������� ���������
    bool IsEquals(const SimpleMessage *message) const;
    /// ���������� ��������� �� pos-� �������. ������ ��� ����������� �����
    char *String(int pos);

    pString Trace();
    /// �������� �����
    void PutWord(uint data);
    /// �������� ������
    void PutData(uint8 *data, uint length);
    /// �������� ��������� ����������
    void Transmit();

protected:
    /// �������� ����
    void PutByte(uint8 data);
    /// �������� �������� �����
    void PutHalfWord(int16 data);

    void PutDoubleWord(uint64 data);

    void PutHalfWord(uint16 data);
    /// �������� float
    void PutFloat(float data);
    /// ������ ���������� ������
    uint allocated;
    /// ����� ������ ������, ���� 0, ���� ������ �� ��������
    uint8 *buffer;
    /// ������� ������ ������ ��������� �������. ������������ ��� Put
    uint used;
    /// �� ����� ������� ���������. ������������ ��� Take
    uint taken;

    SimpleMessage(const SimpleMessage &) : allocated(0), buffer(0), used(0), taken(0) {};
};


namespace Message
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ��������� ��������� - ��� ������ ����� ������������
    class RequestData : public SimpleMessage
    {
    public:
        RequestData();
    };

    namespace FDrive
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// ��������� ��������� ���� � FPGA
        class LoadToFPGA : public SimpleMessage
        {
        public:
            LoadToFPGA(uint8 ch, uint8 numFile, char *directory);
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// ������ ����� �����
        class FileName : public SimpleMessage
        {
        public:
            FileName(uint8 numFile, char *name);
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// ����� ��������� � ������ � ������� ��������
        class NumDirsAndFiles : public SimpleMessage
        {
        public:
            NumDirsAndFiles(uint numDirs, uint numFiles);
        };
    }

    namespace Set
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// ��������� ����� �������
        class FormWave : public SimpleMessage
        {
        public:
            FormWave(uint8 ch, uint8 form);
        };
    }
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������/��������� �����
class MessageEnableChannel : public SimpleMessage
{
public:
    /// ch : 0 - A, 1 - B
    /// enable : 0 - ���������, 1 - ��������
    MessageEnableChannel(uint8 ch, uint8 enable);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� �������
class MessageSetFrequency : public SimpleMessage
{
public:
    MessageSetFrequency(uint8 ch, uint64 frequency);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ���������
class MessageSetAmplitude : public SimpleMessage
{
public:
    MessageSetAmplitude(uint8 ch, uint64 amplitude);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� �������� ������� �� ������
class MessageSetOffset : public SimpleMessage
{
public:
    MessageSetOffset(uint8 ch, uint64 offset);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ��������� �����������
class MessageFreqMeasure : public SimpleMessage
{
public:
    MessageFreqMeasure(uint frequency);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� � ���������������/�������������� �����
class MessageFDriveMount : public SimpleMessage
{
public:
    /// mount :
    /// 0 - ������ �������������;
    /// 1 - ������ ������ ��������������
    /// 2 - ������ ������������� �� �������
    MessageFDriveMount(uint8 mount);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������ ������� �����
class MessageFDriveFileSize : public SimpleMessage
{
public:
    MessageFDriveFileSize(uint8 numFile, uint size);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� � �������
class MessageLog : public SimpleMessage
{
public:
    MessageLog(char *string);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ������ �������
class MessageStartMode : public SimpleMessage
{
public:
    MessageStartMode(uint8 ch, uint8 mode);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������ � �������
class MessageWriteRegister : public SimpleMessage
{
public:
    MessageWriteRegister(uint8 reg, uint64 data);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ����������� ������
class MessageDebugMode : public SimpleMessage
{
public:
    /// mode == 1/0 - ��������/��������� ����� �������
    MessageDebugMode(uint8 mode);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ����� ���������
class MessageReset : public SimpleMessage
{
public:
    MessageReset();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������������� ���������� ��� ������� ���������
class MessageParameter : public SimpleMessage
{
public:
    MessageParameter(Command::E param, uint8 ch, uint64 value);
};
