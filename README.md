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

### TIME_CLOCK
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
*	The initializing value for year must range from ` 2000, ... `. Threfore, any input below 2000 will incur program error and terminate consecutively.
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

` Note: ` Passing a variable to the watch_alarm function, declared with a user-defined struct type aside the program's defined structure type, would result in an abnormal behaviour of the program and possibly invoke an unexpected termination of the program.
``` C
/* USAGE */
   	 struct alarm var;
	 var->mins = 0;
	 var->hour = 12;
	 var->msg = "Alarm label";
	 watch_alarm(&var);
/*...*/
```

### GENERAL INFO:
-	Note that this program could be system/compiler dependent (Successfully compiled with gcc/ARM 64bit/ubuntu 14 O.S). However, this could be resolved by simple modification to the provided source code.
-	The precision of the outputed time at runtime may be dalayed by several milliseconds compared to the actual system time due to changes in timezone, redundancy in execution of program or incorrect system date and time(as program is completely dependent on the system's localtime, i.e, if specified by user).

Author: github.com/saviour623
Contact: saviourme33@gmail.com
