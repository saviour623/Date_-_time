#ifndef CLI_SYS_TIME_H
#define CLI_SYS_TIME_H
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define hour_12(x, y)(y = x > 12 ? x - 12 : x )
#define UNUSED void(*)(x)
#define ST_LINE "\e[1;1H\e[2J"
#define clr() fprintf(stdout, ST_LINE) /* clear screen */
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
void week_rotate(int, int, int rot[]);
void watch_alarm(struct alarm *);
void time_stamp(int, int, int, int);
char *week_days(int, int rot[]);
int week_set(int , int , int );
char *check_month(int, size_t *);
int day_div(int);

char *week_days(int x, int rot[]){
	if (x == rot[0])
		return "Sun";
	else if (x == rot[1])
		return"Mon";
	else if (x == rot[2])
		return "Tue";
	else if (x == rot[3])
		return "Wed";
	else if (x == rot[4])
		return "Thu";
	else if (x == rot[5])
		return "Fri";
	else if (x == rot[6])
		return "Sat";
	else {
		fprintf(stderr, "[error]: Invalid input for \"day\"!\n");
		exit(EXIT_FAILURE);
	}
}
/* Check momth */
char *check_month(int check_nt, size_t *x){
	switch (check_nt){
	case 1:
		*x = 31;
		return "Jan";
	case 2:
		*x = 28;
		return "Feb";
	case 3:
		*x = 31;
		return "Mar";
	case 4:
		*x = 30;
		return "Apr";
	case 5:
		*x = 31;
		return "May";
	case 6:
		*x = 30;
		return "Jun";
	case 7:
		*x = 31;
		return "Jul";
	case 8:
		*x = 31;
		return "Aug";
	case 9:
		*x = 30;
		return "Sept";
	case 10:
		*x = 31;
		return "Oct";
	case 11:
		*x = 30;
		return "Nov";
	case 12:
		*x = 31;
		return "Dec";
	default:
		fprintf(stderr, "[error]: Invalid choice for month !\n");
		exit(EXIT_FAILURE);
	}
}

/* divide days of month to week days */
int day_div(int day){
	int i;
	for (i = 0; i < 5; i++){
		if (!(day < 7 || day == 7))
			day -= 7;
	}
	return day;
}/* rotate week days position according to change in month */
void week_rotate(int turn, int length, int rot[]){
	int i, temp, j = 0;
	while (j < turn){
		temp = rot[length - 1];
		for (i = length - 2; i >= 0; i--)
			rot[i + 1] = rot[i];
		rot[0] = temp;
		j++;
	}
}
int week_set(int d, int m, int y){
	int key[] = {1, 4, 4, 0, 2, 5, 0, 2, 6, 1, 4, 6};
	if (!(y % 4)){
		key[0] -= 1;
		key[1] -= 1;
	}
	return ((y / 4) + (y + d) + (key[m - 1] + 6)) % 7;
}
/* time function */
void time_clock(struct stop_clock *tp, const int def, const int clock_fmt){

	char *lp;
	lp = " ";
	char *s;
	char *month_str;
	char *day_str;
	size_t month_ays[2];
	size_t day_count = 1; /* Count days in month */
	int year, month;
	int week_check_yr; /* stores last two values of year */
	int day, hour, hour_type;
	int mins, secs;
	int rot[] = {1, 2, 3, 4, 5, 6, 7};

	int i;
	clr();

	printf("Setting time");
	for (i = 0; i < 3; i++){
		putchar('.');
		fflush(stdout);
		usleep(500000);
	}
	putchar('\n');

	if (!(clock_fmt == 12 || clock_fmt == 24)){
		fprintf(stderr, "[error]: Invalid clock type!\n");
		exit(EXIT_FAILURE);
	}
	if (!def){
		secs = tp->secs;
		mins = tp->mins;
		hour = tp->hour;
		day = tp->day;
		day_count = tp->day;
		month = tp->month;
		year = tp->year;
		week_check_yr = year - 2000;
	}
	if (secs < 0 || secs > 59 || mins < 0 || mins > 59){
	error:
		fprintf(stderr, "[error]: Invalid time !\n");
		exit(EXIT_FAILURE);
	}
	if (hour < 0 || hour > 23 || day < 1 || day > 31)
		goto error;
	if (month < 1 || month > 12 || year < 2000)
		goto error;
        /* if default use system time */
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
		week_check_yr = year - 2000;
	}
	int temp = week_set(1, month, week_check_yr);
	week_rotate(temp - 1, 7, rot);
	day = day_div(day);
	day_str = week_days(day, rot);

	for (; month <= 12; month++){
		month_str = check_month(month, month_ays);
		if (!(year % 4)){
			lp = "x ";
			if (month == 2)
				*month_ays = 29;
		}

		for (; hour < 24; hour++){
			hour_type = clock_fmt == 12 ? 0 : hour;
			if (clock_fmt == 12){
				hour_12(hour, hour_type);
			}
			s = (hour > 11) ? "PM" : "AM";
			for(; secs < 60 && mins < 60; secs++){
				clr();
				printf("|%s - %02d, %s - %d%s| %02d : %02d : %02d %s |", day_str, day_count, month_str, year, lp, hour_type, mins, secs, s);
				fflush(stdout);
				if (secs == 59){
					mins += 1;
					secs = -1;
				}
				sleep(1);
			}
			secs = 0, mins = 0;

			if (hour == 23){
				if (day_count == *month_ays){
					week_rotate(day, 7, rot);
					day = 1;
					day_count = 1;
					break;
				}
				if (day_count != *month_ays){
					day += 1, reset(day);
					day_str = week_days(day, rot);
					day_count += 1;
					hour = -1;
				}
			}
		}
		hour = 0;
		if (month == 12){
			year += 1;
			month = 0;
		}
		day_str = week_days(day, rot);
	}
}

void time_stamp(int hour, int in_hr, int mins, int in_min){
	int hr_store = hour;
	int hr_count = 0;
	while (hr_store != in_hr){
		if (hr_store == 23)
			hr_store = -1;
		hr_count += 1;
		hr_store += 1;
	}
	int mins_count = 0;
	int mins_store = mins;
	for (; mins_store != in_min; mins_store++){
		if (mins_store == 59)
			mins_store = -1;
		mins_count += 1;
	}
	printf("[Alarm is set for %02d hours %02d minutes]\n", hr_count, mins_count);
	fflush(stdout); sleep(1);
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

	time_stamp(hour, al->hour, mins, al->mins);
	for (; hour < 24; hour++){
		for (; secs < 60; secs++){
			clr();
			if (hour == al->hour && mins == al->mins){
				printf("[ALARM - %02d : %02d]\n%s\n", hour, mins,  al->msg);
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
