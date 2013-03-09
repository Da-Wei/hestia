#include "inverter.h"

unsigned long delayCounter;

Inverter inverter = Inverter();
InverterSensors sensors;

void displayMenu() {
  Serial.println("Hestia");
  Serial.println("======");
  Serial.println("1. Status");
  Serial.println("2. Switch Inverter On/Off");
  Serial.println("");
  Serial.print("==> ");
}

void setup()
{
  Serial.begin(9600);
  delayCounter = millis();
  inverter.setSlaveID(2);
}

void loop()
{
  char cmd;

  if ( ( millis() - delayCounter ) >= 10000 ) {
    // Request inverter for values
    if(inverter.get(&sensors)) 
      {
	Serial.println("Get sensors...");
      }
    
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
    case '\r':
    case 'h':
      displayMenu();
      break;
    case '1':
      Serial.print("Water Output Temperature : ");
      Serial.println(sensors.waterOutputTemp);
      break;
    }
  }
}
