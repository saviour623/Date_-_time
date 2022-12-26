#ifndef CLI_SYS_TIME_H
#define CLI_SYS_TIME_H
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define hour_12(x, y)(y = x > 11 ? x - 12 : x )
#define UNUSED void(*)(x)
#define ST_LINE "\e[1;1H\e[2J"
#define clr() fprintf(stdout, ST_LINE) //clear screen
#define reset(x) (x = (x > 7) ? 1 : x)

struct stop_clock {
	int secs;
	int mins;
	int hour;
	int year;
	int month;
	int day;
};

struct alarm {
	int mins;
	int hour;
	char *msg;
};
/* prototypes */
void time_clock(struct stop_clock *, const int, const int);
void watch_alarm(struct alarm *);
char *week_days(int, char *);
char *check_month(int, size_t *, char *);
int day_div(int);

char *week_days(int x, char *str){
	switch (x){
	case 4:
		str = "Sun";
		break;
	case 5:
		str = "Mon";
		break;
	case 6:
		str = "Tue";
		break;
	case 7:
		str = "Wed";
		break;
	case 1:
		str = "Thu";
		break;
	case 2:
		str = "Fri";
		break;
	case 3:
		str = "Sat";
		break;
	default:
		fprintf(stderr, "Invalid input for \"day\"!!\n");
		exit(EXIT_FAILURE);
	}
	return str;
}
/* Check momth */
char *check_month(int check_nt, size_t *x, char *s){
	switch (check_nt){
	case 1:
		s = "Jan";
		*x = 31;
		break;
	case 2:
		s = "Feb";
		*x = 28;
		break;
	case 3:
		s = "Mar";
		*x = 31;
		break;
	case 4:
		s = "Apr";
		*x = 30;
		break;
	case 5:
		s = "May";
		*x = 31;
		break;
	case 6:
		s = "June";
		*x = 30;
		break;
	case 7:
		s = "July";
		*x = 31;
		break;
	case 8:
		s = "Aug";
		*x = 31;
		break;
	case 9:
		s = "Sept";
		*x = 30;
		break;
	case 10:
		s = "Oct";
		*x = 31;
		break;
	case 11:
		s = "Nov";
		*x = 30;
		break;
	case 12:
		s = "Dec";
		*x = 31;
		break;
	default:
		fprintf(stderr, "Invalid choice for year\n");
		exit(EXIT_FAILURE);
	}
	return s;
}

/* divide days of month to week days */
int day_div(int day){
	int i;
	for (i = 0; i < 4; i++){
		if (!(day < 7 || day == 7))
			day -= 7;
		else return day;
	}
	return -1;
}
/* time function */
void time_clock(struct stop_clock *tp, const int def, const int clock_type){

	char *lp;
	lp = " ";
	char *s, *month_str;
	char *day_str = "";
	size_t month_ays[2];
	size_t day_count = 1; /* Count days in month */
	int year, month;
	int day, hour, hour_type;
	int mins, secs;

	int i;
	printf("Setting time");
	for (i = 0; i < 3; i++){
		putchar('.');
		fflush(stdout);
		sleep(1);
	}

	if (def == 0){
		secs = tp->secs;
		mins = tp->mins;
		hour = tp->hour;
		day = tp->day;
		day_count = tp->day;
		month = tp->month;
		year = tp->year;
	}/* if default use system time */
	if (def){
		struct tm *p;
		time_t timep;
		timep = time(NULL);
		p = localtime(&timep);

		secs = p->tm_sec;
		mins = p->tm_min;
		hour = p->tm_hour + 1;
		day = p->tm_mday;
		day_count = p->tm_mday;
		month = p->tm_mon + 1;
		year = p->tm_year + 1900;
	}
	hour_type = 0;
	day = day_div(day);
	day_str = week_days(day, day_str);
	month_str = check_month(month, month_ays, month_str);

	for (; month <= 12; month++){
		month_str = check_month(month, month_ays, month_str);
		if (!(year % 4)){
			lp = "lp ";
			if (month == 2)
				*month_ays = 29;
		}
		for (; hour < 24; hour++){
			if (clock_type == 12)
				hour_12(hour, hour_type);
			s = (hour > 11) ? "PM" : "AM";
			for(; (secs, mins) < 60; secs++){
				clr();
				printf("| %s - %s - %d%s| %02d : %02d : %02d %s |", day_str, month_str, year, lp, hour_type, mins, secs, s);
				fflush(stdout);
				if (secs == 59){
					mins += 1;
					secs = -1;
				}
				sleep(1);
			}
			secs = 0, mins = 0;

			if (hour == 23){
				day_count += 1;
				day += 1, reset(day);
				day_str = week_days(day, day_str);

				if (day_count == *month_ays){
					reset(day_count);
					break;
				}
				else hour = -1;
			}
		}
		hour = 0;
		if (month == 12){
			year += 1;
			month = 0;
			reset(day);
		}
		day_str = week_days(day, day_str);
	}
}

void watch_alarm(struct alarm *al){
	int mins;
	int secs;
	int hour;


	struct tm *p;
	time_t timep;
	timep = time(NULL);
	p = localtime(&timep);

	secs = p->tm_sec;
	mins = p->tm_min;
	hour = p->tm_hour + 1;

	int hr_store = hour;
	int hr_count = 0;
	while (hr_store != al->hour){
		if (hr_store == 23)
			hr_store = -1;
		hr_count += 1;
		hr_store += 1;
	}
	int mins_count = 0;
	int mins_store = mins;
	for (; mins_store != al->mins; mins_store++){
		if (mins_store == 59)
			mins_store = -1;
		mins_count += 1;
	}
	printf("[Alarm is set for %02d hours %02d minutes]\n", hr_count, mins_count);
	fflush(stdout); sleep(3);

	for (; hour < 24; hour++){
		for (; secs < 60; secs++){
			clr();
			if (hour == al->hour && mins == al->mins){
				printf("[ALARM - %d : %d]\n %s\n", hr_store, mins_store,  al->msg);
				exit(EXIT_SUCCESS);
			}
			printf("| %02d : %02d : %02d |", hour, mins, secs);
			fflush(stdout);
			sleep(1);
			if (secs == 59){
				mins += 1;
				secs = -1;
			}
			if (mins == 59){
				mins = 0;
				break;
			}
		}
		secs = 0;
		if (hour == 23)
			hour = 0;
	}
}
#endif /* CLI_SYS_TIME_H */
