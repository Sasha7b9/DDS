#pragma once


class SimpleMessage;


class Updater
{
public:

    static const uint MAIN_PROGRAM_START_ADDRESS = 0x8020000;

    // true, ���� ����� ��������� ��������� ����������
    static bool NeedUpgrade();

    // ������ ��������� ����������
    static void Upgrade();

    // ���������� ����������� ������
    static void Handler(SimpleMessage *);
};
