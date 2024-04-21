#pragma warning(disable:4996)
#include<stdio.h>
#include<cstdio>
#include<string>
#include<string.h>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<math.h>
#include<iomanip>
#include<stdlib.h>
#include<iostream>
#include<list>
#include<Windows.h>
#include<time.h>
#include<conio.h>
using namespace std;
#define MAXSIZE 100
int N = 0;
int a = 0, b = 0, c = 0;/*时，分, 秒*/
/*---------------------------------------------------------------*/
typedef struct data/*车辆信息的存储结构*/
{
	int start_hour = 0;/*到达时*/
	int start_min = 0; /*到达分*/
	int strat_sec = 0; /*到达秒*/
	int end_hour = 0;  /*离开时*/
	int end_min = 0;   /*离开分*/
	int end_sec = 0;   /*离开秒*/
	string id = "null";/*车牌号,且初始值为空*/
}Datatype;
typedef struct/*停车场和缓存停车场的定义结构*/
{
	Datatype stack[MAXSIZE];
	int top;
	int size;/*停车场所能够容纳的最大车辆数*/
}Seqstack;
/*-----------------------------------------------------------------*/
typedef struct Linknode/*便道的存储结构*/
{
	Datatype data;
	struct Linknode* next;
}Lnode;		 
typedef struct linkqueue
{
	Lnode* front = NULL;/*队头指针*/
	Lnode* rear = NULL;/*队尾指针*/
}Linkqueue;
/*----------------------------------------------------------------*/
void init_stack(Seqstack* s)/*将栈设为空栈，即将停车场设为空*/
{
	s->top = -1;
}
int length_stack(Seqstack* s)/*求取当前停车场的车辆数*/
{
	return s->top + 1;
}
bool empty_stack(Seqstack* s)/*判断停车场是否为空*/
{
	if (s->top == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool push_stack(Seqstack* s, Datatype x)/*车辆进入停车场*/
{
	if (s->top == N - 1)
	{
		return false;
	}
	else
	{
		s->top++;
		s->stack[s->top] = x;
		return true;
	}
}
Datatype pop_stack(Seqstack* s)/*车辆离开停车场*/
{
	if (empty_stack(s))
	{
		Datatype y;
		return y;
	}
	else
	{
		Datatype z;
		Datatype x;
		x = s->stack[s->top];
		s->stack[s->top] = z;/*出去的车辆重新为空*/
		s->top--;
		return x;
	}
}
/*------------------------------------------------------------*/
void init_queue(Linkqueue* q)/*便道初始化*/
{
	q->front = new Lnode;
	q->front->data.id = "null";
	q->front->data.end_hour = 0;
	q->front->data.end_min = 0;
	q->front->data.end_sec = 0;
	q->front->data.start_hour = 0;
	q->front->data.start_min = 0;
	q->front->data.strat_sec = 0;
	q->front->next = NULL;
	q->rear = q->front;
}
bool empty_queue(Linkqueue* q)/*判断便道是否为空*/
{
	if (q->front->next == NULL && q->rear->next == NULL)
		return true;
	else
		return false;
}
void en_queue(Linkqueue* q, Datatype x)/*车辆进入便道*/
{
	Lnode* p = new Lnode;
	p->data = x;
	p->next = NULL;
	if (empty_queue(q))
	{
		q->front->next = p;
		q->rear = p;
	}
	else
	{
		q->rear->next = p;
		q->rear = p;
		q->rear->next = NULL;
	}
}
Datatype de_queue(Linkqueue* q)/*车辆从便道中开出*/
{
	if (empty_queue(q))
	{
		Datatype y;
		return y;
	}
	else
	{
		Lnode* p = new Lnode;
		p = q->front->next;
		Datatype x = p->data;
		q->front->next = p->next;
		if (empty_queue(q))
		{
			q->front->data.id = "null";
			q->front->data.end_hour = 0;
			q->front->data.end_min = 0;
			q->front->data.end_sec = 0;
			q->front->data.start_hour = 0;
			q->front->data.start_min = 0;
			q->front->data.strat_sec = 0;
			q->front->next = NULL;
			q->rear = q->front;
		}
		free(p);
		return x;
	}
}
/*------------------------------------------------------------------*/
void local_time()
{
	time_t timer;
	struct tm* p;
	time(&timer);
	p = localtime(&timer);
	a = p->tm_hour;/*记录时和分*/
	b = p->tm_min;
	c = p->tm_sec;
	printf("%d年%d月%d日--%d:%d:%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday
		, p->tm_hour, p->tm_min, p->tm_sec);
}
/*--------------------------------------------------------------------*/
double cost(double price, int a, int b, int c, int d, int e, int f)/*计算停车费用*/
{
	double result = (d * 3600 + e * 60 + f) - (a * 3600 + b * 60 + c);
	result = result < 0 ? (0 - result) : result;
	if (result > 7200)
	{
		result = (result - 7200) * (price / 3600*1.5)+ (price*2);
		cout << "由于您停留的时间过于久啦，我们对您实行了阶梯收费，两小时之后的收费收取停车场费用的1.5倍";
		return result;
	}
	else
	{
		result = result * (price / 3600);
		return result;
	}
}
/*---------------------------------------------------------------------*/
void help()//进入显示
{
	cout << endl;
	cout << endl;
	cout << "                   ★-----★---------★---------★-----★" << endl;
	cout << endl;
	cout << "                   ☆     制作小软件，我是认真的！   ☆" << endl;
	cout << endl;
	cout << "                   ★-----★---------★---------★-----★" << endl;
	cout << endl;
	cout << endl;
}
void mainjiemian()
{
	cout << "                   ★-----★---------★---------★-----★" << endl;
	cout << "                           欢迎进入停车信息管理系统      " << endl;
	cout << "                   ☆                                  ☆" << endl;
	cout << "                               1 进入停车位              " << endl;
	cout << "                   ☆          2 离开停车位            ☆" << endl;
	cout << "                               3 停车场一览              " << endl;
	cout << "                   ☆          4 更改设置              ☆" << endl;
	cout << "                               5 退出系统                " << endl;
	cout << "                   ☆                                  ☆" << endl;
	cout << "                               Made BY ZJK               " << endl;
	cout << "                   ★-----★---------★---------★-----★" << endl;
	cout << endl;
	cout << endl;
	cout << "请选择数字命令：";
}
void exit()
{
	cout << "                   ★-----★---------★---------★-----★" << endl;
	cout << endl;
	cout << "                   ☆            感谢您的使用！        ☆" << endl;
	cout << endl;
	cout << "                   ★-----★---------★---------★-----★" << endl;
	cout << endl;
}
/*--------------------------------------------------------*/
int main()
{
	system("color 57");
	help();
	Seqstack* s = new Seqstack;/*停车场*/
	Seqstack* t = new Seqstack;/*缓存停车场*/
	Linkqueue* q = new Linkqueue;/*便道*/
	/*对三者分别进行初始化*/
	init_stack(s);
	init_stack(t);
	init_queue(q);
	double price;/*停车场价格*/
	printf("喵，请输入停车场容量大小(个):");
	scanf("%d", &N);
	s->size = N;/*对大小进行保存*/
	t->size = N;
	printf("喵，请设置停车场价格(元/小时):");
	scanf("%lf", &price);
	string order;
	char* end;/*末端指针*/
	system("cls");
	mainjiemian();
	while (cin >> order)
	{
		int a_order = static_cast<int>(strtol(order.c_str(), &end, 10));/*将输入进来的值转化为int类型*/
		switch (a_order + 48)
		{
		case'1':
		{
			string idnumber;
			Datatype x;/*新来车辆*/
			printf("亲，请输入您车牌号:");
			cin >> idnumber;
			printf("^ω^当前到达时间为:");
			local_time();
			x.id = idnumber;
			x.start_hour = a; x.start_min = b; x.strat_sec = c;/*将时间赋值给车辆信息*/
			x.end_hour = a; x.end_min = b; x.end_sec = c;
			if (length_stack(s) < N)
			{
				push_stack(s, x);
				printf("小张为您安排%d号停车位\n", s->top);
			}
			else
			{
				en_queue(q, x);
				printf("烦，停车场已满，还是先去便道吧，磕会儿瓜子先\n");
			}
			system("pause");
			system("cls");
			mainjiemian();
			break;
		}
		case'2':
		{
			string idnumber;
			printf("亲，请输入离开的车牌号:");
			cin >> idnumber;
			Datatype x;
			Datatype y;
			Datatype z;
			x.id = idnumber;
			while (empty_stack(s) == false && s->stack[s->top].id != idnumber)
			{
				push_stack(t, pop_stack(s));/*取出停车场中的车辆进入缓存停车场*/
			}
			if (empty_stack(s) == false && s->stack[s->top].id == idnumber)
			{

				printf("^ω^当前离开时间为:");
				local_time();
				s->stack[s->top].end_hour = a; s->stack[s->top].end_min = b; s->stack[s->top].end_sec = c;
				y.end_hour = a; y.end_min = b; y.end_sec = c;
				y.start_hour = s->stack[s->top].start_hour; y.start_min = s->stack[s->top].start_min; y.strat_sec = s->stack[s->top].strat_sec;
				printf("亲，一共需要交费%.4lf元哦\n", cost(price, s->stack[s->top].start_hour, s->stack[s->top].start_min, s->stack[s->top].strat_sec,
					a, b, c));
				pop_stack(s);/*将车取出*/
				while (empty_stack(t) == false)//再将缓存停车场中的车开回停车场中
				{
					push_stack(s, pop_stack(t));
				}
			}
			else
			{
				while (empty_stack(t) == false)//再将缓存停车场中的车开回停车场中
				{
					push_stack(s, pop_stack(t));
				}
				printf("哎呀，好像没有这辆车呢！\n");
			}
			while ((length_stack(s) < s->size) && empty_queue(q) == false)/*如果停车场未满，且便道不空，就再进车*/
			{
				/*进的时候要更新车辆的到达时间*/
				z = de_queue(q);
				z.start_hour = a; z.start_min = b; z.strat_sec = c;
				z.end_hour = a; z.end_min = b; z.end_sec = c;
				push_stack(s, z);
			}
			printf("o(^▽^)o...停车场中共有%d辆车\n", length_stack(s));
			system("pause");
			system("cls");
			mainjiemian();
			break;
		}
		case'3':
		{
			system("cls");
			printf("停车场信息:\n");
			printf("停车位\t\t车牌号\t\t到达时间\n");
			for (int i = 0; i < s->size; i++)
			{
				cout << std::right << "[" << i << "]";
				cout << std::right << setw(17) << s->stack[i].id;
				cout << std::right << setw(14) << s->stack[i].start_hour << ":";
				cout << s->stack[i].start_min << ":";
				cout << s->stack[i].strat_sec << endl;
			}
			printf("便道信息:\n");
			printf("序号\t\t车牌号\t\t到达时间\n");
			if (empty_queue(q))
			{
				printf("啦啦啦，便道是空的！\n");
			}
			else
			{
				int xuhao = 1;/*计数器*/
				Lnode* p = new Lnode;
				p = q->front->next;
				while (p->next != NULL)
				{
					cout << std::right << "[" << xuhao << "]";
					cout << std::right << setw(17) << p->data.id;
					cout << std::right << setw(14) << p->data.start_hour << ":";
					cout << p->data.start_min << ":";
					cout << p->data.strat_sec << endl;
					xuhao++;
					p = p->next;
				}
				cout << std::right << "[" << xuhao << "]";
				cout << std::right << setw(17) << q->rear->data.id;
				cout << std::right << setw(14) << q->rear->data.start_hour << ":";
				cout << q->rear->data.start_min << ":";
				cout << q->rear->data.strat_sec << endl;
			}
			system("pause");
			system("cls");
			mainjiemian();
			break;
		}
		case'4':
		{
			printf("亲，请输入停车场容量大小(个):");
			scanf("%d", &N);
			printf("亲，请设置停车场价格(元/小时):");
			scanf("%lf", &price);
			system("pause");
			system("cls");
			mainjiemian();
			break;
		}
		case'5':
		{
			system("cls");
			exit();
			return 0;
			break;
		}
		default:
		{
			cin.clear();
			cin.sync();
			cout << "手抖，输错了?没关系，重新开始吧。" << endl;
			system("pause");
			system("cls");
			mainjiemian();
			break;
		}
		}
	}
	return 0;
}