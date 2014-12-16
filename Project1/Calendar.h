#ifndef _CALENDAR_H_
#define _CALENDAR_H_
#include <time.h>
typedef struct item_int item, *Calendar;

struct paramThread
{
	Calendar income, run, past;
};

struct item_int
{
	int ID;
	time_t startTime;
	time_t endTime;
	char name[64];
	char people[64];
	char location[64];
	time_t remenderTime;
	item *next;
	item *prev;
};
void initCalendar(Calendar * c);
void addItem(Calendar *c, item it);
void checkItem(Calendar income, Calendar run, Calendar past);
void checkRemender(Calendar income, Calendar run, Calendar past);

#endif