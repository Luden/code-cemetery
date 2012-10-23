#include "stdio.h"

class confa
	{
	public:
		unsigned char * x;
		unsigned char * y;
		unsigned char * r;
		unsigned char ** mas;
		int bcount;
		unsigned char maxx;
		unsigned char maxy;
		static const unsigned char LEFT = 128;
		static const unsigned char DOWN = 64;
		static const unsigned char RIGHT = 32;
		static const unsigned char UP = 16;

		confa(unsigned char ** m1,int bc, unsigned char mx, unsigned char my)
		{
			mas = m1;
			bcount = bc;
			maxx = mx;
			maxy = my;
			x = new unsigned char[bcount];			
			y = new unsigned char[bcount];			
			r = new unsigned char[bcount];
			int cur=0;
			int posx,posy;

			for(int i=0;i<mx;i++)
			{
				for(int j=0;j<my;j++)
				{
					if((mas[i][j]&64)!=0)
					{
						x[cur]=i;
						y[cur]=j;
						cur++;
					}
					if((mas[i][j]&16)!=0)
					{
						posx=i;
						posy=j;
					}
				}
			}
			reaches(posx,posy);
		}
		
		confa(confa * cf)
		{
			bcount = cf->bcount;
			maxx = cf->maxx;
			maxy = cf->maxy;
			mas = cf->mas;
			x = new unsigned char[bcount];		
			y = new unsigned char[bcount];		
			r = new unsigned char[bcount];
		
			for(int i=0;i<bcount;i++)
			{
				x[i] = cf->x[i];
				y[i] = cf->y[i];
				r[i] = cf->r[i];
			}
		}

		bool check(confa * c)
		{			
			for(int i=0;i<bcount;i++)
			{
				if((x[i]!=c->x[i])||(y[i]!=c->y[i])||(r[i]!=c->r[i]))return false;				
			}
			return true;
		}
		
		bool win()
		{
			for(int i=0;i<bcount;i++)
			{
				if((mas[x[i]][y[i]]&(96))!=96)return false;
			}
			return true;
		}

		//лаконичное рекурсивное определение ловушки групповой неподвижности
		bool myplace(unsigned short x, unsigned short y)
		{
			if((x<0)||(x>=maxx)||(y<0)||(y>=maxy))return true;
			if((mas[x][y]&4)!=0)return true;
			bool ans=true;			
			if((mas[x][y]&128)!=0)return true;
			if((mas[x][y]&96)==96)
			{
				mas[x][y]=mas[x][y]|4;
				ans = ans&&myplace(x-1,y);
				ans = ans&&myplace(x+1,y);
				ans = ans&&myplace(x,y-1);
				ans = ans&&myplace(x,y+1);
				mas[x][y]=mas[x][y]&(255-4);
				return ans;
			}
			else if((mas[x][y]&64)==64) return false;
			return true;
		}

		bool immobile(unsigned short x, unsigned short y)
		{
			if((x<0)||(x>=maxx)||(y<0)||(y>=maxy))return true;
			if((mas[x][y]&8)!=0)return true;
			bool ans=true;						
			if((mas[x][y]&128)!=0)return true;
			if((mas[x][y]&64)!=0)
			{
				mas[x][y]=mas[x][y]|8;
				ans = ans&&(immobile(x-1,y)||immobile(x+1,y))&&(immobile(x,y-1)||immobile(x,y+1));				
			
				mas[x][y]=mas[x][y]&(255-8);
				return ans;
			}
			return false;
		}

		bool lose()
		{
			bool ans = true;
			//все ящики недостежими/недвижимы
			for(int i=0;i<bcount;i++)if(r[i]!=0)ans=false;
			if(ans==true)return ans;

			//попали в ловушку
			for(int i=0;i<bcount;i++)if(immobile(x[i],y[i])&&(!(myplace(x[i],y[i]))))ans=true;

			//

			return ans;
		}

		void makemas()
		{
			for(int i=0;i<maxx;i++)
			{
				for(int j=0;j<maxy;j++)
				{				
					mas[i][j]=((mas[i][j])&(255-(64+16+1)));
				}
			}
			for(int i=0;i<bcount;i++)
			{
				mas[x[i]][y[i]]=mas[x[i]][y[i]]|64;
			}
		}
		
		confa * move(int n, unsigned char wh)
		{
			confa * ans = new confa(this);
			if(wh==LEFT)	ans->x[n]=ans->x[n]+1;
			if(wh==RIGHT)	ans->x[n]=ans->x[n]-1;
			if(wh==UP)		ans->y[n]=ans->y[n]-1;
			if(wh==DOWN)	ans->y[n]=ans->y[n]+1;
			ans->reaches(x[n],y[n]);
			return ans;
		}

		//рекурсивная волна волнового алгоритма
		void mark(unsigned char x, unsigned char y)
		{
			if((x<0)||(x>=maxx)||(y<0)||(y>=maxy))return;
			if((mas[x][y]&(128+64))!=0)return;	
			if((mas[x][y]&(1))!=0)return;

			mas[x][y]=mas[x][y]|1;
			mark(x-1,y);
			mark(x,y-1);
			mark(x+1,y);
			mark(x,y+1);
		}
		//проверка достижимостей блоков
		bool checkr(unsigned char x, unsigned char y)
		{
			if((x<0)||(x>=maxx)||(y<0)||(y>=maxy))return false;
			if((mas[x][y]&1)!=0)return true;
			else return false;
		}

		//проверка движимости блоков
		bool checkm(unsigned char x, unsigned char y)
		{
			if((x<0)||(x>=maxx)||(y<0)||(y>=maxy))return false;
			if((mas[x][y]&(128+64))!=0)return false;
			else return true;
		}

		void reaches(unsigned char x1, unsigned char y1)
		{
			makemas();
			mark(x1,y1);
			for(int i=0;i<bcount;i++)
			{
				r[i]=0;
				if((checkr(x[i]-1,y[i]))&&(checkm(x[i]+1,y[i])))r[i]=r[i]|LEFT;
				if((checkr(x[i],y[i]-1))&&(checkm(x[i],y[i]+1)))r[i]=r[i]|DOWN;
				if((checkr(x[i]+1,y[i]))&&(checkm(x[i]-1,y[i])))r[i]=r[i]|RIGHT;
				if((checkr(x[i],y[i]+1))&&(checkm(x[i],y[i]-1)))r[i]=r[i]|UP;
			}
		}
	};

