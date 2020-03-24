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

    static bool Handler(SimpleMessage *msg);
};


struct FileRequests
{
    /// ������� ������ �� �����
    static void SendRequestForString(const String *name, int numString);
};
