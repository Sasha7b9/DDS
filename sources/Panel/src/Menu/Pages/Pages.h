#pragma once
#include "common/Common.h"
#include "Menu/MenuItems.h"


class Parameter;


struct PageMain
{
    static Page *self;

    // ���������� true, ���� ������� ������ ����������� (� ������� ������������ ��������� �������)
    static bool OnSubPageTuneChannels();
};


struct PageSignals
{
    static void Init();

    static void SetCurrentChanenl(Chan::E ch);

    static void OnPress_Channel(bool);

    static void OnPress_Form(bool);

    static void SetForm(TypeForm::E form);
};


class PageFrequencyCounter
{
public:
    // ������������ ���������� �������� ���������� ������������ � ������������ � �����������
    static void WriteRegisterRG9();

    static Page *self;
};


class PageService
{
public:

    static void OnPress_Reset();

    static Page *self;
};


class PageLoadForm
{
public:
    static Page *self;
};


struct PageTuneParameter
{
    static Page *self;

    // ������������� �������� ��� ��������������
    static void SetParameter(Parameter *);

    // ���������� ����� ����� ��������
    static void SetModeEntering();

    // �������� ����� ����� ��������
    static void ResetModeEntering();

    // ��� ������� ����� �������� Tuner ��� ������� ������ "��������"
    static void CallbackOnButtonCancel();

    // ��� ������� ����� �������� Tuner ��� ������� ������ "���������"
    static void CallbackOnButtonApply();

    static bool IsOpened();
};


struct PageDebug
{
    static Page *self;

    // �������� ����������� �������� �������
    static void Enable();

    struct PageRegisters
    {
        static void Draw();

    private:
        // �������� ��������
        static void DrawRegisters(int x, int y);

        static void DrawInputWindow();
    };

    struct SubRange
    {
        static Page *self;
    };

    struct Colors
    {
        static void Init();

        static Page *self;

        struct ChanA
        {
            static Page *self;
        };

        struct ChanB
        {
            static Page *self;
        };

        struct Menu
        {
            static Page *self;
        };
    };

    struct Calibartion
    {
        static Page *self;
    };

    struct _Calibration
    {
        struct PageA
        {
            static Page *self;
        };

        struct PageB
        {
            static Page *self;
        };

        static void OnPress_OffsetAD9952(Chan::E ch, bool enter, KoeffCal::E koeff);

        static void OnPress_DDS(Chan::E ch, bool enter, KoeffCal::E koeff);

        static void OnPress_AmplitudeAD9952(Chan::E ch, bool enter, KoeffCal::E koeff);

        static void WriteKoeffCal(Chan::E ch, KoeffCal::E koeff);
    };
};
