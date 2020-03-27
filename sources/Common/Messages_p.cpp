#include "defines.h"
#include "Messages_p.h"
#include "Settings/CalibrationSettings.h"


Message::LoadFormDDS::LoadFormDDS(uint8 ch, uint16 data[PGenerator::DDS_NUM_POINTS]) : SimpleMessage(2 + PGenerator::DDS_NUM_POINTS * 2, Command::LoadFormDDS)
{
    PutByte(ch);
    PutData(reinterpret_cast<uint8*>(data), sizeof(data[0]) * PGenerator::DDS_NUM_POINTS);
}


Message::CalibrateSet::CalibrateSet(uint8 ch, uint8 signal, uint8 range, uint8 parameter) : SimpleMessage(7, Command::CalibrationSet)
{
    PutByte(ch);
    PutByte(signal);
    PutByte(range);
    PutByte(parameter);
    PutHalfWord(*setCal.GetK(ch, signal, range, parameter));
}


Message::CalibrateLoad::CalibrateLoad(uint8 ch, uint8 signal, uint8 range, uint8 parameter) : SimpleMessage(7, Command::CalibrationLoad)
{
    PutByte(ch);
    PutByte(signal);
    PutByte(range);
    PutByte(parameter);
    PutHalfWord(*setCal.GetK(ch, signal, range, parameter));
}
