	//------------------------------------------------------------------
	//		������ ���������
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
	
	double bias; //����� ����������	

	double sum; //��������
	double ans; //�������� �������� ���������
	double err; //������
	int aksnum; //����� �������
	
	double * w; //����
	neuron ** akson; //������ ���������� �� �������� �������
	
	neuron();	
	neuron(double bias0);
	void add(double x);
	double set();
	double calcerr(double desout); //���������� ������
	void setaksnum(int n);
	double func();	
};

class network
{
public:
	int dim; //����������� �������� ���� ��������
	int dim2; //_����������_ �������� �������� ����
	int numout; //���������� �������� ��������

	int height; //��������� ��������
	int width;

	bool dl; //���� � 2 ����
	
	double alef;	
	double bias1;
	double bias2;
	
	double bet1; //�� � �� ��������� �����
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