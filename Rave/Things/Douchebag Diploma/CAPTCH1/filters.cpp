	//------------------------------------------------------------------
	//		Модуль фильтрации
	//------------------------------------------------------------------

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "filters.h"
#include <iostream>
#include <fstream>

using namespace std;

ofstream log3;

double ** filter::clone(double ** mass)
{
	//------------------------------------------------------------------
	//		Клонирование фильтра
	//------------------------------------------------------------------
	double ** mas = new double * [cwidth];
	for(int i=0;i<cwidth;i++)
	{
		mas[i] = new double [cheight];
		for(int j=0;j<cheight;j++)
		{
			mas[i][j]=mass[i][j];	
		}
	}
	return mas;
}


void filter::gaussblur(double ** mass)
{
	//------------------------------------------------------------------
	//		размытие по Гауссу
	//------------------------------------------------------------------

	double ** mas = clone(mass);

	for(int i=0;i<cwidth;i++)
	{
		for(int j=0;j<cheight;j++)
		{
			double ccl = gauss(i,j,mas);			
			mass[i][j]=ccl;
		}
	}
}

double filter::gauss(int x, int y, double ** mass)
{
	//------------------------------------------------------------------
	//		Алгоритм размытия по Гауссу
	//------------------------------------------------------------------

	double sum = 0; 
	double total = 0;

	for(int i=x-rad;i<x+rad+1;i++)
	{		
		for(int j=y-rad;j<y+rad+1;j++)
		{			
			if(dot(i,j)==1)
			{
				total += patt[rad+i-x][rad+j-y];
				sum += (mass[i][j] * patt[rad+i-x][rad+j-y]);
			}
		}
	}

	return sum/total;
}

void filter::createpattern()
{	
	//------------------------------------------------------------------
	//		Создание шаблона Гауссового размытия
	//------------------------------------------------------------------

	if(sigm==0) sigm = (double)rad * 0.75;	

	patt = new double * [rad*2+1];
	for(int i=0;i<rad*2+1;i++)
	{
		patt[i] = new double [rad*2+1];
		for(int j=0;j<rad*2+1;j++)
		{
			patt[i][j]=0;
		}
	}

	for(int i=-rad;i<rad+1;i++)
	{		
		for(int j=-rad;j<rad+1;j++)
		{			
			double g = (1/(6.28*sigm*sigm))*exp(-(i*i+j*j)/(2*sigm*sigm));			
			patt[i+rad][j+rad]=g;
		}		
	}

	for(int i=0;i<rad*2+1;i++)
	{
		for(int j=0;j<rad*2+1;j++)
		{
			patt[i][j]=patt[i][j]/patt[rad*2][rad*2];			
			log3<<patt[i][j]<<" ";
		}	
		log3<<endl;
	}	
}


double filter::dot(int x, int y)
{
	//------------------------------------------------------------------
	//		проверка границ
	//------------------------------------------------------------------

	if(x<0)return 0;
	if(y<0)return 0;
	if(x>=cwidth)return 0;
	if(y>=cheight)return 0;
	return 1;
}

void filter::spotnoise(double ** mass)
{	
	//------------------------------------------------------------------
	//		Фильтр по весу пятна
	//------------------------------------------------------------------

	double ** mas = clone(mass);

	for(int i=0;i<cwidth;i++)
	{
		for(int j=0;j<cheight;j++)
		{
			int aa = spotter(i,j,mas);
			if((aa<=weight)&&(aa>0)) spotter(i,j,mass);			
		}
	}
}


void filter::advnoise(double ** mass)
{	
	//------------------------------------------------------------------
	//		Фильтр по среднему
	//------------------------------------------------------------------

	double ** mas = clone(mass);

	for(int i=0;i<cwidth;i++)
	{
		for(int j=0;j<cheight;j++)
		{
			if(medi(i,j,mas)==0)
				mass[i][j]=0;
		}
	}
}

int filter::medi(int x,int y,double ** mass)
{
	//------------------------------------------------------------------
	//		Алгоритм фильтрации по среднему
	//------------------------------------------------------------------

	int sum=0;
	for(int i=x-rad;i<x+rad+1;i++)
	{
		if(i<0) continue;
		if(i>=cwidth) continue;
		for(int j=y-rad;j<y+rad+1;j++)
		{
			if(j<0)continue;
			if(j>=cheight)continue;
			sum+=mass[i][j];
		}
	}
	int hsq = pow((double)(rad*2+1),(double)2)/2;
	if(sum>level)return 1; 
	else return 0;
}

