#include <ModbusMaster.h>

#include "inverter.h"

unsigned long delayCounter;

void displayMenu() {
  Serial.println('Hestia');
  Serial.println('======');
  Serial.println('1. Status');
  Serial.println('2. Switch Inverter On/Off');
}

void setup()
{
  delayCounter = millis()
}

void loop()
{
  InverterSensors sensors;

  if ( ( millis() - delayCounter ) >= 10000 ) {
    // Request inverter for values
    sensors = inverter.get();

    // Store values with timestamp
    // tstamp = getTimestamp();
    // storeData(tstamp, sensors);
    
    // Reset delayCounter
    delayCounter = millis();
  }

  // Analyse and send action(s)
  
  // Answer operator's request
  if ( Serial.avalaible() > 0 ){
    cmd = Serial.read();
    switch(cmd) {
    case '\n':
      displayMenu();
    }
  }
}
