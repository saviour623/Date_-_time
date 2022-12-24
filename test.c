#include "main.h"
int main(void){
	struct stop_clock string;
	string.secs = 0;
	string.mins = 13;
	string.hour = 1;
	string.month = 12;
	string.year = 2022;
	string.day = 24;
	time_clock(&string, 0);
	return 0;
}
