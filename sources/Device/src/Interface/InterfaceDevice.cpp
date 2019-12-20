#include "defines.h"
#include "log.h"
#include "Message.h"
#include "Transceiver.h"
#include "HandlersDevice.h"
#include "InterfaceDevice.h"
#include "FDrive/FDriveDevice.h"
#include "Generator/Generator_d.h"
#include "Generator/FPGA.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Hardware/Modules/SPI.h"
#include "FreqMeter/FreqMeter.h"
#include "Settings/CalibrationSettings.h"
#include "Utils/Debug.h"
#include "Utils/Queue.h"
#include "Utils/StringUtils.h"
#include "Command.h"
#include "structs.h"
#include <cstdlib>


namespace Interface
{
    /// ��������� ��������� � ������� ��������. ���� ������� ���������, ��������� ��������� � ������� ���������� false
    bool AddMessageForTransmit(SimpleMessage *message);
    /// ������� ���������, ��������� ��������
    Queue outbox;
    /// ��������� �������� ��������, ��� ��� ������� �������� � ������ ��� ���������� ������������ ��������
    uint freqForSend = MAX_UINT;
};



Queue &Interface::GetOutbox()
{
    return outbox;
}


void Interface::ResetFreqForSend()
{
    freqForSend = MAX_UINT;
}


void Interface::Update()
{
    CPU::SetReady();

    uint size = 0;

    if (SPI1_::Receive(&size, 4, 10))                                                           // ����� ������ ������������ ���������
    {
        SimpleMessage first;              // ���� ��������� ������ ���������
        SimpleMessage second;             // ���� ��������� ������ ���������

        uint timeout = size > 100U ? 200U : 10U;

        if (first.AllocateMemory(size))
        {
            if (SPI1_::Receive(first.Data(), first.Size(), timeout))                            // ��������� ������
            {
                if (SPI1_::Transmit(&size, 4, timeout))                                         // ������� ��� ������
                {
                    if (SPI1_::Transmit(first.Data(), first.Size(), timeout))                   // � ������
                    {
                        if (SPI1_::Receive(&size, 4, 10))
                        {
                            if (second.AllocateMemory(size))                                    // ������ ��� ��������� ����� ��������� � ���� �����
                            {
                                if (SPI1_::Receive(second.Data(), second.Size(), timeout))      // ��� � ������
                                {
                                    size = second.Size();

                                    if (SPI1_::Transmit(&size, 4, timeout))
                                    {
                                        if (SPI1_::Transmit(second.Data(), second.Size(), timeout))
                                        {
                                            if (second.IsEquals(&first))                        // ���������, ������� �� ��� �������� ���������
                                            {
                                                Handlers::Processing(&first);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    CPU::SetBusy();
}


bool Interface::AddMessageForTransmit(SimpleMessage *message)
{
    SimpleMessage *clone = message->Clone();

    if (!outbox.Push(clone))
    {
        delete clone;
        /// \tood ����� ����� �������� �� ������. ������� ���, ����� ��������� �� ������� �������� ����������������� �������� - �������� �� � ������� ���� ����� ��� ��� ����� (����������)
        // LOG_ERROR("������� �����������");
        return false;
    }

    return true;
}


void SimpleMessage::Transmit()
{
    Interface::AddMessageForTransmit(this);
}