//узел решения
class pathnode
{
public:
	pathnode * next;
	unsigned char x;
	unsigned char wh;
	pathnode(unsigned char x1, unsigned char w1)
	{
		x=x1;
		wh=w1;
		next = NULL;
	}
	~pathnode()
	{
		delete(next);
	}
};

//очередь решений
class path
{
public:
	pathnode * head;
	pathnode * tail;
	int length;
	
	path()
	{
		head=NULL;
		tail=NULL;
		length = 0;
	}

	path(path * p)
	{
		head=NULL;
		tail=NULL;
		length = 0;
		pathnode * temp = p->tail;
		while(temp!=NULL)
		{
			add(temp->x,temp->wh);
			temp=temp->next;
		}
	}

	path(path * p, unsigned char x1, unsigned char w1)
	{
		head=NULL;
		tail=NULL;
		length = 0;

		pathnode * temp = p->tail;
		while(temp!=NULL)
		{
			add(temp->x,temp->wh);
			temp=temp->next;
		}
		add(x1,w1);
	}

	~path()
	{
		pathnode * temp;
		while(head!=NULL)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}

	void add(unsigned char x1, unsigned char w1)
	{		
		pathnode * temp = new pathnode(x1,w1);
		if(tail==NULL)tail=temp;
		if(head==NULL)head=temp;
		else
		{
			head->next=temp;
			head=temp;
		}
		length++;
	}
};

class winpathnode
{
public:
	winpathnode * next;
	path * p;
	winpathnode()
	{
		next=NULL;
	}
	winpathnode(path * p1)
	{
		p = new path(p1);
	}
};
//стек успешных очередей решений
class winpath
{
public:
	winpathnode * head;
	int BestRes;

	winpath()
	{
		head = NULL;
		BestRes = int::MaxValue;
	}
	void add(path * p)
	{
		winpathnode * temp = new winpathnode(p);
		temp->next=head;
		head = temp;
		if(p->length<BestRes)BestRes=p->length;
	}
	path * best()
	{
		int min = int::MaxValue;
		path * ans = NULL;
		winpathnode * temp = head;
		while(temp!=NULL)
		{
			if(temp->p->length<min)
			{
				min=temp->p->length;
				ans = temp->p;
			}
			temp=temp->next;
		}
		return ans;
	}
};

//узел памяти
class confnode
{
public:
	confa * cf;
	int length;
	confnode * next;
	confnode (confa * c, path * p1)
	{
		cf = new confa(c);
		length = p1->length;
		next = NULL;
	}
};

//стек памяти
class conflist
{
public:
	confnode * head;
	conflist()
	{
		head = NULL;
	}
	void add(confa * c,path * p)
	{
		confnode * temp = new confnode(c,p);
		temp->next=head;
		head = temp;
	}

	bool check(confa * cf, path * p)
	{
		confnode * temp = head;
		while(temp!=NULL)
		{
			if(cf->check(temp->cf))
			{
				//return true;
				if(temp->length>p->length) //новый путь имеет меньшую длину
				{
					if(temp==head) //удалим старый путь
					{
						head=head->next;
						delete(temp);
					}
					else
					{
						confnode * temp2 = head;
						while(temp2->next!=temp)temp2=temp2->next;
						temp2->next=temp->next;
						delete(temp);
					}
					//скажем что запись не найдена
					return false;					
				}
				return true; //узел есть
			}
			temp=temp->next;
		}
		return false; //узла нет
	}
};