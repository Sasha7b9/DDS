#pragma once
#include "defines.h"
#include "Common.h"
#include "Hardware/CPU.h"
#include "GeneratorSettingsTypes.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace AD9952
{
    void Init();

    void SetFrequency(Chan::E ch, ParamValue frequency);

    void SetAmplitude(Chan::E ch, ParamValue amplitude);

    void SetPhase(Chan::E ch, ParamValue phase);

    /// �����������
    namespace Manipulation
    {
        /// True ��������, ��� ����������� ��������
        extern bool enabled[Chan::Count];
        struct Type
        {
            enum E
            {
                OSK,    ///< ����������� ���������� �� ����������� ��������
                FPGA    ///< ����������� �������������� ����������
            } value;
        };
        extern Type::E type[Chan::Count];
        /// ����������/�������� ������������� ��������� �������� "����"
        void SetEnabled(Chan::E ch, bool enable);
        inline bool IsEnabled(Chan::E ch) { return enabled[ch]; };
        void SetType(Chan::E ch, Type::E type);
        inline Type::E GetType(Chan::E ch) { return type[ch]; };
    };
};
