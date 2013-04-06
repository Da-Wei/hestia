#include <Wire.h>
#include "DS1307.h"

DS1307::DS1307()
{

}

void DS1307::init() {
	Wire.beginTransmission(0x68);
	Wire.write(0);
	Wire.endTransmission();	
}
bool DS1307::setTime(char hours, char minutes, char seconds) {
	
}

bool DS1307::setDate(char day, char month, int year) {
	
}

bool DS1307::getDateTime(char *buffer) 
{
	char i=0;
	this->init();
	Wire.requestFrom(0x68, 7);    // request 6 bytes from slave device #2

	while(Wire.available())    // slave may send less than requested
	{
		buffer[i] = Wire.read();    // receive a byte as character
		i++;
	}
	if (i != 6) return false;
	return true;
}

