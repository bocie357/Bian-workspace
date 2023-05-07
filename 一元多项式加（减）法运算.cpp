#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
typedef struct Polynomial
{
	float coef;																									//系数.
	int expn;																									//指数
	struct Polynomial* next;
}Polynomial, * Polyn;

Polyn Create_Polyn();																					//尾插法建立多项式.

void Print_Polyn(Polynomial* head);														//打印多项式.

Polyn Add_Polyn(Polynomial* pa, Polynomial* pb);										//多项式相加. 

Polyn Suberact_Polyn(Polynomial* pa, Polynomial* pb);									//多项式相减. 

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

Polyn Create_Polyn()																							//尾插法建立多项式.
{
	Polynomial* head, * rear, * s;
	char c[100];																											//系数
	int e;																												//指数
	head = (Polyn)malloc(sizeof(Polynomial));
	rear = head;																									/*rear始终指向单链表的尾部，便于尾插法建表。*/
	int flag = 1;
	printf("请依次输入多项式每一项的系数和指数（以#号结束）：\n");
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
		rear->next = s;																							 /*尾插*/
		rear = s;
	}
	rear->next = NULL;																						/*将表中最后一个结点的next置为NULL*/

	return head;
}

void Print_Polyn(Polynomial* head)																	/*打印多项式.*/
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

Polyn Add_Polyn(Polynomial* pa, Polynomial* pb)												//多项式相加.
{
	Polyn qa = pa->next;
	Polyn qb = pb->next;
	Polyn headc, pc, qc;
	pc = (Polyn)malloc(sizeof(Polynomial));															/*单链表pc用来存放pa,pb的和*/
	pc->next = NULL;
	headc = pc;
	while (qa != NULL && qb != NULL)																/*当两个多项式均未扫描结束时*/
	{
		qc = (Polyn)malloc(sizeof(Polynomial));
		if (qa->expn < qb->expn)																		/*pa的指数项小于pb的指数项*/
		{
			qc->coef = qa->coef;
			qc->expn = qa->expn;
			qa = qa->next;
		}
		else if (qa->expn == qb->expn)																/*指数项相同时*/
		{
			qc->coef = qa->coef + qb->coef;
			qc->expn = qa->expn;																			/*当然也可以是qb->expn*/
			qa = qa->next;
			qb = qb->next;
		}
		else {																											/*pb的指数项小于pa的指数项*/
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
	while (qa != NULL) { 																						/*pa存在剩余项，将剩余项插入到pc当中*/
		qc = (Polyn)malloc(sizeof(Polynomial));
		qc->coef = qa->coef;
		qc->expn = qa->expn;
		qa = qa->next;
		qc->next = pc->next;
		pc->next = qc;
		pc = qc;
	}
	while (qb != NULL) {																						/*pb存在剩余项，将剩余项插入到pc当中*/
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

Polyn Suberact_Polyn(Polynomial* pa, Polynomial* pb)									//多项式相减.
{
	Polyn h = pb;
	Polyn p = pb->next;
	Polyn pd;
	while (p) {																									/*pa-pb就等于pa+(-pb),所以将pb多项式的各项符号循环遍历变号*/
		p->coef *= -1;
		p = p->next;
	}

	pd = Add_Polyn(pa, h);																				/*利用已创函数Add_Polyn()执行pa+(-pb)，即减法运算*/

	for (p = h->next; p; p = p->next) {															/*执行完pa+(-pb)后，循环遍历，将pb的符号全部更改为之前的状态*/
		p->coef *= -1;
	}
	return pd;
}