	//------------------------------------------------------------------
	//		Модуль простой очереди
	//------------------------------------------------------------------

#include "stdafx.h"
#include "stdio.h"

using namespace std;

class qnode
{
public:
	qnode * next;
	int x;
	int y;
	qnode(int x1, int y1)
	{
		x = x1;
		y = y1;
		next = NULL;
	}

};

class simpleq
{
public:
	qnode * head;
	qnode * tail;

	simpleq()
	{
		head = NULL;
		tail = NULL;
	}

	void add(int x1, int y1)
	{
		qnode * temp = new qnode(x1,y1);
		if(head==NULL)
		{
			head=temp;
			tail=temp;
		}
		else
		{
			tail->next=temp;
			tail=temp;
		}
	}

	bool get(int &x1, int &y1)
	{
		if(head==NULL)return false;
		else
		{
			x1 = head->x;
			y1 = head->y;
			qnode * temp = head->next;
			delete(head);
			head = temp;
			if(head==NULL)tail=NULL;
			return true;
		}
	}
};