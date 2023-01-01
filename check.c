#include "CLI_sys_time.h"

int main(){
	struct stop_clock p = {54, 59, 23, 2023, 12, 31};
	time_clock(&p, 0, 12);
	return 0;
}
