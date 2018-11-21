#pragma once
#include "Message.h"
#include "RawData.h"
#include "Utils/Buffer.h"


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

    /// ��� ����� ��������� �� ����������
    static void Update();
    /// ������� � ��������� ������
    static void Send(uint8 *buffer, uint size);

    static void Send(const Buffer &buffer);

    static void Send(RawData *message);

private:
    /// ��������� ������� recv
    static bool Run(Message *message);
};
