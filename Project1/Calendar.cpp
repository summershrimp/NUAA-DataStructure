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
	while (cc != nullptr)
	{
		if (cc->startTime > t->startTime)
			break;
		cc = cc->next;
	}
	t->next = cc;
	t->prev = cc->prev;
	cc->prev = t;
}
void checkItem(Calendar income, Calendar run, Calendar past)
{
	time_t timeNow = time(nullptr);
	while (income)
	{
		if (income->startTime <= timeNow)
		{
			printf("�����¼���ʼ�ˣ�\n���ƣ�\t%s\n��ʼʱ�䣺%s\t\n����ʱ�䣺%s\t\n�¼�����%s\t\nͬ����Ա��%s\t\n�ص㣺%s\t\n����ʱ�䣺%s\t\n",
				income->name, ctime(&income->startTime), ctime(&income->endTime), income->name, income->people, income->location,ctime(&income->remenderTime) );
			addItem(&run, *income);
		}
		income = income->next;
	}
	while (run)
	{
		if (run->startTime <= timeNow)
		{
			printf("�����¼������ˣ�\n���ƣ�\t%s\n��ʼʱ�䣺%s\t\n����ʱ�䣺%s\t\n�¼�����%s\t\nͬ����Ա��%s\t\n�ص㣺%s\t\n����ʱ�䣺%s\t\n",
				run->name, ctime(&run->startTime), ctime(&run->endTime), run->name, run->people, run->location, ctime(&run->remenderTime));
			addItem(&past, *run);
		}
		run = run->next;
	}
}

void checkRemender(Calendar income, Calendar run, Calendar past)
{
	time_t timeNow = time(nullptr);
	checkItem(income, run, past);
	while (income)
	{
		if (income->remenderTime <= timeNow)
		{
			printf("�����¼����ѣ�\n���ƣ�\t%s\n��ʼʱ�䣺%s\t\n����ʱ�䣺%s\t\n�¼�����%s\t\nͬ����Ա��%s\t\n�ص㣺%s\t\n����ʱ�䣺%s\t\n",
				income->name, ctime(&income->startTime), ctime(&income->endTime), income->name, income->people, income->location, ctime(&income->remenderTime));
		}
		income = income->next;
	}
	while (run)
	{
		if (run->remenderTime <= timeNow)
		{
			printf("�����¼����ѣ�\n���ƣ�\t%s\n��ʼʱ�䣺%s\t\n����ʱ�䣺%s\t\n�¼�����%s\t\nͬ����Ա��%s\t\n�ص㣺%s\t\n����ʱ�䣺%s\t\n",
				run->name, ctime(&run->startTime), ctime(&run->endTime), run->name, run->people, run->location, ctime(&run->remenderTime));
		}
		run = run->next;
	}
	while (past)
	{
		if (past->remenderTime <= timeNow)
		{
			printf("�����¼����ѣ�\n���ƣ�\t%s\n��ʼʱ�䣺%s\t\n����ʱ�䣺%s\t\n�¼�����%s\t\nͬ����Ա��%s\t\n�ص㣺%s\t\n����ʱ�䣺%s\t\n",
				past->name, ctime(&past->startTime), ctime(&past->endTime), past->name, past->people, past->location, ctime(&past->remenderTime));
		}
		past = past->next;
	}
}