#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    void Create(uint8 *data, uint size);
    /// ��������� �� ������ ������
    uint8 *Begin();
    /// ������ ������
    uint Size() const;
    /// ���������� true, ���� ������ ��������� (����� � ��������� �� ����)
    bool IsEquals(Packet *rhs) const;

private:
    /// ������ ������
    static const uint SIZE = 64;
    /// ������ ���� ����������� �����
    static const uint SIZE_FIELD_CRC = 4;
    /// ������ ���� ������ ������
    static const uint SIZE_FIELD_NUMBER_PACKET = 4;
    /// ������ ���� ������ ���������
    static const uint SIZE_FIELD_NUMBER_SUBPACKET = 3;
    /// ������ ���� ������� ������
    static const uint SIZE_FIELD_SIZE_DATA = 1;
    /// ������ ���������� ����
    static const uint SIZE_SERVICE_FIELD = SIZE_FIELD_CRC + SIZE_FIELD_NUMBER_PACKET + SIZE_FIELD_NUMBER_SUBPACKET + SIZE_FIELD_SIZE_DATA;
    /// ������ ���� ������
    static const uint MAX_SIZE_DATA_FIELD = SIZE - SIZE_SERVICE_FIELD;
    /// ���������� ��������� �� ������ ���� ������
    uint8 *DataField();
    /// ���������� ��������� �� ����, ��������� �� offset �� ������ ������
    uint8 *FromBegin(uint offset);
    /// ��������� ��������� ���� ����������
    void FillServiceField(uint sizeData);
    /// �������� ���������� � ���� ������ ������
    void WriteNumberPacket();
    /// �������� ���������� � ���� ������ ���������
    void WriteNumberSubPacket(uint number);
    /// �������� ���������� � ���� ������� ������
    void WriteSizeData(uint size);
    /// �������� ����������� �����
    void WriteCRC();
    /// ���������� ���������� �������. ��� ������ ���������� �� �������.
    static uint transcievedPackets;

    struct Data
    {
        uint numberPacket;
        uint numberSubPacket;
        uint size;
        uint8 data[SIZE - 3 * 4];
    } data;
};
