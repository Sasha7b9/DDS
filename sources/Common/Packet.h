#pragma once


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    +------------------------------------------------+-------------+
    |             ��������� ����                     | ���� ������ |
    +--------------+-----------------+---------------+-------------+
    | ����� ������ | ����� ��������� | ������ ������ |   ������    |
    +--------------+-----------------+---------------+-------------+
    |    0...3     |      4...7      |   8...11      | 12...63     |
    +--------------+-----------------+---------------+-------------+

    ������ ����� �������� �� �� ���� ��� ������. � ���� "������ ������" ������� ���������� ������
*/

class Packet
{
public:
    Packet();
    /// ������ ����� �� ������������ ������
    void CreateNew(uint8 *data, uint size);
    /// ��������� �� ������ ������
    uint8 *Begin();
    /// ������ ������
    uint Size() const;
    /// ���������� true, ���� ������ ��������� (����� � ��������� �� ����)
    bool IsEquals(Packet *rhs) const;
    /// ���������� ��������� �� ������ ���� ������
    uint8 *DataField();

    void Log() const;

private:
    /// ��������� ��������� ���� ����������
    void FillServiceField(uint sizeData);
    /// ���������� ���������� �������. ��� ������ ���������� �� �������.
    static uint transcievedPackets;

    /// ������ ������
    static const uint SIZE = 64;
    /// ������������ ������ ���� ������
    static const uint MAX_SIZE_DATA_FIELD = SIZE - 2 * sizeof(uint);

    struct Data
    {
        uint numberPacket;
        uint size;
        uint8 data[MAX_SIZE_DATA_FIELD];
    } data;
};
