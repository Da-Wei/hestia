#ifndef __INVERTER_H__
#define __INVERTER_H__

struct InverterSensors {
  int waterOutputTemp;
  int waterInputTemp;
  int airTemp;
};

class Inverter {
 public:
  Inverter();
  Inverter(int slaveID);
  bool get(InverterSensors *sensors);
  int start();
  int stop();
  void setSlaveID(int slaveID);
 private:
  int slaveID;
};

#endif
