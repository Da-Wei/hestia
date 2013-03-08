#ifndef __INVERTER_H__
#define __INVERTER_H__

struct InverterSensors {
  int waterOutputTemp;
  int waterInputTemp;
  int airTemp;
};

class Inverter {
 public:
  InverterSensors get(void);
  int start(void);
  int stop(void);
};

#endif
