#define _CRT_SECURE_NO_WARNINGS
#include "Calendar.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
void initCalendar(Calendar * c)
{
	*c = nullptr;
}
void addItem(Calendar *c, item it)
{
	item *t = (item *)malloc(sizeof(item));
	memcpy(t, &it, sizeof(item));
	if ((*c) == nullptr)
	{
		(*c) = t;
		(*c)->next = nullptr;
		(*c)->prev = nullptr;
		return;
	}
	Calendar cc = *c;
	while (cc->next != nullptr)
	{
		if (cc->startTime > t->startTime)
			break;
		cc = cc->next;
	}
	if (cc->next != nullptr)
	{
		t->next = cc;
		t->prev = cc->prev;
		cc->prev = t;
	}
	else
	{
		if (cc->startTime < t->startTime)
		{
			t->next = NULL;
			t->prev = cc;
			cc->next = t;
		}
		else
		{
			t->next = cc;
			t->prev = cc->prev;
			cc->prev = t;
		}
	}
	while ((*c)->prev)
		(*c) = (*c)->prev;
}
void moveItem(Calendar *ci ,item *i, Calendar * c)
{
	if (i->prev)
		i->prev->next = i->next;
	if (i->next)
		i->next->prev = i->prev;
	if (i == *ci)
		(*ci) = i->next;
	if ((*c) == nullptr)
	{
		(*c) = i;
		(*c)->next = nullptr;
		(*c)->prev = nullptr;
		return;
	}
	Calendar cc = *c;
	while (cc->next != nullptr)
	{
		if (cc->startTime > i->startTime)
			break;
		cc = cc->next;
	}
	if (cc->next != nullptr)
	{
		i->next = cc;
		i->prev = cc->prev;
		cc->prev = i;
	}
	else
	{
		if (cc->startTime <= i->startTime)
		{
			i->next = NULL;
			i->prev = cc;
			cc->next = i;
		}
		else
		{
			i->next = cc;
			i->prev = cc->prev;
			cc->prev = i;
		}
	}
	while ((*c)->prev)
		(*c) = (*c)->prev;
}
void checkItem(Calendar *income, Calendar *run, Calendar *past)
{
	time_t timeNow = time(nullptr);
	item *p = *income;
	while (p)
	{
		if (p->startTime <= timeNow)
		{
			printf("有新事件开始了！\n名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				p->name, ctime(&p->startTime), ctime(&p->endTime), p->name, p->people, p->location,ctime(&p->remenderTime) );
			moveItem(income,p,run);
		}
		p = p->next;
	}
	p = *run;
	while (p)
	{
		if (p->endTime <= timeNow)
		{
			printf("有新事件结束了！\n名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				p->name, ctime(&p->startTime), ctime(&p->endTime), p->name, p->people, p->location, ctime(&p->remenderTime));
			moveItem(run, p, past);
		}
		p = p->next;
	}
}

void checkRemender(Calendar income, Calendar run, Calendar past)
{
	time_t timeNow = time(nullptr);
	while (income)
	{
		if (income->remenderTime <= timeNow && !income->alreadyReminded)
		{
			income->alreadyReminded = true;
			printf("有新事件提醒！\n名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				income->name, ctime(&income->startTime), ctime(&income->endTime), income->name, income->people, income->location, ctime(&income->remenderTime));
		}
		income = income->next;
	}
	while (run)
	{
		if (run->remenderTime <= timeNow && !run->alreadyReminded)
		{
			run->alreadyReminded = true;
			printf("有新事件提醒！\n名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				run->name, ctime(&run->startTime), ctime(&run->endTime), run->name, run->people, run->location, ctime(&run->remenderTime));
		}
		run = run->next;
	}
	while (past)
	{
		if (past->remenderTime <= timeNow && !past->alreadyReminded)
		{
			past->alreadyReminded = true;
			printf("有新事件提醒！\n名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				past->name, ctime(&past->startTime), ctime(&past->endTime), past->name, past->people, past->location, ctime(&past->remenderTime));
		}
		past = past->next;
	}
}