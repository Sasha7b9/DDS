#include "defines.h"
#include "log.h"
#include "Message.h"
#include "Transceiver.h"
#include "Handlers_d.h"
#include "Interface_d.h"
#include "FDrive/FDrive_d.h"
#include "Generator/Generator_d.h"
#include "Generator/FPGA.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Hardware/Modules/SPI.h"
#include "FreqMeter/FreqMeter_d.h"
#include "Settings/CalibrationSettings.h"
#include "Utils/Debug.h"
#include "Utils/Queue.h"
#include "Utils/StringUtils.h"
#include "Command.h"
#include "structs.h"
#include <cstdlib>


uint  DInterface::freqForSend = MAX_UINT;
Queue DInterface::outbox;


Queue &DInterface::GetOutbox()
{
    return outbox;
}


void DInterface::ResetFreqForSend()
{
    freqForSend = MAX_UINT;
}


void DInterface::Update()
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


bool DInterface::AddMessageForTransmit(SimpleMessage *message)
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
    DInterface::AddMessageForTransmit(this);
}
