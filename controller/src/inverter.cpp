#include "inverter.h"

Inverter::Inverter()
{

}

Inverter::Inverter(int slaveID)
{
  this->slaveID = slaveID;
}

void Inverter::setSlaveID(int slaveID)
{
  this->slaveID = slaveID;
}

bool Inverter::get(InverterSensors *sensors)
{
  sensors->waterOutputTemp = 40;
  sensors->waterInputTemp = 15;
  sensors->airTemp = 6;
  return true;
}

int Inverter::start()
{
  return 0;
}

int Inverter::stop()
{
  return 0;
}
