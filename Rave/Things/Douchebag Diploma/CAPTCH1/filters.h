	//------------------------------------------------------------------
	//		������ ����������
	//------------------------------------------------------------------

#ifndef FILTERSTUFF
#define FILTERSTUFF

#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "math.h"

using namespace std;

class filter
{
public:
	int type;				// ��� �������
	double ** patt;			// ������� ��� ������	
	int weight;				// ��� �����
	bool hexbind;			// 0 - ��������� �����������, 1 - ��������� ������������
	double brlev;			// ����� ������� �����
	int level;				// ����������� ����� ����� �������� ��� ����������� ��������
	int rad;				// ������ ���������� ����
	int cwidth, cheight;	// ��������� �����������
	double sigm;			// ����������� ���������� ���������
	
	filter(int type0);
	void doit(double ** mass);
	void spotnoise(double ** mass);
	void advnoise(double ** mass);
	void gaussblur(double ** mass);
	void brightbias(double ** mass);

	double ** clone(double ** mass);
	void createpattern();
	double gauss(int x, int y, double ** mass);
	double dot(int x, int y);
	int medi(int x,int y, double ** mass);	
	int spotter(int x,int y, double ** mass);

};

class filternode
{
public:
	filter * f;
	filternode * next;

	filternode(filter * f1)
	{
		next = NULL;
		f = f1;
	}
};

class filterlist
{
public:

	filternode * head;
	filternode * tail;
	//double ** mass;

	filterlist();
	void add(filter * f);
	void del(int x);
	filter * get(int x);
	void set(int x, filter * f);
	void exchange(int x, int y);
	void doit(double ** mass);
};

#endif