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
int a = 0, b = 0, c = 0;/*ʱ����, ��*/
/*---------------------------------------------------------------*/
typedef struct data/*������Ϣ�Ĵ洢�ṹ*/
{
	int start_hour = 0;/*����ʱ*/
	int start_min = 0; /*�����*/
	int strat_sec = 0; /*������*/
	int end_hour = 0;  /*�뿪ʱ*/
	int end_min = 0;   /*�뿪��*/
	int end_sec = 0;   /*�뿪��*/
	string id = "null";/*���ƺ�,�ҳ�ʼֵΪ��*/
}Datatype;
typedef struct/*ͣ�����ͻ���ͣ�����Ķ���ṹ*/
{
	Datatype stack[MAXSIZE];
	int top;
	int size;/*ͣ�������ܹ����ɵ��������*/
}Seqstack;
/*-----------------------------------------------------------------*/
typedef struct Linknode/*����Ĵ洢�ṹ*/
{
	Datatype data;
	struct Linknode* next;
}Lnode;		 
typedef struct linkqueue
{
	Lnode* front = NULL;/*��ͷָ��*/
	Lnode* rear = NULL;/*��βָ��*/
}Linkqueue;
/*----------------------------------------------------------------*/
void init_stack(Seqstack* s)/*��ջ��Ϊ��ջ������ͣ������Ϊ��*/
{
	s->top = -1;
}
int length_stack(Seqstack* s)/*��ȡ��ǰͣ�����ĳ�����*/
{
	return s->top + 1;
}
bool empty_stack(Seqstack* s)/*�ж�ͣ�����Ƿ�Ϊ��*/
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
bool push_stack(Seqstack* s, Datatype x)/*��������ͣ����*/
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
Datatype pop_stack(Seqstack* s)/*�����뿪ͣ����*/
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
		s->stack[s->top] = z;/*��ȥ�ĳ�������Ϊ��*/
		s->top--;
		return x;
	}
}
/*------------------------------------------------------------*/
void init_queue(Linkqueue* q)/*�����ʼ��*/
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
bool empty_queue(Linkqueue* q)/*�жϱ���Ƿ�Ϊ��*/
{
	if (q->front->next == NULL && q->rear->next == NULL)
		return true;
	else
		return false;
}
void en_queue(Linkqueue* q, Datatype x)/*����������*/
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
Datatype de_queue(Linkqueue* q)/*�����ӱ���п���*/
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
	a = p->tm_hour;/*��¼ʱ�ͷ�*/
	b = p->tm_min;
	c = p->tm_sec;
	printf("%d��%d��%d��--%d:%d:%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday
		, p->tm_hour, p->tm_min, p->tm_sec);
}
/*--------------------------------------------------------------------*/
double cost(double price, int a, int b, int c, int d, int e, int f)/*����ͣ������*/
{
	double result = (d * 3600 + e * 60 + f) - (a * 3600 + b * 60 + c);
	result = result < 0 ? (0 - result) : result;
	if (result > 7200)
	{
		result = (result - 7200) * (price / 3600*1.5)+ (price*2);
		cout << "������ͣ����ʱ����ھ��������Ƕ���ʵ���˽����շѣ���Сʱ֮����շ���ȡͣ�������õ�1.5��";
		return result;
	}
	else
	{
		result = result * (price / 3600);
		return result;
	}
}
/*---------------------------------------------------------------------*/
void help()//������ʾ
{
	cout << endl;
	cout << endl;
	cout << "                   ��-----��---------��---------��-----��" << endl;
	cout << endl;
	cout << "                   ��     ����С�������������ģ�   ��" << endl;
	cout << endl;
	cout << "                   ��-----��---------��---------��-----��" << endl;
	cout << endl;
	cout << endl;
}
void mainjiemian()
{
	cout << "                   ��-----��---------��---------��-----��" << endl;
	cout << "                           ��ӭ����ͣ����Ϣ����ϵͳ      " << endl;
	cout << "                   ��                                  ��" << endl;
	cout << "                               1 ����ͣ��λ              " << endl;
	cout << "                   ��          2 �뿪ͣ��λ            ��" << endl;
	cout << "                               3 ͣ����һ��              " << endl;
	cout << "                   ��          4 ��������              ��" << endl;
	cout << "                               5 �˳�ϵͳ                " << endl;
	cout << "                   ��                                  ��" << endl;
	cout << "                               Made BY ZJK               " << endl;
	cout << "                   ��-----��---------��---------��-----��" << endl;
	cout << endl;
	cout << endl;
	cout << "��ѡ���������";
}
void exit()
{
	cout << "                   ��-----��---------��---------��-----��" << endl;
	cout << endl;
	cout << "                   ��            ��л����ʹ�ã�        ��" << endl;
	cout << endl;
	cout << "                   ��-----��---------��---------��-----��" << endl;
	cout << endl;
}
/*--------------------------------------------------------*/
int main()
{
	system("color 57");
	help();
	Seqstack* s = new Seqstack;/*ͣ����*/
	Seqstack* t = new Seqstack;/*����ͣ����*/
	Linkqueue* q = new Linkqueue;/*���*/
	/*�����߷ֱ���г�ʼ��*/
	init_stack(s);
	init_stack(t);
	init_queue(q);
	double price;/*ͣ�����۸�*/
	printf("����������ͣ����������С(��):");
	scanf("%d", &N);
	s->size = N;/*�Դ�С���б���*/
	t->size = N;
	printf("����������ͣ�����۸�(Ԫ/Сʱ):");
	scanf("%lf", &price);
	string order;
	char* end;/*ĩ��ָ��*/
	system("cls");
	mainjiemian();
	while (cin >> order)
	{
		int a_order = static_cast<int>(strtol(order.c_str(), &end, 10));/*�����������ֵת��Ϊint����*/
		switch (a_order + 48)
		{
		case'1':
		{
			string idnumber;
			Datatype x;/*��������*/
			printf("�ף������������ƺ�:");
			cin >> idnumber;
			printf("^��^��ǰ����ʱ��Ϊ:");
			local_time();
			x.id = idnumber;
			x.start_hour = a; x.start_min = b; x.strat_sec = c;/*��ʱ�丳ֵ��������Ϣ*/
			x.end_hour = a; x.end_min = b; x.end_sec = c;
			if (length_stack(s) < N)
			{
				push_stack(s, x);
				printf("С��Ϊ������%d��ͣ��λ\n", s->top);
			}
			else
			{
				en_queue(q, x);
				printf("����ͣ����������������ȥ����ɣ��Ļ��������\n");
			}
			system("pause");
			system("cls");
			mainjiemian();
			break;
		}
		case'2':
		{
			string idnumber;
			printf("�ף��������뿪�ĳ��ƺ�:");
			cin >> idnumber;
			Datatype x;
			Datatype y;
			Datatype z;
			x.id = idnumber;
			while (empty_stack(s) == false && s->stack[s->top].id != idnumber)
			{
				push_stack(t, pop_stack(s));/*ȡ��ͣ�����еĳ������뻺��ͣ����*/
			}
			if (empty_stack(s) == false && s->stack[s->top].id == idnumber)
			{

				printf("^��^��ǰ�뿪ʱ��Ϊ:");
				local_time();
				s->stack[s->top].end_hour = a; s->stack[s->top].end_min = b; s->stack[s->top].end_sec = c;
				y.end_hour = a; y.end_min = b; y.end_sec = c;
				y.start_hour = s->stack[s->top].start_hour; y.start_min = s->stack[s->top].start_min; y.strat_sec = s->stack[s->top].strat_sec;
				printf("�ף�һ����Ҫ����%.4lfԪŶ\n", cost(price, s->stack[s->top].start_hour, s->stack[s->top].start_min, s->stack[s->top].strat_sec,
					a, b, c));
				pop_stack(s);/*����ȡ��*/
				while (empty_stack(t) == false)//�ٽ�����ͣ�����еĳ�����ͣ������
				{
					push_stack(s, pop_stack(t));
				}
			}
			else
			{
				while (empty_stack(t) == false)//�ٽ�����ͣ�����еĳ�����ͣ������
				{
					push_stack(s, pop_stack(t));
				}
				printf("��ѽ������û���������أ�\n");
			}
			while ((length_stack(s) < s->size) && empty_queue(q) == false)/*���ͣ����δ�����ұ�����գ����ٽ���*/
			{
				/*����ʱ��Ҫ���³����ĵ���ʱ��*/
				z = de_queue(q);
				z.start_hour = a; z.start_min = b; z.strat_sec = c;
				z.end_hour = a; z.end_min = b; z.end_sec = c;
				push_stack(s, z);
			}
			printf("o(^��^)o...ͣ�����й���%d����\n", length_stack(s));
			system("pause");
			system("cls");
			mainjiemian();
			break;
		}
		case'3':
		{
			system("cls");
			printf("ͣ������Ϣ:\n");
			printf("ͣ��λ\t\t���ƺ�\t\t����ʱ��\n");
			for (int i = 0; i < s->size; i++)
			{
				cout << std::right << "[" << i << "]";
				cout << std::right << setw(17) << s->stack[i].id;
				cout << std::right << setw(14) << s->stack[i].start_hour << ":";
				cout << s->stack[i].start_min << ":";
				cout << s->stack[i].strat_sec << endl;
			}
			printf("�����Ϣ:\n");
			printf("���\t\t���ƺ�\t\t����ʱ��\n");
			if (empty_queue(q))
			{
				printf("������������ǿյģ�\n");
			}
			else
			{
				int xuhao = 1;/*������*/
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
			printf("�ף�������ͣ����������С(��):");
			scanf("%d", &N);
			printf("�ף�������ͣ�����۸�(Ԫ/Сʱ):");
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
			cout << "�ֶ��������?û��ϵ�����¿�ʼ�ɡ�" << endl;
			system("pause");
			system("cls");
			mainjiemian();
			break;
		}
		}
	}
	return 0;
}