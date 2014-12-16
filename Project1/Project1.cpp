#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <time.h>
#include "Calendar.h"

using namespace std;

Calendar income, run, past;
HANDLE hCheck;

void showMenu(int n);
void addPlan();
void showPast();
void showRun();
void showIncome();
void showIncomeByDay();
void showIncomeByWeek();
void showIncomeByMonth();
void writeToFile();
void readFromFile();
DWORD WINAPI CheckCalendar(LPVOID lp);

int main(void)
{
	printf("%d", sizeof(item));
	struct paramThread tp;
	tp.income = &income;
	tp.past = &past;
	tp.run = &run;
	hCheck = CreateThread(NULL, 0, CheckCalendar, &tp, 0, NULL);
	int input;
	readFromFile();
	while (1)
	{
		system("cls");
		showMenu(0);
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			addPlan();
			system("pause");
			break;
		case 2:
			showPast();
			system("pause");
			break;
		case 3:
			showRun();
			system("pause");
			break;
		case 4:
			showIncome();
			break;
		case 99:
			writeToFile();
			return 0;
		}
	}
	return 0;
}

void writeToFile()
{
	FILE *fp = fopen("plans.db", "wb+");
	if (!fp)
		return;
	item *p = income;
	while (p)
	{
		fwrite(p, sizeof(item), 1, fp);
		p = p->next;
	}
	p = run;
	while (p)
	{
		fwrite(p, sizeof(item), 1, fp);
		p = p->next;
	}
	p = past;
	while (p)
	{
		fwrite(p, sizeof(item), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

void readFromFile()
{
	FILE *fp = fopen("plans.db", "rb");
	if (!fp)
		return;
	item i;
	fread(&i, sizeof(item), 1, fp);
	while (!feof(fp))
	{
		addItem(&income, i);
		fread(&i, sizeof(item), 1, fp);
	}
	fclose(fp);
	checkRemender(income, run, past);
}

DWORD WINAPI CheckCalendar(LPVOID lp)
{
	struct paramThread *p = (struct paramThread *)lp;
	while (1)
	{
		checkItem(p->income, p->run, p->past);
		checkRemender(*(p->income), *(p->run), *(p->past));
		Sleep(1000);
	}
	return 0;
}

void addPlan()
{
	system("cls");
	item i;
	struct tm t;
	int year, mon, day, hh, mm, ss;
	system("cls");
	printf("������ƻ�ID:");
	scanf("%d", &(i.ID));
	printf("�����뿪ʼʱ�䣬��ʽΪ ��-��-�� ʱ:��:�� \n");
	scanf("%d-%d-%d %d:%d:%d", &year, &mon, &day, &hh, &mm, &ss);
	t.tm_year = year - 1900;
	t.tm_mon = mon - 1;
	t.tm_mday = day;
	t.tm_hour = hh;
	t.tm_min = mm;
	t.tm_sec = ss;
	i.startTime = mktime(&t);
	printf("���������ʱ�䣬��ʽΪ ��-��-�� ʱ:��:�� \n");
	scanf("%d-%d-%d %d:%d:%d", &year, &mon, &day, &hh, &mm, &ss);
	t.tm_year = year - 1900;
	t.tm_mon = mon - 1;
	t.tm_mday = day;
	t.tm_hour = hh;
	t.tm_min = mm;
	t.tm_sec = ss;
	i.endTime = mktime(&t);
	printf("����������ʱ�䣬��ʽΪ ��-��-�� ʱ:��:�� \n");
	scanf("%d-%d-%d %d:%d:%d", &year, &mon, &day, &hh, &mm, &ss);
	t.tm_year = year - 1900;
	t.tm_mon = mon - 1;
	t.tm_mday = day;
	t.tm_hour = hh;
	t.tm_min = mm;
	t.tm_sec = ss;
	i.remenderTime = mktime(&t);
	printf("������ƻ����ƣ�");
	scanf("%s", i.name);
	printf("������ͬ����Ա��");
	scanf("%s", i.people);
	printf("������ȥ���ص㣺");
	scanf("%s", i.location);
	i.alreadyReminded = false;
	addItem(&income,i);
	printf("��ӳɹ���");
}
void showPast()
{
	system("cls");
	Calendar t = past;
	while (t)
	{
		printf("���ƣ�\t%s\n��ʼʱ�䣺\t%s����ʱ�䣺\t%s�¼�����\t%s\nͬ����Ա��\t%s\n�ص㣺\t%s\n����ʱ�䣺\t%s",
			t->name, ctime(&t->startTime), ctime(&t->endTime), t->name, t->people, t->location, ctime(&t->remenderTime));
		t = t->next;
	}
}
void showRun()
{
	system("cls");
	Calendar t = run;
	while (t)
	{
		printf("���ƣ�\t%s\n��ʼʱ�䣺\t%s����ʱ�䣺\t%s�¼�����\t%s\nͬ����Ա��\t%s\n�ص㣺\t%s\n����ʱ�䣺\t%s",
			t->name, ctime(&t->startTime), ctime(&t->endTime), t->name, t->people, t->location, ctime(&t->remenderTime));
		t = t->next;
	}
}
void showIncome()
{
	system("cls");
	showMenu(4);
	int choice;
	scanf("%d",&choice);
	switch (choice)
	{
	case 1:
		showIncomeByDay();
		system("pause");
		break;
	case 2:
		showIncomeByWeek();
		system("pause");
		break;
	case 3:
		showIncomeByMonth();
		system("pause");
		break;
	default:
		break;
	}
}
void showIncomeByDay()
{
	system("cls");
	Calendar t = income;
	time_t tt = time(nullptr);
	struct tm *tn = localtime(&tt);
	struct tm *ti;
	while (t)
	{
		ti = localtime(&(t->startTime));
		if (tn->tm_year == ti->tm_year && ti->tm_mon == tn->tm_mon && ti->tm_mday == tn->tm_mday)
		{
			printf("���ƣ�\t%s\n��ʼʱ�䣺\t%s����ʱ�䣺\t%s�¼�����\t%s\nͬ����Ա��\t%s\n�ص㣺\t%s\n����ʱ�䣺\t%s",
				t->name, ctime(&t->startTime), ctime(&t->endTime), t->name, t->people, t->location, ctime(&t->remenderTime));
		}
		t = t->next;
	}
}
void showIncomeByWeek()
{
	system("cls");
	Calendar t = income;
	time_t tt = time(nullptr);
	struct tm *tn = localtime(&tt);
	struct tm *ti;
	while (t)
	{
		ti = localtime(&(t->startTime));
		if (tn->tm_year == ti->tm_year && ti->tm_mon == tn->tm_mon && (ti->tm_mday - ti->tm_wday )<=( tn->tm_mday - tn->tm_wday + 7))
		{
			printf("���ƣ�\t%s\n��ʼʱ�䣺\t%s����ʱ�䣺\t%s�¼�����\t%s\nͬ����Ա��\t%s\n�ص㣺\t%s\n����ʱ�䣺\t%s",
				t->name, ctime(&t->startTime), ctime(&t->endTime), t->name, t->people, t->location, ctime(&t->remenderTime));
		}
		t = t->next;
	}
}
void showIncomeByMonth()
{
	system("cls");
	Calendar t = income;
	time_t tt = time(nullptr);
	struct tm *tn = localtime(&tt);
	struct tm *ti;
	while (t)
	{
		ti = localtime(&(t->startTime));
		if (tn->tm_year == ti->tm_year && ti->tm_mon == tn->tm_mon)
		{
			printf("���ƣ�\t%s\n��ʼʱ�䣺\t%s����ʱ�䣺\t%s�¼�����\t%s\nͬ����Ա��\t%s\n�ص㣺\t%s\n����ʱ�䣺\t%s",
				t->name, ctime(&t->startTime), ctime(&t->endTime), t->name, t->people, t->location, ctime(&t->remenderTime));
		}
		t = t->next;
		free(ti);
	}
}
void showMenu(int n)
{
	system("cls");
	switch (n)
	{
	case 4:
		printf("δ��ʼ�ƻ���ѯ\n");
		printf("1. ����\n");
		printf("2. ����\n");
		printf("3. ����\n");
		printf("99.����\n");
		printf("����������ѡ��");
		break;
	default:
		printf("��������ϵͳ\n");
		printf("1. ��Ӽƻ�\n");
		printf("2. �鿴�ѽ����ƻ�\n");
		printf("3. �鿴���ڽ��мƻ�\n");
		printf("4. ��ѯδ��ʼ�ƻ�\n");
		printf("99.�˳�\n");
		printf("����������ѡ��");
		break;
	}
}