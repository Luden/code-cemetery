	//------------------------------------------------------------------
	//		Модуль аналитических методов
	//------------------------------------------------------------------

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "analytics.h"
#include <iostream>
#include <fstream>
#include "time.h"

using namespace std;

ofstream log4;

sphere::sphere(double * c1, double r1)
{
	//------------------------------------------------------------------
	//		Конструктор сферы
	//------------------------------------------------------------------

	center = new double[dnl];
	for(int i=0;i<dnl;i++)
	{
		center[i]=c1[i];
	}
	radius = r1;
}

sphere * sphere::make(double **coord, int num)
{
	//------------------------------------------------------------------
	//		Создание сферы
	//------------------------------------------------------------------

	double * mid = new double[dnl]; // средняя точка. она центр будущей сферы
	for(int j=0;j<dnl;j++)
	{
		mid[j]=0;
	}

	for(int i=0;i<num;i++)
	{
		for(int j=0;j<dnl;j++)
		{
			mid[j]+=coord[i][j];
		}
	}
	
	for(int j=0;j<dnl;j++)
	{
		mid[j]=mid[j]/(double)num;
	}

	double * dist; // расстояния от точек до центра
	double max; //максимальное расстояние - оно же радиус
	dist = new double [num];
	for(int i=0;i<num;i++)
	{
		dist[i] = 0;
		for(int j=0;j<dnl;j++)
		{
			dist[i]+=pow((mid[j]-coord[i][j]),(double)2);
		}
		dist[i]=sqrt(dist[i]);
	}

	max = dist[0];
	for(int i=0;i<num;i++)
	{
		if(dist[i]>max)
		{
			max=dist[i];
		}
	}

	// теперь нужно добавление радиуса для единичных точек.
	if(max==0)max+=0.0001;
	//else max+=(0.0001*max);

	sphere * s = new sphere(mid,max);
	return s;
}

bool sphere::check(double *coord)
{
	//------------------------------------------------------------------
	//		проверка на попадание в сферу
	//------------------------------------------------------------------

	double dist = 0;
	for(int i=0;i<dnl;i++)
	{
		dist+=pow((center[i]-coord[i]),(double)2);
	}
	dist = sqrt(dist);
	
	if(dist>radius)return 0;
	else return 1;
}

rulenode::rulenode()
{
	//------------------------------------------------------------------
	//		правило
	//------------------------------------------------------------------

	klass = 0;
	next = NULL;
	subrules = new rulelist();
}

bool rulenode::checkrule(double * coord)
{
	//------------------------------------------------------------------
	//		Проверка правила
	//------------------------------------------------------------------

	if(s->check(coord)==false)return 0;
	rulenode * temp = subrules->head;
	while(temp!=NULL)
	{
		if(temp->checkrule(coord))return 0;
		temp=temp->next;
	}
	return 1;
}

rulelist::rulelist()
{
	//------------------------------------------------------------------
	//		Список правил
	//------------------------------------------------------------------

	head = NULL;
	tail = NULL;
}

void rulelist::add(rulenode *r)
{
	//------------------------------------------------------------------
	//		добавление правила в список
	//------------------------------------------------------------------

	if(head==NULL)
	{
		head = r;
		tail = r;
	}
	else
	{
		tail->next=r;
		tail = r;
	}
}

dret::dret(int p1)
{
	//------------------------------------------------------------------
	//		Инициализация алгоритма ДРЭТ
	//------------------------------------------------------------------

	srand( (unsigned)time( NULL ) );
	if(log4.is_open())log4.close();
	log4.open("log4.txt");
	points = p1;
	curpoint = 0;
	rules = new rulelist();
	coords = new double * [points];
	for(int i=0;i<points;i++)
	{
		coords[i] = new double[dnl];
	}
	klasses = new int[points];
	nums = new int[dnl]; //количество точек каждого класса
}

void dret::premake()
{
	//------------------------------------------------------------------
	//		Предсоздание алгоритма дрэт
	//------------------------------------------------------------------

	points = curpoint; // наслучай если всё таки образов оказалось меньше чем задумывалось
	
	for(int i=0;i<dnl;i++)
	{
		nums[i]=0;
	}

	for(int i=0;i<points;i++)
	{
		nums[klasses[i]]++;
	}
}

void dret::make(int nn)
{	
	//------------------------------------------------------------------
	//		создание алгоритма дрэт. итерационно
	//------------------------------------------------------------------

	int i = nn; // атавизм
	
	if(nums[i]==0)return; //пропустим те классы, которые в сферу не попали

	double ** cc = new double*[nums[i]];
	int n = 0; //переменная для малого цикла		
	for(int j=0;j<points;j++) //большой цикл
	{
		if(klasses[j]==i)//малый цикл
		{
			cc[n] = new double[dnl];
			for(int k=0;k<dnl;k++)
			{
				cc[n][k]=coords[j][k];
			}
			n++;
		}			
	}
	// в итоге получили массив сс с координатами точек, попавших в сферу и принадлежащих к этому классу
	
	if(n!=nums[i])log4<<"error"<<endl;

	rulenode * r = new rulenode();
	r->s = r->s->make(cc,nums[i]);
	r->klass = i;
	log4<<"class "<<i<<", "<<n<<" points, r="<<r->s->radius<<endl;
	makesubrules(r,0);
	rules->add(r);	
}


