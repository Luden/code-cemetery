	//------------------------------------------------------------------
	//		Модуль нейросети
	//------------------------------------------------------------------

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "neubase.h"
#include <iostream>
#include <fstream>


using namespace std;

ofstream log2;

void neuron::add(double x)
{
	//------------------------------------------------------------------
	//		Накопление сигнала на сумматоре
	//------------------------------------------------------------------

	sum+=x;
}

double neuron::set()
{
	//------------------------------------------------------------------
	//		Активация нейрона
	//------------------------------------------------------------------

	double f = func();
	for(int i=0;i<aksnum;i++)
	{
		akson[i]->add(f*w[i]);
	}
	ans = f;
	sum = 0;
	return f;
}

double neuron::func()
{
	//------------------------------------------------------------------
	//		Активационная функция нейрона
	//------------------------------------------------------------------

	float alfa1 = 1;
	sum+=bias; //порог по хайкину надо добавлять на сумматор
	double f = -0.5f+1/(1+exp(-sum*alfa1)); // от сжимает на отрезок -0.5 до 0.5
	//double f = 1/(1+exp(-sum)); // от сжимает на отрезок 0 до 1
	return f;
}

neuron::neuron()
{
	bias = 0;	
	sum = 0;	
}

neuron::neuron(double bias0)
{
	bias = bias0;
	sum = 0;
}

void neuron::setaksnum(int n)
{
	//------------------------------------------------------------------
	//		Число аксонов
	//------------------------------------------------------------------

	aksnum = n;
	w = new double[n];
	for(int i=0;i<n;i++)w[i]=1; // инициализация начальными весами! исправить ли на случайные?
	akson = new neuron * [n];
}

network::network(int n, int m, int numout0, double bias01, double bias02, double alef0, double w1, double w2, bool dl0, int d2)
{
	//------------------------------------------------------------------
	//		Конструктор сети
	//------------------------------------------------------------------

	height = n;
	width = m;
	dim = n*m;
	dim2 = d2;
	bias1 = bias01;
	bias2 = bias02;
	alef = alef0;
	numout = numout0;
	bet1 = w1;
	bet2 = w2;
	dl = dl0;

	x = new neuron [dim];
	nr = new neuron [dim2];
	y = new neuron [numout];
}

void network::initialize()
{	
	//------------------------------------------------------------------
	//		Инициализация сети
	//------------------------------------------------------------------

	if(log2.is_open())log2.close();
	log2.open("log2.txt");

	srand( (unsigned)time( NULL ) );
	int b1 = bias2*100 - bias1*100;
	int w1 = bet2*100 - bet1*100;

	for(int i=0;i<numout;i++)
	{
		y[i] = neuron();			
		y[i].aksnum = 0;
	}

	if(dl==true) //сеть в два слоя
	{
		double b;
		for(int i=0;i<dim2;i++)	
		{
			if(b1>0) b = ((double)(rand()%b1)+(double)(bias1*100))/100;
			else b=bias1;
			nr[i] = neuron(b);
			nr[i].setaksnum(numout);
		}
	}

	for(int i=0;i<dim;i++)
	{
		double b;

		if(b1>0) b = ((double)(rand()%b1)+(double)(bias1*100))/100;
		else b=bias1;		
		
		if(dl==false) //сеть в один слой
		{
			x[i] = neuron(b);
			x[i].setaksnum(numout);
			for(int j=0;j<numout;j++)
			{	
				x[i].akson[j]=&y[j];			
				if (w1>0) x[i].w[j] = ((double)(rand()%w1)+(double)(bet1*100))/100;
				else x[i].w[j] = bet1;
				//log2<<"w="<<x[i].w[j]<<endl;
			}
		}
		else //сеть в два слоя
		{
			x[i] = neuron(b);
			x[i].setaksnum(dim2);
			for(int j=0;j<dim2;j++)
			{
				x[i].akson[j]=&nr[j];
				if (w1>0) x[i].w[j] = ((double)(rand()%w1)+(double)(bet1*100))/100;
				else x[i].w[j] = bet1;
			}
			if(i<dim2) //так как цикл по i перебирает до dim, а нейронов в скрытом слое может быть меньше
			for(int j=0;j<numout;j++)
			{	
				nr[i].akson[j]=&y[j];			
				if (w1>0) nr[i].w[j] = ((double)(rand()%w1)+(double)(bet1*100))/100;
				else nr[i].w[j] = bet1;				
			}
		}
	}
	//log2.close();
}

int network::work(double **img)
{
	//------------------------------------------------------------------
	//		Работа сети
	//------------------------------------------------------------------

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			x[i*height+j].add(img[i][j]); //возможно картинка подаваемая на нейросеть будет перевёрнута.
			x[i*height+j].set();
		}
	}

	if(dl==true) //сеть в два слоя
	{
		for(int i=0;i<dim2;i++)
		{
			nr[i].set();			
		}
	}

	//здесь должен быть выбор нейрона-победителя. или указание что победителя нет.
	int ans = 0;
	double max = y[0].func();
	for(int i=0;i<numout;i++)
	{
		y[i].set();
		if(y[i].ans>max) {ans=i;max=y[i].ans;}		
	}	
	return ans;
}

