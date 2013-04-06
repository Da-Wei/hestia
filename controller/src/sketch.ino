#include <Wire.h>
#include "inverter.h"
#include "DS1307.h"

unsigned long delayCounter;

char dt[7];
DS1307 clock = DS1307();
Inverter inverter = Inverter();
InverterSensors sensors;

void displayMenu() {
	Serial.println("Hestia");
	Serial.println("======");
	Serial.println("1. Status");
	Serial.println("2. Switch Inverter On/Off");
	Serial.println("3. Show date");
	Serial.println("4. Set date");
	Serial.println("");
	Serial.print("==> ");
}

void setup()
{
	Wire.begin();
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
			case '4':
				Wire.beginTransmission(0x68); // activate DS1307
				Wire.write(0); // where to begin
				Wire.write(0x00);          //seconds
				Wire.write(0x03);          //minutes
				Wire.write(0x80 | 0x01);    //hours (24hr time)
				Wire.write(0x06);  // Day 01-07
				Wire.write(0x01);  // Date 0-31
				Wire.write(0x05);  // month 0-12
				Wire.write(0x09);  // Year 00-99
				Wire.endTransmission();
				break;
			case '\r':
			case 'h':
				displayMenu();
				break;
			case '1':
				Serial.print("Water Output Temperature : ");
				Serial.println(sensors.waterOutputTemp);
				break;
			case '3':
				clock.getDateTime(dt);

				// hours, minutes, seconds

				Serial.print("The time is "); 
				if (dt[2] < 10) Serial.print("0");
				Serial.print(dt[2],HEX);    
				Serial.print(":");
				if (dt[1] < 10) Serial.print("0");
				Serial.print(dt[1], HEX);
				Serial.print(":");
				if (dt[0] < 10) Serial.print("0");
				Serial.println(dt[0], HEX);

				// use MM-DD-YYYY

				Serial.print("The date is "); 
				if (dt[5] < 10) Serial.print("0");
				Serial.print(dt[5],HEX);    
				Serial.print("-");
				if (dt[4] < 10) Serial.print("0");
				Serial.print(dt[4], HEX);
				Serial.print("-");
				Serial.print("20");
				if (dt[6] < 10) Serial.print("0");
				Serial.println(dt[6], HEX);
				Serial.println();
				break;
		}
	}
}
