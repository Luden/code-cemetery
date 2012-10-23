	//------------------------------------------------------------------
	//		Модуль нейросети
	//------------------------------------------------------------------

#include "stdafx.h"
#include "stdio.h"
#include "iostream"

using namespace std;

class neuron;
class network;

class neuron
{	
public:
	
	double bias; //порог восприятия	

	double sum; //сумматор
	double ans; //выданный нейроном результат
	double err; //ошибка
	int aksnum; //число аксонов
	
	double * w; //веса
	neuron ** akson; //массив указателей на связаные нейроны
	
	neuron();	
	neuron(double bias0);
	void add(double x);
	double set();
	double calcerr(double desout); //вычисление ошибки
	void setaksnum(int n);
	double func();	
};

class network
{
public:
	int dim; //размерность входного слоя нейронов
	int dim2; //_количество_ нейронов скрытого слоя
	int numout; //количество выходных нейронов

	int height; //параметры картинки
	int width;

	bool dl; //сеть в 2 слоя
	
	double alef;	
	double bias1;
	double bias2;
	
	double bet1; //от и до начальных весов
	double bet2;
	
	neuron * x;
	neuron * nr;	
	neuron * y;

	network(int n, int m, int numout0, double bias01, double bias02, double alef0, double w1, double w2, bool dl0, int d2);
	void initialize();
	int learn(double ** img, int rans);
	int work(double ** img);
	double * getouts();

	void save();
	void load();
};