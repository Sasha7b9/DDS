#pragma once


/*
    ������������ ��� ��������� ���������
*/


struct FloatValue;
struct Key;
class Parameter;
class ParameterValue;


// ��������� ������������ ��� ��������� �������� ���������
class ParameterPainter
{
public:

    ParameterPainter(ParameterValue *param) : parameter(param) { };

    static const int SIZE_BUFFER = 50;
    
    // ���������� ������ �������� ��������� (���� ����������, �� �� ������) ��� ���������������. � ������� indexes ����������� ������� �������� ������������ ����� (� �������������, ��� ����� ����� ����� ������� � ������� �������)
    pString Digits(int8 *indexes);
    
    // ���������� ������ � ��������� ���������
    pString Units(uint lang);

private:
    ParameterValue *parameter;
    FloatValue *value;
    char buffer[SIZE_BUFFER];
    int8 *indexes;

    // �������� � posBuffer ������ ������, ��������������� ����� � ������� indexDigit FloatValue
    void SetChar(int posBuffer, int8 indexDigit);
    void SetChars(int posBuffer, int8 indexDigit, int8 numDigits);

public:
    void DigitsFrequency();
    void DigitsPeriod();
    void DigitsAmplitude();
    void DigitsOffset();
    void DigitsDuration();
    void DigitsDutyRatio();
    void DigitsPhase();
    void DigitsDelay();
    void DigitsDurationRise();
    void DigitsDurationFail();
    void DigitsDurationStady();
    void DigitsDutyFactor();
    void DigitsManipDuration();
    void DigitsManipPeriod();
    void DigitsPacketPeriod();
    void DigitsPacketNumber();
    void DigitsEmpty();
    void DigitsTime();
};


class Tuner
{
public:

    Tuner(Parameter *param);

    // ���������� ������� ����������. ���������� true, ���� ������� ����������
    bool ProcessControl(const Key &key);

private:

    // ��������� �������� � ������� ������e
    void DecreaseInCurrentPosition();

    // ��������� �������� � ������� �������
    void IncreaseInCurrentPosition();

    // ������� �������� ���������� ������
    void SetActivePrev();

    // ������� �������� ��������� ������
    void SetActiveNext();

    // ������ ������� �������� ���� ����� �, ���� ������� ���������� true
    bool ChangedSign();

    // ���������� true, ���� ������ � ������ ������� ����� ���� ���������
    bool PositionMayBeActived(int pos);

    Parameter *parameter;

    static const int NUM_SYMBOLS = 50;

    // ����� �������� ������� �������� �� FloatValue, ��������������� �������� �������� � buffer. ��� ���������� �������� == 255;
    int8 indexes[NUM_SYMBOLS];

    // ����� �������� �������������� �������
    char buffer[NUM_SYMBOLS];

    // ������� ��������� �������
    int positionActive;

    ParameterPainter painter;
};
