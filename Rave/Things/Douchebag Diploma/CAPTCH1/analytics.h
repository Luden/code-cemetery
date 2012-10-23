	//------------------------------------------------------------------
	//		������ ������������� �������
	//------------------------------------------------------------------

#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "math.h"

using namespace std;

class sphere;
class rulenode;
class rulelist;
class dret;

class sphere
{
public:
	static const int dnl = 24; // ����������� ������������
	double * center;
	double radius;
	sphere(double * c1, double r1);
	bool check(double * coord);
	sphere * make(double ** coord, int num);
};

class rulenode
{
public:
	static const int dnl = 24;

	sphere * s;
	int klass;
	rulelist * subrules;
	rulenode * next;
	rulenode();
	
	bool checkrule(double * coord);
};

class rulelist
{
public:
	rulenode * head;
	rulenode * tail;
	rulelist();
	void add(rulenode * r); //��������� � �����
	//void del(); //���� � ������
};

class dret
{	
public:
	static const int dnl = 24;	 // ����������� ������������
	int points;					 // ���������� ��������� �����
	double ** coords;			 // ���������� �����
	int * klasses;				 // ������ �����
	int curpoint;				 // ������� �����
	int * nums;					 // ���������� ����� ������� ������

	rulelist * rules;
	dret(int p1);
	void premake();
	void make(int nn);
	int check(double * x);
	void makesubrules(rulenode * r, int level);
	void add(double * x, int kl);
	void shake(double ** cc, int num, rulenode * r, int kl, int level);
	void dontshake(double ** cc, int num, rulenode * r, int kl, int level);

	int knear(double * cc, double r);	// ����� � ���������
};