double * network::getouts()
{
	//------------------------------------------------------------------
	//		Вывод значений выходного слоя
	//------------------------------------------------------------------

	double * ans = new double[numout];
	for(int i=0;i<numout;i++)
	{
		ans[i]=y[i].ans;
	}
	return ans;
}

int network::learn(double ** img, int rans)
{
	//------------------------------------------------------------------
	//		Обучение сети
	//------------------------------------------------------------------

	double summa = 0;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			//log2<<x[i*width+j].sum<<"-";
			x[i*width+j].add(img[i][j]);
			x[i*width+j].set();
		 	//log2<<img[i][j]<<"-"<<x[i*width+j].ans<<"  ";
		}
		//log2<<"-----------------";
	}
	
	if(dl==true) //сеть в два слоя
	{
		for(int k=0;k<dim2;k++)
		{
			nr[k].set();			
		}
	}

	//здесь должен быть выбор нейрона-победителя. или указание что победителя нет.
	int ans = 0;
	double max = y[0].func();
	for(int i=0;i<numout;i++)
	{			
		//log2<<i<<" - "<<y[i].sum<<endl;
		y[i].set();
		if(y[i].ans>max) {ans=i;max=y[i].ans;}
		
	}	

	//log2<<endl;
	//получили вектор ошибки
	
	//								считаем ошибку выходного слоя
	for(int i=0;i<numout;i++)
	{
		double desout =  -0.5;
		if(i==rans) desout = 0.5;
		//расчёт ошибки.
		y[i].err = (desout-y[i].ans)* (y[i].ans+0.5) * (0.5 - y[i].ans);
		//log2<<i<<" - "<<y[i].ans<<" - "<<desout<<" - "<<y[i].err<<endl;
	}
	//log2<<endl;
	//log2<<endl;

	if(dl==true) //сеть в два слоя
	{
		//считаем ошибку скрытого слоя		
		for(int i=0;i<dim2;i++)
		{
			double sum = 0;
			for(int j=0;j<numout;j++)
			{
				sum += nr[i].akson[j]->err * nr[i].w[j];
			}
			nr[i].err = (nr[i].ans+0.5) * (0.5 - nr[i].ans) * sum;
			//log2<<sum<<" ";
		}
		//log2<<endl<<endl;
	}

	//корректировка весов
	for(int i=0;i<dim;i++)
	{
		if(dl==true) //сеть в два слоя
		{			
			for(int j=0;j<dim2;j++)
			{
				double coef = 1; // вообще коэффициент
				//if((alef * nr[j].err)>0)coef=dim; //если угадано верно, бонус
				x[i].w[j] += (alef * nr[j].err * x[i].ans*coef);
			}
			if(i<dim2)
			for(int j=0;j<numout;j++)
			{
				double coef = 1; // вообще коэффициент
				if((alef * y[j].err)>0)coef=numout; //если угадано верно, бонус
				nr[i].w[j] += (alef * y[j].err * nr[i].ans*coef);
			}
		}
		else //сеть в один слой
		{
			for(int j=0;j<numout;j++)
			{
				double coef = 1; // вообще коэффициент
				if((alef * y[j].err)>0)coef=numout; //если угадано верно, бонус
				x[i].w[j] += (alef * y[j].err * x[i].ans*coef);				
			}
		}
	}
	return ans;
}

void network::save()
{
	//------------------------------------------------------------------
	//		сохранение сети в файл
	//------------------------------------------------------------------

	ofstream file;
	file.open("net.txt");
	file<<dl<<endl;
	file<<dim<<endl;
	file<<dim2<<endl; //количество нейронов второго слоя
	file<<numout<<endl;

	if(!dl)
	{
		for(int i=0;i<dim;i++)
		{
			for(int j=0;j<numout;j++)
			{
				file<<x[i].w[j]<<endl;
			}
		}
	}
	else
	{
		for(int i=0;i<dim;i++)
		{
			for(int j=0;j<dim;j++)
			{
				file<<x[i].w[j]<<endl;
			}
		}
		for(int i=0;i<dim2;i++)
		{
			for(int j=0;j<numout;j++)
			{
				file<<nr[i].w[j]<<endl;
			}
		}
	}
	file.close();
}

void network::load()
{
	//------------------------------------------------------------------
	//		Загрузка сети из файла
	//------------------------------------------------------------------

	ifstream file;
	file.open("net.txt");
	file>>dl;
	file>>dim;
	file>>dim2; //количество нейронов второго слоя
	file>>numout;

	if(!dl)
	{
		x = new neuron [dim];		
		y = new neuron [numout];
		initialize();

		for(int i=0;i<dim;i++)
		{
			for(int j=0;j<numout;j++)
			{
				file>>x[i].w[j];
			}
		}
	}
	else
	{
		x = new neuron [dim];
		nr = new neuron [dim2];
		y = new neuron [numout];
		initialize();

		for(int i=0;i<dim;i++)
		{
			for(int j=0;j<dim;j++)
			{
				file>>x[i].w[j];
			}
		}
		for(int i=0;i<dim2;i++)
		{
			for(int j=0;j<numout;j++)
			{
				file>>nr[i].w[j];
			}
		}
	}
	file.close();
}