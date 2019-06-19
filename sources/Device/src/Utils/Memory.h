#pragma once


namespace Memory
{
    void Init();
    /// �������� ������� ������ �������� size ���� � ��������� ��������� �� ����
    void *Allocate(uint size);
    /// ����������� ����� ���������� ������� ������
    void Free(void *address);
};
