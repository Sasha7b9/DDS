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

    // ���� ���������� ���������� �������� ������ ���������� ����� �������� device
    class PortionUpgradeDevice : public SimpleMessage
    {
    public:
        PortionUpgradeDevice(int portion);
    };

    // ���� ���������� ���������� �������� ������ ���������� ����� �������� panel � ����� ������� ������
    class PortionUpgradePanel : public SimpleMessage
    {
    public:
        PortionUpgradePanel(int num, int portion, uint8 *data, int size);
    };

    // ���� ���������� device ��� ������ ���������� �� ������
    class StartMainApplication : public SimpleMessage
    {
    public:
        StartMainApplication();
    };
}