int filter::spotter(int x,int y, double ** mass)
{	
	//------------------------------------------------------------------
	//		Выделение пятна
	//------------------------------------------------------------------

	int ans=0;
	
	if(mass[x][y]>brlev)
	{
		ans=1;

		mass[x][y]=0;
		
		if(x>0)ans+=spotter(x-1,y,mass);
		if(x<cwidth-1)ans+=spotter(x+1,y,mass);
		if(y>0)ans+=spotter(x,y-1,mass);
		if(y<cheight-1)ans+=spotter(x,y+1,mass);

		if(hexbind)
		{
			if((x>0)&&(y>0))ans+=spotter(x-1,y-1,mass);
			if((x<cwidth-1)&&(y<cheight-1))ans+=spotter(x+1,y+1,mass);
			if((y>0)&&(x<cwidth-1))ans+=spotter(x+1,y-1,mass);
			if((y<cheight-1)&&(x>0))ans+=spotter(x-1,y+1,mass);
		}
	}
	return ans;
}


void filter::brightbias(double ** mass)
{
	//------------------------------------------------------------------
	//		Порог по яркости
	//------------------------------------------------------------------

	for(int i=0;i<cwidth;i++)
	{
		for(int j=0;j<cheight;j++)
		{
			if(mass[i][j]<brlev)
				mass[i][j]=0;
		}
	}
}

filter::filter(int type0)
{
	//------------------------------------------------------------------
	//		Конструктор класса
	//------------------------------------------------------------------

	type = type0;
	weight = 0;
	brlev = 0;
	rad = 0;
	level = 0;
	hexbind = 0;
	cwidth = 0;
	cheight = 0;
	sigm = 0;
}

void filter::doit(double ** mass)
{
	//------------------------------------------------------------------
	//		Выполнение фильтрации
	//------------------------------------------------------------------

	switch (type)
	{
	case 0: 
		{
			spotnoise(mass);
			break;
		}
	case 1: 
		{
			advnoise(mass);
			break;
		}
	case 2: 
		{
			gaussblur(mass);
			break;
		}
	case 3: 
		{
			brightbias(mass);
			break;
		}
	}
}


filterlist::filterlist()
{
	log3.open("log3.txt");
	head = NULL;
	tail = NULL;
}

void filterlist::add(filter * f)
{
	//------------------------------------------------------------------
	//		Добавление фильтра в список
	//------------------------------------------------------------------

	filternode * node = new filternode(f);

	if(head==NULL)
	{	
		head = node;
		tail = node;
	}
	else
	{
		tail->next = node;
		tail = node;
	}	
}

void filterlist::del(int x)
{
	//------------------------------------------------------------------
	//		Удаление фильтра из списка
	//------------------------------------------------------------------

	if(head==NULL)return;

	filternode * temp = head;
	filternode * prev = head;

	for(int i=0;i<x;i++)
	{
		if(temp->next!=NULL)
		{
			prev = temp;
			temp=temp->next;
		}
	}

	if(temp==head)
	{
		if(temp==tail)tail==NULL;
		head = temp->next;
		delete(temp);
	}
	else if (temp==tail)	
	{
		prev->next=NULL;
		tail = prev;
		delete(temp);
	}
	else
	{
		prev->next=temp->next;
		delete(temp);
	}
}

void filterlist::exchange(int x, int y)
{
	//------------------------------------------------------------------
	//		Обмен фильтров в списке
	//------------------------------------------------------------------

	if(head==NULL)return;
	
	filternode * temp = head;
	filternode * temp2 = head;

	for(int i=0;i<x;i++)
	{
		if(temp->next!=NULL)
		{			
			temp=temp->next;
		}
		else return;
	}

	for(int i=0;i<y;i++)
	{
		if(temp2->next!=NULL)
		{			
			temp2=temp2->next;
		}
		else return;
	}

	filter * tt = temp->f;
	temp->f = temp2->f;
	temp2->f = tt;
}

void filterlist::doit(double ** mass)
{
	//------------------------------------------------------------------
	//		Выполнение списка фильтров
	//------------------------------------------------------------------

	if(head==NULL)return;
	
	filternode * temp = head;

	while(temp!=NULL)
	{
		temp->f->doit(mass);
		temp = temp->next;
	}
}

filter * filterlist::get(int x)
{
	//------------------------------------------------------------------
	//		Получение фильра из списка
	//------------------------------------------------------------------

	if(head==NULL)return NULL;

	filternode * temp = head;
	for(int i=0;i<x;i++)
	{
		if(temp->next!=NULL)
		{			
			temp=temp->next;
		}
		else return NULL;
	}
	
	return temp->f;
}

void filterlist::set(int x, filter * f)
{
	//------------------------------------------------------------------
	//		Установка фильтра в список
	//------------------------------------------------------------------

	if(head==NULL)return;

	filternode * temp = head;
	for(int i=0;i<x;i++)
	{
		if(temp->next!=NULL)
		{			
			temp=temp->next;
		}
		else return;
	}
	
	temp->f = f;
}