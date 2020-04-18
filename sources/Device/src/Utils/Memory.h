#pragma once


struct Memory
{
    static void Init();
    // �������� ������� ������ �������� size ���� � ��������� ��������� �� ����
    static void *Allocate(uint size);
    // ����������� ����� ���������� ������� ������
    static void Free(void *address);
};