void dret::shake(double ** cc, int num, rulenode * r, int kl, int level)
{
	//------------------------------------------------------------------
	//		Функция вывода из зацикливания
	//------------------------------------------------------------------

	int cen = rand()%(num-1)+1;

	double ** cc1 = new double *[cen];
	for(int i=0;i<cen;i++)
	{
		cc1[i] = new double[dnl];
		for(int j=0;j<dnl;j++)
		{
			cc1[i][j] = cc[i][j];
		}
	}
	double ** cc2 = new double *[num-cen];
	for(int i=0;i<num-cen;i++)
	{
		cc2[i] = new double[dnl];
		for(int j=0;j<dnl;j++)
		{
			cc2[i][j] = cc[cen+i][j];
		}
	}

	rulenode * r1 = new rulenode();
	r1->s = r1->s->make(cc1,cen);
	r1->klass = kl;
	
	//for(int i=0;i<level;i++)log4<<"  ";
	//log4<<r->klass<<":1 subclass "<<kl<<", "<<cen<<" points, r="<<r1->s->radius<<endl;
	
	makesubrules(r1, level+1);
	r->subrules->add(r1);


	rulenode * r2 = new rulenode();
	r2->s = r2->s->make(cc2,num-cen);
	r2->klass = kl;
	
	//for(int i=0;i<level;i++)log4<<"  ";
	//log4<<r->klass<<":2 subclass "<<kl<<", "<<num-cen<<" points, r="<<r2->s->radius<<endl;
	
	makesubrules(r2, level+1);
	r->subrules->add(r2);
}

void dret::dontshake(double ** cc, int num, rulenode * r, int kl, int level)
{
	//------------------------------------------------------------------
	//		неиспользование функции вывода из зацикливания
	//------------------------------------------------------------------

	rulenode * r1 = new rulenode();
	r1->s = r1->s->make(cc,num);
	r1->klass = kl;
	
	//for(int i=0;i<level;i++)log4<<"  ";
	//log4<<r->klass<<":1 subclass "<<kl<<", "<<num<<" points, r="<<r1->s->radius<<endl;
	
	makesubrules(r1, level+1);
	r->subrules->add(r1);
}

void dret::makesubrules(rulenode * r, int level)
{
	//------------------------------------------------------------------
	//		Создание подправил
	//------------------------------------------------------------------

	int * nums = new int[dnl]; //количество точек каждого класса
	for(int i=0;i<dnl;i++)
	{
		nums[i]=0;
	}

	int tnum=0;
	int bnum=0;
	for(int i=0;i<points;i++)
	{
		if(r->s->check(coords[i]))
		{
			nums[klasses[i]]++;  // посчитаем точки классов попавших в сферу правила
			tnum++;
			if(klasses[i]!=r->klass)bnum++;
		}
	}
	for(int i=0;i<level;i++)log4<<"  ";
	//log4<<"metaclass "<<r->klass<<", total "<<tnum<<" bad "<<bnum<<endl;
	for(int i=0;i<dnl;i++) //упакуем точки разных классов в отдельные массивы
	{
		if(nums[i]==0)continue; //пропустим те классы, которые в сферу не попали
		if(i==r->klass)continue;//пропустим которые принадлежат выбраному классу

		double ** cc = new double*[nums[i]];
		int n = 0; //переменная для малого цикла
		for(int j=0;j<points;j++) //большой цикл
		{
			if((klasses[j]==i)&&(r->s->check(coords[j])))//малый цикл
			{
				cc[n] = new double[dnl];
				for(int k=0;k<dnl;k++)
				{
					cc[n][k]=coords[j][k];
				}
				n++;
			}
		}
		//if(n!=nums[i])log4<<"error n="<<n<<" nums[i]="<<nums[i]<<endl;

		// в итоге получили массив сс с координатами точек, попавших в сферу и принадлежащих к этому классу		
		
		if(nums[i]>1) shake(cc,nums[i],r,i,level);
		else dontshake(cc,nums[i],r,i,level);
	}
}


void dret::add(double *x, int kl)
{
	//------------------------------------------------------------------
	//		Добавление точки
	//------------------------------------------------------------------

	if(curpoint>=points)return;

	for(int i=0;i<dnl;i++)
	{
		coords[curpoint][i] = x[i];
	}
	klasses[curpoint] = kl;

	curpoint++;
}

int dret::check(double *x)
{
	//------------------------------------------------------------------
	//		проверка точки
	//------------------------------------------------------------------

	rulenode * temp = rules->head;	
	while(temp!=NULL)
	{
		if(temp->checkrule(x))return temp->klass;
		temp=temp->next;
	}
	return 777; // нет такого. вернём бесконечность
}

int dret::knear(double * cc, double r)
{
	//------------------------------------------------------------------
	//		к-соседей
	//------------------------------------------------------------------

	sphere * s = new sphere(cc,r);
	int * nums = new int[dnl];
	for(int i=0;i<dnl;i++)
	{
		nums[i]=0;
	}

	for(int i=0;i<curpoint;i++)
	{
		if(s->check(coords[i]))
		{
			nums[klasses[i]]++;
		}
	}

	int max = nums[0];
	int maxnum = 0;
	for(int i=0;i<dnl;i++)
	{
		if(nums[i]>max)
		{
			max = nums[i];
			maxnum = i;
		}
		//log4<<i<<" - "<<nums[i]<<endl;
	}
	
	if(max==0) //радиус слишком мал и ниодной точки не попало
	{		
		double * dist; // расстояния от точек до центра
		double maxx; //максимальное расстояние - оно же радиус
		dist = new double [curpoint];
		for(int i=0;i<curpoint;i++)
		{
			dist[i] = 0;
			for(int j=0;j<dnl;j++)
			{
				dist[i]+=pow((cc[j]-coords[i][j]),(double)2);
			}
			dist[i]=sqrt(dist[i]);
		}

		maxx = dist[0];
		for(int i=0;i<curpoint;i++)
		{
			if(dist[i]>max)
			{
				maxx=dist[i];
				maxnum=klasses[i];
			}
		}
	}

	return maxnum;
}