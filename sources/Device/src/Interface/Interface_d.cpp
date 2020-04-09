#include "defines.h"
#include "common/Messages.h"
#include "common/Transceiver.h"
#include "Handlers_d.h"
#include "Interface_d.h"
#include "FDrive/FDrive_d.h"
#include "Generator/Generator_d.h"
#include "Generator/FPGA.h"
#include "Hardware/CPU.h"
#include "Hardware/Timer.h"
#include "Hardware/HAL/HAL.h"
#include "FreqMeter/FreqMeter_d.h"
#include "Settings/CalibrationSettings.h"
#include "Utils/Debug.h"
#include "Utils/Queue.h"
#include "Utils/StringUtils.h"
#include "common/Command.h"
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

    int size = 0;

    if (HAL_SPI1::Receive(&size, 4, 10))                                                           // ����� ������ ������������ ���������
    {
        SimpleMessage first;              // ���� ��������� ������ ���������
        SimpleMessage second;             // ���� ��������� ������ ���������

        uint timeout = size > 100U ? 200U : 10U;

        if (first.AllocateMemory(size))
        {
            if (HAL_SPI1::Receive(first.Data(), first.Size(), timeout))                            // ��������� ������
            {
                if (HAL_SPI1::Transmit(&size, 4, timeout))                                         // ������� ��� ������
                {
                    if (HAL_SPI1::Transmit(first.Data(), first.Size(), timeout))                   // � ������
                    {
                        if (HAL_SPI1::Receive(&size, 4, 10))
                        {
                            if (second.AllocateMemory(size))                                    // ������ ��� ��������� ����� ��������� � ���� �����
                            {
                                if (HAL_SPI1::Receive(second.Data(), second.Size(), timeout))      // ��� � ������
                                {
                                    size = second.Size();

                                    if (HAL_SPI1::Transmit(&size, 4, timeout))
                                    {
                                        if (HAL_SPI1::Transmit(second.Data(), second.Size(), timeout))
                                        {
                                            if (second.IsEquals(&first))                        // ���������, ������� �� ��� �������� ���������
                                            {
                                                DHandlers::Processing(&first);
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
