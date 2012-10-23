	//------------------------------------------------------------------
	//		ћодуль статистики
	//------------------------------------------------------------------

#include "stdafx.h"
#include "stdio.h"
#include "iostream"

using namespace std;

class statistic
{
public:
	char * liters;		// символы
	int * count;		// их общие количества
	int * lastcount;	// количества за последние
	int * gcount;		// их общие количества успешных распознаваний
	int * lastgcount;	// количества успешных распознаваний за последние
	
	int * gcounta;		// количества успешных распознаваний аналитикой

	float * stats;		// в виде процентов
	float * laststats;

	float * statsa;		// в виде процентов аналитика

	int num;			// количество символов
	int total;			// всего символов прин€то
	int diskr;			// за последние итераций
	int wlen;			// длина слова
	int winers;			// винеры
	float crit;			// критерий вина

	statistic(char * l, int n,int wl = 5, int d = 1)
	{
		//------------------------------------------------------------------
		//		 онструктор класса статистики
		//------------------------------------------------------------------

		num = n;
		total = 0;
		diskr = d;
		wlen = wl;
		winers = 0;
		crit = 1;

		liters = new char[num];

		count = new int[num];
		lastcount = new int[num];

		gcount = new int[num];	
		gcounta = new int[num];	
		lastgcount = new int[num];

		stats = new float[num];
		statsa = new float[num];
		laststats = new float[num];

		for(int i=0;i<num;i++)
		{
			stats[i]=0;
			statsa[i]=0;
			laststats[i]=0;
			
			count[i]=0;
			lastcount[i]=0;
			
			gcount[i]=0;
			gcounta[i]=0;
			lastgcount[i]=0;
			
			liters[i]=l[i];
		}
	}

	void setdiskr(int d)
	{
		diskr=d;
	}

	void setwordlength(int wl)
	{
		wlen = wl;
	}

	void setcrit(float cr)
	{
		crit = cr;
	}

	void reset()
	{
		//------------------------------------------------------------------
		//		—брос статистики
		//------------------------------------------------------------------

		total = 0;

		for(int i=0;i<num;i++)
		{
			stats[i]=0;
			statsa[i]=0;
			laststats[i]=0;
			
			count[i]=0;
			lastcount[i]=0;
			
			gcount[i]=0;
			gcounta[i]=0;
			lastgcount[i]=0;
		}
	}

	void check(char * first, char * second, int len = 0)
	{
		//------------------------------------------------------------------
		//		¬едение статистики
		//------------------------------------------------------------------

		//first - предположение, second - отгадка

		if(len==0)len=wlen;

		winers=0;

		total+=len;
		for(int i=0;i<len;i++)
		{
			int ln = 0; //вычисление индекса литеры в массиве
			for(int j=0;j<num;j++)
			{
				if (liters[j]==first[i])break;
				ln++;
			}

			int ln2 = 0;
			for(int j=0;j<num;j++)
			{
				if (liters[j]==second[i])break;
				ln2++;
			}

			count[ln2]++;
			lastcount[ln2]++;
			if(first[i]==second[i]) 
			{
				gcount[ln]++;
				lastgcount[ln]++;
			}

			if(lastcount[ln]>=diskr)
			{
				laststats[ln]=(float)lastgcount[ln]/(float)lastcount[ln];
				lastcount[ln]=0;
				lastgcount[ln]=0;
			}
		}
	}

	void checka(char * first, char * second, int len = 0)
	{
		//------------------------------------------------------------------
		//		ведение статистики аналитики
		//------------------------------------------------------------------

		//first - предположение, second - отгадка

		if(len==0)len=wlen;

		for(int i=0;i<len;i++)
		{
			int ln = 0; //вычисление индекса литеры в массиве
			for(int j=0;j<num;j++)
			{
				if (liters[j]==first[i])break;
				ln++;
			}
			
			if(first[i]==second[i]) 
			{
				gcounta[ln]++;				
			}
		}
	}

	void checkstats()
	{
		//------------------------------------------------------------------
		//		пересчет статистики
		//------------------------------------------------------------------

		winers=0;
		
		for(int i=0;i<num;i++)
		{
			stats[i]=(float)gcount[i]/(float)count[i];
			statsa[i]=(float)gcounta[i]/(float)count[i];
			if(count[i]==0){stats[i]=0;statsa[i]=0;}
			if(laststats[i]>=crit)winers++;
		}		
	}

	void forcecheck()
	{
		//------------------------------------------------------------------
		//		принудительный пересчЄт статистики
		//------------------------------------------------------------------

		winers = 0;

		for(int i=0;i<num;i++)
		{
			stats[i]=(float)gcount[i]/(float)count[i];
			statsa[i]=(float)gcounta[i]/(float)count[i];
			laststats[i]=(float)lastgcount[i]/(float)lastcount[i];
			if(laststats[i]>=crit)winers++;
			if(count[i]==0){stats[i]=0;statsa[i]=0;}
			if(lastcount[i]==0)laststats[i]=0;
			lastcount[i]=0;
			lastgcount[i]=0;
		}
	}
};