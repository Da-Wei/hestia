#ifndef __DS1307_H__
#define __DS1307_H__

class DS1307 {
	public:
		DS1307();
		bool setTime(char hours, char minutes, char seconds);
		bool setDate(char day, char month, int year);
		bool getDateTime(char *buffer);
	private:
		void init();
};

#endif __DS1307_H__
