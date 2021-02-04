#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 //infeasible ����ʵ�ֵģ� 
#define OVERFLOW -2   //overflow   ���
//Status�Ǻ�������
typedef int Status;

using namespace std; 

/*
	Name: �������� 
	Copyright: WonYno 
	Author: ���� 
	Date: 04/02/21 09:53
	Description: ���Ա����ʽ�洢�ṹ 
*/

// - - - - - - - - ���Ա�ĵ�����洢�ṹ - - - - - -
typedef int ElemType; 
typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LNode , *LinkList; 

//��ȡ�������е�i��Ԫ�ز�����e 
Status GetElem_L(LinkList L,int i,ElemType &e) {
	LinkList p;				
	p = L->next;	int j = 1;					// ��ʼ����pָ���һ���ڵ㣬jΪ������ 
	while (p && j < i) {						//	���� 
		p = p->next;	++j;
	}
	if( !p || j>i)	return ERROR;
	e = p->data;								//ȡ��i��Ԫ�� 
	return OK;
}// GetElem_L

// ���������� 
void CreateList_L(LinkList &L,int n) {
	L = (LinkList) malloc (sizeof(LNode));
	L->next = NULL;
	LinkList head = L;							//����ͷ�ڵ� 
	for(int i = 0 ; i < n ; ++i) {
		LinkList p = (LinkList) malloc (sizeof(LNode));
//		scanf("%d",&p->data);
		p->data = i+6;
//		p->next = L->next;	L->next = p;		//�嵽��ͷ
		p->next = NULL;		head->next = p;		head = p;			//�嵽��β		 
	}
}// CreateList_L

//��iλ�ò�����Ԫ��ֵΪe 
Status ListInsert_L(LinkList &L,int i,ElemType e) {
	LinkList p = L , s; int j = 0;
	while (p && j < i-1) {
		p = p->next;	++j;
	}
	if(!p || j > i-1)	return ERROR;
	s = (LinkList) malloc (sizeof(LNode));
	s->data = e;	s->next = p->next;
	p->next = s;
	return OK;
}//	ListInsert_L

//ɾ�� 
Status ListDelete_L(LinkList &L,int i,ElemType &e) {
	LinkList p = L , q;	int j=0;
	while (p->next && j < i-1) {
		p = p->next ; ++j;
	}
	if(!(p->next) || j > i-1)	return ERROR;
	q = p->next;	p->next = q->next;
	e = q->data;	free(q);
	return OK;
}// Listdelete_L 

//�ǵݼ��ϲ� 
void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc) {
	LinkList pa , pb , pc;
	pa = La->next;	pb = Lb->next;
	Lc = pc = La;										// ��La��ͷ�ڵ���lc��ͷ�ڵ� 
	while (pa && pb) {
		if(pa->data <= pb->data) {
			pc->next = pa;	pc = pa ; pa = pa->next;
		}
		else {
			pc->next = pb;	pc = pb;  pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;							//����ʣ��� 
	free(Lb); 	
}// MergeList_L

//��ӡ������ 
void PrintList(LinkList L) {
	LinkList p = L->next;
	while (p) {
		printf("%d\t",p->data);
		p = p->next;
	}
	printf("\n");
}

//������ 
int main(int argc, char** argv) {
	LinkList L , Lb ,Lc;

	//���������� 
	CreateList_L(L,5);	LinkList p = L->next;
	CreateList_L(Lb,15);
//	printf("%d\n",L->next->data);
	int e;
	GetElem_L(L,1,e);
	printf("e = %d\n",e);
	
	ListInsert_L(L,6,100000);
	PrintList(L);
	
	ListDelete_L(L,2,e);
	PrintList(L);
	MergeList_L(L,Lb,Lc);
	PrintList(Lc); 
	return 0;
}
