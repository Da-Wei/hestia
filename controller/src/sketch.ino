#include "inverter.h"

unsigned long delayCounter;

Inverter inverter = Inverter();

void displayMenu() {
  Serial.println('Hestia');
  Serial.println('======');
  Serial.println('1. Status');
  Serial.println('2. Switch Inverter On/Off');
}

void setup()
{
  delayCounter = millis();
  inverter.setSlaveID(2);
}

void loop()
{
  InverterSensors sensors;
  char cmd;

  if ( ( millis() - delayCounter ) >= 10000 ) {
    // Request inverter for values
    inverter.get(&sensors);

    // Store values with timestamp
    // tstamp = getTimestamp();
    // storeData(tstamp, sensors);
    
    // Reset delayCounter
    delayCounter = millis();
  }

  // Analyse and send action(s)
  
  // Answer operator's request
  if ( Serial.available() > 0 ){
    cmd = Serial.read();
    switch(cmd) {
    case '\n':
      displayMenu();
    }
  }
}
