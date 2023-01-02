#include "CLI_sys_time.h"

int main(){
	/* Alarm */
	struct alarm k;
	k.mins = 26;
	k.hour = 14;
	k.msg = "Message";
	/* watch_alarm(&k); */

        /* Date and time */
	struct stop_clock p = {00, 00, 00, 2000, 1, 1};
	time_clock(&p, 0, 24);
	return 0;
}
