#pragma once
#include "InputWindowStruct.h"
#include "Hardware/Controls.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���� �������������� ���������� �������� ���������
class InputWindow
{
public:
    static void Init();

    static void Draw();

    static void KeyLeft();

    static void KeyRight();

    static void KeyEnter();

    static void ProcessContorl(Control control);

    /// ��������� ��������� allowParameters ���������� � ������������ � ����������� ��� ������ ����� ������� � ������
    static void FillAllowParameters(Chan ch, Wave::Form form, AllowableParameters *allowParameters);

private:
    static void DrawAmplitude(int x, int y);

    static void DrawFrequency(int x, int y);

    static void DrawOffset(int x, int y);

    static void DrawPhase(int x, int y);

    static void DrawDelay(int x, int y);

    static void DrawPeriod(int x, int y);

    static void DrawDutyRatio(int x, int y);

    static void DrawDuration(int x, int y);

    static void DrawDigits(int x, int y);

    static void DrawDepthModulation(int x, int y);

    static void DrawPolarity(int x, int y);

    static void DrawDurationRise(int x, int y);

    static void DrawDurationFall(int x, int y);

    static void DrawDurationStady(int x, int y);

    static void DrawDutyFactor(int x, int y);
    /// �����, ��� �������� �������� ��������
    static Chan              chan;
    /// ����� �������, ��� �������� �������� ��������
    static Wave::Form        form;
    /// ��������, �������� �������� ��������
    static Wave::Parameter   m_param;

public:
    class Struct
    {
    public:

        void Fill(Chan ch, Wave::Form form, Wave::Parameter param);

        char *StringValue();

        float Value();

        void DrawInputField(int x, int y);

        void KeyLeft();

        void KeyRight();

        void RegLeft();

        void RegRight();

        void PressKey(Control key);

        void SaveValue();

        char   inputBuffer[NUM_DIGITS + 1];
        char   prevBuffer[NUM_DIGITS + 1];
        int8   posComma;            ///< ����� ������ ���������� �������� �������
        int8   prevPosComma;
        int8   hightLightDigit;     ///< ������� ������������� ����������
        uint8  order       : 3;
        uint8  param       : 4;     ///< ������������ ���� Wave::Parameter
        uint8  sign        : 2;     ///< ������������ ���� SignValue
        uint   allow       : 1;     ///< ���� 1, �������� �������� ��� ������� �������
        uint   numLockMode : 1;     ///< 1, ����� ���������� ��������� (0...9) ���� ��������

    private:
        void IncreaseDigit(int num);
        void DecreaseDigit(int num);
        /// ���������� true, ���� ��� ����� ����� �� num ����� ����. � num ����
        bool All0LeftWithThis(int num);
        /// ���������� true, ���� ��� ����� ����� � ��� �������� ���������
        bool All9LeftWithThis(int num);
        /// ���������� true, ���� ����� ���� ������������ ������� � ��� ��������� � ����� �������
        bool Only1InThis(int num);
        /// �������� ��� ������� ������
        void ShiftToRight();
        /// ����� ���� �������� �����
        void ShiftToLeft();
        /// ���������� true, ���� ���� ������ ���� ������� ������ �����
        bool OnlyOneRigthDigit();
        /// ���������� ����� �� �������
        int ValueBeforeComma();
        /// ���������� ����� ����� �������
        float ValueAfterComma();
        /// ����������� ������� �� ��������� �� �����������
        void IncreaseOrder();
        /// ��������������� ����� ���������� ��������
        void RestoreValue();
        /// ��������� iws �� inputBuffer
        void FillIWSfromInputBuffer();
        /// ������� ������� �������� � ���������
        void SendIWStoGenerator();
    };

    static Struct m_iws;
};
