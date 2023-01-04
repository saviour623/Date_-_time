# <div align="center"> CLI_SYS_TIME.H </div>
This is a Simple C program that sets and run time/date independently on the CLI using user-defined time or system default time(local time) as specified by the user.

` Note: ` In order to use this features, this header file must be present in the current directory and manually added to the C program as a user defined header.

### STOP_CLOCK
#### Prototype:
  ``` C
struct stop_clock {
	int secs;
	int mins;
	int hour;
	int year;
	int month;
	int day;
	};
 ```
Time setting is collected using a predefined struct `stop_clock` of format :-
``` C
int secs;
int mins;
int hour;
int year;
int month;
int day;
```
<div align="left"> A variable of type "struct stop_clock" is defined and it's address is passed as an argument to time_clock function. </div>

## TIME_CLOCK
``` C
 void time_clock(struct stop_clock *, const int, const int);
```

The time_clock function accepts three arguments of types ` struct * `, ` const int ` and ` const int `.

The first argument is a pointer to struct, which points to the address of a predefined struct type (stop_clock) variable which must be passed as an argument when time_clock is called.

Struct members could be initialized with specific user-defined time and date or could be left uninitialized, i.e if user prefers to use the system's default time. This is specified by passing ` 0 ` (initialize user-defined time) or ` 1 ` (initialize system time which uses default device local time) as the next argument of time_clock function.

` Note :- `
* The value of the above argument must either be ` 1 ` or ` 0 ` else behaviour of time_clock will be undefined.
***
The last argument of the time_clock, specifies the clock format. This program only identifies two clock format, ` 12hr & 24hr clock format `, which could be specified by passing either ` 12 ` or ` 24 ` to the parameter.

` Note :- `
*	Any other value aside the ones specified above will incur an error message and terminate the program.
*	The time_clock considers leap years in date. In output, the character, ` x ` is attached to the end of the value, year, to signify that it is a leap year.
*	The user-defined value for year must range from ` 2000, ... `. Threfore, any input below 2000 will incur program error and terminate consecutively.
***

``` C {
      /*USAGE*/
      struct stop_clock var;
      time_clock(&var, 1, 12); /* System defined 12hr clock */

      /* or */
      var->secs = 0;
      var->mins = 0;
      var->hour = 0;
      var->year = 2000;
      var->month = 1;
      var->day = 1;
      time_clock(&var, 0, 24); /* User-defined 24hr clock */
      }
```
### OTHER FUNCTIONS

 #### WEEK_ROTATE
``` C
void week_rotate(int, int, int rot[]);
```
This function basically rotates an array of integers. week_rotate is used to reshuffle week_days according to changes in month. e.g if tuesday is the last day of january, i.e, 31st, the array of week days(1...7) will be rotated to make the next day(wednesday) the 1st day of the week of the next month.
*     First argument of the week_rotate function takes in ` n ` number of times to rotate array (usually the last day of the month in week positíon).
*     The second argument of the function takes in the length of the array.
*     The last argument takes in the address of the array (array of weeks) to be rotated.
***

 #### DAY_DIV
```C
int day_div(int);
```
      This function takes in an argument, precisely day in month(1...28/29/30/31), and returns the value of day in week(1...7).

` Note: ` Interpretation of the returned value depends on the first day of the week of the month.

####  WEEK_SET
``` C
int week_set(int , int , int );
```
     The week_set function takes in three argumemt in the order of; ` day(1...28/29/30/,31) `, ` month(1...12) ` and ` year(last two digit of year starting from year 2000) ` and returns the current day of the wéek of the provided date.

#### WEEK_DAY
``` C
char *week_days(int, int rot[]);
```
     The week_days function takes in two argument in order of; ` day in weeks(1...7) `, ` array of weeks arranged according to first day of the week of the month ` and returns a pointer to the  week day in strings.

#### CHECK_MONTH
``` C
char *check_month(int, size_t *);
```
     This function takes the position of month(1...12) and the address of an empty pointer and returns a pointer to the current month in strings. Also the empty pointer passed through the function  will be initialized with the total days the specified month has (leap year excluded).

#### WATCH_ALARM
``` C
void watch_alarm(struct alarm *);
```
     The watch_alarm function sets a simple clock that exits at a specific user-defined time. The watch_alarm only accepts the address of a single argument of type ` struct alarm `. The struct is already pre-defined and should only be used to declare a variable whose address is to be passed to the watch_alarm function.
``` C
     /* struct prototype */
      struct alarm {
	int mins;
	int hour;
	char *msg;
     };
```

` Note: ` Passing a variable to the watch_alarm function which was declared with a user-defined struct type aside the program's defined structure type, would result in an abnormal behaviour of the program and possibly invoke an unexpected termination of the program.
``` C
/* USAGE */
   	 struct alarm var;
	 var->mins = 0;
	 var->hour = 12;
	 var->msg = "Alarm label";
	 watch_alarm(&var);
/*...*/
```

## GENERAL INFO:
-	Note that this program could be system/compiler dependent (Successfully compiled with gcc/ARM 64bit/ubuntu 14 O.S). However, this could be resolved by simple modification to the provided source code.
-	The precision of the outputed time at runtime may be dalayed by several milliseconds compared to the actual system time due to changes in timezone, redundancy in execution of program or incorrect system date and time(as program is completely dependent on the system's localtime, i.e, if specified by user).

Author: github.com/saviour623
Contact: saviourme33@gmail.com
