#pragma once


struct CPU
{
    static void Init();
    /// ���������� �� PA2 ������� ����, ��� ��������� �����
    static void SetBusy();
    /// ���������� �� PA2 ������� ����, ��� ��������� ��������
    static void SetReady();

private:

    static void InitGPIOS();
};
