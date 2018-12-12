#pragma once
#include "defines.h"


/*
    ����� ����������� ������������ ��� ��������������� ���������/������������ ������ �� ����
*/

class Buffer
{
public:
    Buffer(uint size);
    ~Buffer();
    bool ReSize(uint size);
    void *Data();
    uint   Size() const;
private:
    void Allocate(uint size);
    void Free();
    void *buffer;
    uint size;
};
