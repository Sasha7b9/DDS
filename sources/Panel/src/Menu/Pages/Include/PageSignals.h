#pragma once
#include "Menu/MenuItems.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct KoeffCal
{
    enum E
    {
        AD9952_NEG,     ///< ��� �������� ���������� ���, ���������� ��� �������� -5� ��������������� �������
        AD9952_ZERO,    ///< ��� �������� ���������� ���, ���������� ��� �������� 0� ��������������� �������
        AD9952_POS,     ///< ��� �������� ���������� ���, ���������� ��� �������� +5� ��������������� �������
        AD9952_AMPL,    ///< ����� ���� ��������� ������������ ������������ � ��������� ��������������� ������� : ����������_��� = ������������_��� * (1 + AD9952_AMPL / 10000)
        DDS_MAX,        ///< ���, ��������������� ������ +5� DDS
        DDS_MIN,        ///< ���, ��������������� ������ -5� DDS
        DDS_OFFSET,     ///< ���, �������������� �������� ������ �������� DDS
        Number
    } value;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PageSignals
{
public:
    static void Init();

    static void OnPress_Channel(bool);

    static void OnPress_Form(bool);

    static Page *pointer;

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageLoad
    {
    public:
        static Page *pointer;
    };

    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    class PageCalibration
    {
    public:

        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        class PageA
        {
        public:
            static Page *pointer;
        };

        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        class PageB
        {
        public:
            static Page *pointer;
        };

        static void OnPress_OffsetAD9952(Chan ch, bool enter, KoeffCal::E koeff);

        static void OnPress_AmplitudeAD9952(Chan ch, bool enter, KoeffCal::E koeff);

        static void WriteKoeffCal(Chan ch, KoeffCal::E koeff);
    };
};
