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
    // mode : 0 - ������������ ���������� device; 1 - ������������ ���������� panel
    class PortionUpdate : public SimpleMessage
    {
    public:
        PortionUpdate(int mode, int portion);
    };

    // ���� ���������� device ��� ������ ���������� �� ������
    class StartMainApplication : public SimpleMessage
    {
    public:
        StartMainApplication();
    };
}
