#pragma once
#pragma once
#include "common/Messages.h"


namespace Message
{
    // ���� ���������� ������ ������ ������ �� ����������
    class RequestUpgrade : public SimpleMessage
    {
    public:
        RequestUpgrade();
    };

    // ���� ���������� ���������� �������� ������ �������������� �����.
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
