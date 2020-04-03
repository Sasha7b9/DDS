#pragma once
#pragma once
#include "common/Messages.h"


namespace Message
{
    // ���� ���������� ������ ������ ������ �� ����������
    class RequestUpdate : public SimpleMessage
    {
    public:
        RequestUpdate();
    };

    // ���� ���������� ���������� �������� ������ �������������� �����
    class PortionUpdateDevice : public SimpleMessage
    {
    public:
        PortionUpdateDevice(int portion);
    };

    // ���� ���������� device ��� ������ ���������� �� ������
    class StartMainApplication : public SimpleMessage
    {
    public:
        StartMainApplication();
    };
}
