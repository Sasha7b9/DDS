#pragma once


class Memory
{
public:

    void Init();
    /// �������� ������� ������ �������� size ���� � ��������� ��������� �� ����
    void *Allocate(uint size);
    /// ����������� ����� ���������� ������� ������
    void Free(void *address);
};
