#pragma once
#include "common/Messages.h"


class String;



class File
{
public:
    File();
    ~File();
    /// ��������� ����
    void Open(int num);
    /// ��������� ���� � ����������� ������
    void Close();
};
