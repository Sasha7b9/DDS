#pragma once


namespace SCPI
{
    namespace Error
    {
        namespace Syntax
        {
            /// ������������ ���������
            void Invalid();
            /// ��������� ��������� � ������ �������
            void MissingColon();
        }

        /// ����������� �������
        void UnknownCommand();
    }
}
