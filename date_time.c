#include "main.h"
int main(void){
	struct stop_clock t;
//	time_clock(&t, 1, 12);
	struct alarm string;
	string.mins = 45;
	string.hour = 00;
	string.msg = "It's time to go to church";
	watch_alarm(&string);
	return 0;
}
