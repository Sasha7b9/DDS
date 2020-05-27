#pragma once


struct TypeForm
{
    enum E
    {
        Sine,           // �����
        RampPlus,       // ����+
        RampMinus,      // ����-
        Triangle,       // �����������
        Meander,        // ������
        Impulse,        // ��������
        PacketImpuls,   // ����� ���������
        Free,           // ������������ ������
        Count
    };
};


struct FloatValue
{
    explicit FloatValue(float v);

    // ���� �������� �� ���������� �������������. ��� ���� ������ �������� ����� ���� ���� ("+" ��� "-"), ������� ����� ���������� �� ����� ������ ("."),
    // � order ��������, �� ������� ����� ��������� �������� ����� (3 - �������� �� 1000, -3 - ��������� �� 1000)
    explicit FloatValue(const char *const buffer, int order = 0);

    void FromUnits(int units, uint mUnits, uint uUnits, uint nUnits, int sign);
    void FromFloat(float v);
    void FromUINT64(uint64 v) { value = v; }
    void FromString(const char * const buffer, int order);

    float ToFloat() const;
    uint64 ToUINT64() const { return value; }

    void Div(uint div);
    void Mul(uint mul);
    void Add(FloatValue value);
    void Sub(FloatValue value);

    void SetSign(int sign);

    // ���������� ����
    int Sign() const;

    // ���������� ����� �����
    int Integer() const;
      
    // ���������� ���������� ���������� � ������� �����
    int FractNano() const;

    uint64 Abs() const;

    bool operator<(const FloatValue &);
    bool operator>(const FloatValue &);
    bool operator<=(const FloatValue &);
    bool operator>=(const FloatValue &);
    bool operator==(const FloatValue &);

private:

    uint64 value;       // �������� ��������� � �������� ��������� "����". ������������� � "1" ������� ��� ��������, ��� ����� �������������
};
