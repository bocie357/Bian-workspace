#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
typedef struct Polynomial
{
	float coef;																									//ϵ��.
	int expn;																									//ָ��
	struct Polynomial* next;
}Polynomial, * Polyn;

Polyn Create_Polyn();																					//β�巨��������ʽ.

void Print_Polyn(Polynomial* head);														//��ӡ����ʽ.

Polyn Add_Polyn(Polynomial* pa, Polynomial* pb);										//����ʽ���. 

Polyn Suberact_Polyn(Polynomial* pa, Polynomial* pb);									//����ʽ���. 

int main()
{
	Polynomial* pa, * pb, * pc, * pd;
	pa = Create_Polyn();
	pb = Create_Polyn();
	pc=Add_Polyn(pa,pb);
	pd = Suberact_Polyn(pa, pb);
	Print_Polyn(pc);
	Print_Polyn(pd);
	printf("#");

	return 0;
}

Polyn Create_Polyn()																							//β�巨��������ʽ.
{
	Polynomial* head, * rear, * s;
	char c[100];																											//ϵ��
	int e;																												//ָ��
	head = (Polyn)malloc(sizeof(Polynomial));
	rear = head;																									/*rearʼ��ָ�������β��������β�巨����*/
	int flag = 1;
	printf("�������������ʽÿһ���ϵ����ָ������#�Ž�������\n");
	while (flag==1) {	
		
		scanf("%s", &c);
		if (c[0] == '#') {
			flag = 0;
			continue;
		}
		float temp = atof(c);
		scanf("%d", &e);
		s = (Polyn)malloc(sizeof(Polynomial));
		s->coef = temp;
		s->expn = e;
		rear->next = s;																							 /*β��*/
		rear = s;
	}
	rear->next = NULL;																						/*���������һ������next��ΪNULL*/

	return head;
}

void Print_Polyn(Polynomial* head)																	/*��ӡ����ʽ.*/
{
	Polyn q = head->next;
	double doeftemp[1000]={ 0 };
	while (q) {
		doeftemp[q->expn] += q->coef;
		q = q->next;
	}
	for (int i = 0; i < 1000; i++) {
		if (doeftemp[i] != 0)
			printf("%gX^%d\n", doeftemp[i],i);
	}
}

Polyn Add_Polyn(Polynomial* pa, Polynomial* pb)												//����ʽ���.
{
	Polyn qa = pa->next;
	Polyn qb = pb->next;
	Polyn headc, pc, qc;
	pc = (Polyn)malloc(sizeof(Polynomial));															/*������pc�������pa,pb�ĺ�*/
	pc->next = NULL;
	headc = pc;
	while (qa != NULL && qb != NULL)																/*����������ʽ��δɨ�����ʱ*/
	{
		qc = (Polyn)malloc(sizeof(Polynomial));
		if (qa->expn < qb->expn)																		/*pa��ָ����С��pb��ָ����*/
		{
			qc->coef = qa->coef;
			qc->expn = qa->expn;
			qa = qa->next;
		}
		else if (qa->expn == qb->expn)																/*ָ������ͬʱ*/
		{
			qc->coef = qa->coef + qb->coef;
			qc->expn = qa->expn;																			/*��ȻҲ������qb->expn*/
			qa = qa->next;
			qb = qb->next;
		}
		else {																											/*pb��ָ����С��pa��ָ����*/
			qc->coef = qb->coef;
			qc->expn = qb->expn;
			qb = qb->next;
		}
		if (qc->coef != 0) {
			qc->next = pc->next;
			pc->next = qc;
			pc = qc;
		}
		else free(qc);
	}
	while (qa != NULL) { 																						/*pa����ʣ�����ʣ������뵽pc����*/
		qc = (Polyn)malloc(sizeof(Polynomial));
		qc->coef = qa->coef;
		qc->expn = qa->expn;
		qa = qa->next;
		qc->next = pc->next;
		pc->next = qc;
		pc = qc;
	}
	while (qb != NULL) {																						/*pb����ʣ�����ʣ������뵽pc����*/
		qc = (Polyn)malloc(sizeof(Polynomial));
		qc->coef = qb->coef;
		qc->expn = qb->expn;
		qb = qb->next;
		qc->next = pc->next;
		pc->next = qc;
		pc = qc;
	}
	return headc;
}

Polyn Suberact_Polyn(Polynomial* pa, Polynomial* pb)									//����ʽ���.
{
	Polyn h = pb;
	Polyn p = pb->next;
	Polyn pd;
	while (p) {																									/*pa-pb�͵���pa+(-pb),���Խ�pb����ʽ�ĸ������ѭ���������*/
		p->coef *= -1;
		p = p->next;
	}

	pd = Add_Polyn(pa, h);																				/*�����Ѵ�����Add_Polyn()ִ��pa+(-pb)������������*/

	for (p = h->next; p; p = p->next) {															/*ִ����pa+(-pb)��ѭ����������pb�ķ���ȫ������Ϊ֮ǰ��״̬*/
		p->coef *= -1;
	}
	return pd;
}